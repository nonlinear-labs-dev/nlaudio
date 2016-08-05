/******************************************************************************/
/** @file		cabinet.cpp
    @date		2016-07-01
    @version	0.2
    @author		Anton Schmied[2016-03-18]
    @brief		Cabinet Class member and method definitions
*******************************************************************************/

#include "cabinet.h"



/******************************************************************************/
/** Cabinet Default Constructor
 * @brief    initialization of the modules local variabels with default values
 *           SampleRate:            48 kHz
 *           Drive:                 20 dB
 *           Tilt:                  -12 dB
 *           HiCut Frequency:       4700 Hz     Lowpass Filters
 *           LoCut Frequency:       61 Hz       Highpass Filters
 *           Fold:                  0.25
 *           Asym:                  0.1
 *           Cabinet Level:         -14 dB
 *           Mix:                   0.f
*******************************************************************************/

Cabinet::Cabinet()
    : mSampleRate(48000.f)
    , mFold(0.25f)
    , mAsym(0.1f)

    // External module initialisation
    , mHighpass(48000.f, 61.f, 0.f, 0.5, BiquadFilterType::HIGHPASS)
    , mLowpass1(48000.f, 4700.f, 0.f, 0.5, BiquadFilterType::LOWPASS)
    , mLowpass2(48000.f, 4700.f * 1.333f, 0.f, 0.5, BiquadFilterType::LOWPASS)
    , mLowshelf1(48000.f, 1200.f, -12.f, 2.f, 0.5f, TiltFilterType::LOWSHELF)
    , mLowshelf2(48000.f, 1200.f, -12.f * (-1.f), 2.f, 0.5f, TiltFilterType::LOWSHELF)
    , mHighpass30Hz(48000.f)
    , mDrySmoother(48000.f, 0.032f)
    , mWetSmoother(48000.f, 0.032f)
    , mDriveSmoother(48000.f, 0.032f)
{
    setDrive(20.f);
    setSaturation(-12.f);
    setMix(0.f);
    setCabLvl(-14.f);
}

/******************************************************************************/
/** Cabinet Parameterized Constructor
 * @brief    initialization of the modules local variabels with custom
 *           parameters
*******************************************************************************/

Cabinet::Cabinet(int _sampleRate,
                 float _drive,
                 float _tilt,
                 float _hiCut,
                 float _loCut,
                 float _fold,
                 float _asym,
                 float _cabLvl,
                 float _mix)
    : mSampleRate(static_cast<float>(_sampleRate))
    , mFold(_fold)
    , mAsym(_asym)

    // External module initialisation
    , mHighpass(_sampleRate, _loCut, 0.f, 0.5, BiquadFilterType::HIGHPASS)
    , mLowpass1(_sampleRate, _hiCut, 0.f, 0.5, BiquadFilterType::LOWPASS)
    , mLowpass2(_sampleRate, _hiCut * 1.333f, 0.f, 0.5, BiquadFilterType::LOWPASS)
    , mLowshelf1(_sampleRate, 1200.f, _tilt, 2.f, 0.5f, TiltFilterType::LOWSHELF)
    , mLowshelf2(_sampleRate, 1200.f, _tilt * (-1.f), 2.f, 0.5f, TiltFilterType::LOWSHELF)
    , mHighpass30Hz(_sampleRate)
    , mDrySmoother(_sampleRate, 0.032f)
    , mWetSmoother(_sampleRate, 0.032f)
    , mDriveSmoother(_sampleRate, 0.032f)

{
    setDrive(_drive);
    setSaturation(_tilt);
    setCabLvl(_cabLvl);
    setMix(_mix);
}



/******************************************************************************/
/** @brief    sets fold amount
 *  @param    fold amount [0 .. 1]
*******************************************************************************/

inline void Cabinet::setFold(float _fold)
{
    mFold = _fold;
}



/******************************************************************************/
/** @brief    sets asym amount
 *  @param    asym amount [0 .. 1]
*******************************************************************************/

inline void Cabinet::setAsym(float _asym)
{
    mAsym = _asym;
}



/******************************************************************************/
/** @brief    sets satL amount
 *  @param    tilt amount [-50 .. 50] dB
*******************************************************************************/

inline void Cabinet::setSaturation(float _tilt)
{
    mSaturation = NlToolbox::Conversion::db2af(0.5f * _tilt);
}



/******************************************************************************/
/** @brief    sets mix amount, calculates dry and wet amounts,
 *            and initializes the smoothers
 *  @param    mix amount [0 .. 1]
*******************************************************************************/

void Cabinet::setMix(float _mix)
{
    mMix = _mix;
    mWet = mMix * mCabLvl;
    mDry = 1.f - mMix;

    mDrySmoother.initSmoother(mDry);
    mWetSmoother.initSmoother(mWet);
}



/******************************************************************************/
/** @brief    sets cabinet level
 *  @param    cabinet level [-50 .. 0] dB
*******************************************************************************/

inline void Cabinet::setCabLvl(float _cabLvl)
{
    mCabLvl = NlToolbox::Conversion::db2af(_cabLvl);

    mWet = mMix * mCabLvl;
    mWetSmoother.initSmoother(mWet);
}



/******************************************************************************/
/** @brief    sets drive level
 *  @param    drive level [0 .. 50] dB
*******************************************************************************/

void Cabinet::setDrive(float _drive)
{
    mDrive = NlToolbox::Conversion::db2af(_drive);
    mDriveSmoother.initSmoother(mDrive);
}



/******************************************************************************/
/** @brief    sets hiCut for the two lowpass fiters
 *  @param    hiCut [ .. ] Hz
*******************************************************************************/

void Cabinet::setHiCut(float _hiCut)
{
    mLowpass1.setCutFreq(_hiCut);
    mLowpass2.setCutFreq(_hiCut * 1.333f);
}



/******************************************************************************/
/** @brief    sets loCut for the highpass fiter
 *  @param    loCut [ .. ] Hz
*******************************************************************************/

void Cabinet::setLoCut(float _loCut)
{
    mHighpass.setCutFreq(_loCut);
}



/******************************************************************************/
/** @brief    sets tilt level for the two lowshelf filters
 *  @param    tilt [-50 .. 50] dB
*******************************************************************************/

void Cabinet::setTilt(float _tilt)
{
    mLowshelf1.setTilt(_tilt);
    mLowshelf2.setTilt(_tilt * (-1.f));

    setSaturation(_tilt);
}



/*****************************************************************************/
/** @brief    interface method which converts and scales the incoming midi
 *            values and passes these to the respective methods
 *  @param    midi control value [0 ... 127]
 *  @param    midi control ID -> enum CtrlID (cabinet.h)
******************************************************************************/

void Cabinet::setCabinetParams(float _ctrlVal, unsigned char _ctrlTag)
{
    switch(_ctrlTag)
    {
        case CtrlId::HICUT:
        _ctrlVal = (_ctrlVal * 80.f) / 127.f + 60.f;            //Midi to Pitch [60 .. 140]
        printf("HiCut: %f\n", _ctrlVal);

        _ctrlVal = pow(2.f, (_ctrlVal - 69.f) / 12) * 440.f;    //Pitch to Freq [261Hz .. 26580Hz]

        setHiCut(_ctrlVal);
        break;

        case CtrlId::LOCUT:
        _ctrlVal = (_ctrlVal * 80.f) / 127.f + 20.f;            //Midi to Pitch [20 ..100]
        printf("LoCut: %f\n", _ctrlVal);

        _ctrlVal = pow(2.f, (_ctrlVal - 69.f) / 12) * 440.f;    //Pitch to Freq [26Hz .. 2637Hz]
        setLoCut(_ctrlVal);
        break;

        case CtrlId::MIX:
        _ctrlVal = _ctrlVal / 127.f;                            //Midi to [0 .. 1]
        printf("Mix: %f\n", _ctrlVal);

        setMix(_ctrlVal);
        break;

        case CtrlId::CABLEVEL:
        _ctrlVal = (_ctrlVal - 127.f) * (50.f / 127.f);         //Midi to [-50db .. 0dB]
        printf("Cab Lvl: %f\n", _ctrlVal);

        setCabLvl(_ctrlVal);
        break;

        case CtrlId::DRIVE:
        _ctrlVal = _ctrlVal * (50.f / 127.f);                     //Midi to [0dB .. 50dB]
        printf("Drive: %f\n", _ctrlVal);

        setDrive(_ctrlVal);
        break;

        case CtrlId::TILT:
        _ctrlVal = (_ctrlVal - 63.5f) * (50.f / 63.5f);           //Midi to [-50dB .. 50dB]
        printf("Tilt: %f\n", _ctrlVal);

        setTilt(_ctrlVal);
        break;

        case CtrlId::FOLD:
        _ctrlVal = _ctrlVal / 127.f;                              //Midi to [0 .. 1]
        printf("Fold: %f\n", _ctrlVal);

        setFold(_ctrlVal);
        break;

        case CtrlId::ASYM:
        _ctrlVal = _ctrlVal / 127.f;                              //Midi to [0 .. 1]
        printf("Asym: %f\n", _ctrlVal);

        setAsym(_ctrlVal);
        break;
    }
}


/*****************************************************************************/
/** @brief    applies the cabinet effect to the incoming sample depending on the channel
 *  @param    raw Sample
 *  @return   processed sample
******************************************************************************/

float Cabinet::applyCab(float _currSample)
{
    mDry = mDrySmoother.smooth();                         //apply smoothers
    mWet = mWetSmoother.smooth();
    mDrive = mDriveSmoother.smooth();

    float output = 0.f;

    output = _currSample * mDrive;                        // apply drive

    output = mHighpass.applyFilter(output);           // apply biquad highpass filter

    output = mLowshelf1.applyFilter(output);           // apply first biquad tilt lowshelf filters

    output = sineShaper(output);

    output = mLowshelf2.applyFilter(output);           // apply second biquad tilt lowshelf filters

    output = mLowpass1.applyFilter(output);            // apply biquad lowpass filters
    output = mLowpass2.applyFilter(output);

    output = NlToolbox::Crossfades::crossFade(_currSample, output, mDry, mWet);       // apply crossfade between the incoming and the processed sample

    return output;
}



/*****************************************************************************/
/** @brief    sine shaping module - might moove to tools.h
 *  @param    raw Sample
 *  @return   processed sample
******************************************************************************/


float Cabinet::sineShaper(float _currSample)
{
    _currSample *= (0.1588f / mSaturation);          ///das kann/muss eine Konstane sein!!!

    float ctrlSample = _currSample;

    _currSample = NlToolbox::Math::sinP3(_currSample);

    _currSample = NlToolbox::Others::threeRanges(_currSample, ctrlSample, mFold);

    float currSample_square = mHighpass30Hz.applyFilter(_currSample * _currSample);

    _currSample = NlToolbox::Others::parAsym(_currSample, currSample_square, mAsym);

    _currSample *= mSaturation;

    return _currSample;

}

