/**
 * @file       cabinet.h
 * @date       2016-03-18
 * @brief      this class is an implementation of the cabinet effect as found in Reaktor
 * @author     Anton Schmied [date of file creation 2016-03-18]
*/

#pragma once

#include "math.h"
#include "tools.h"
#include "biquadfilters.h"
#include "tiltfilters.h"
#include "smoother.h"

class Cabinet
{
public:
    /** Cabinet Constructor with default values */
    Cabinet(int _sRate,
            float _drive = 20.f,
            float _tilt = -12.f,
            float _hiCut = 4700.f,
            float _loCut = 61.f,
            float _fold = 0.25f,
            float _asym = 0.1f,
            float _cabLvl = -14.f,
            float _mix = 0.f)
        :sRate(static_cast<float>(_sRate))
        ,mix(0.f)
        ,fold(_fold)
        ,asym(_asym)
        ,lowpass1(_sRate, _hiCut)
        ,lowpass2(_sRate, _hiCut * 1.333f)
        ,highpass1(_sRate, _loCut, 0.f, 0.5, BiquadFiltertype::highpass)
        ,lowshelf1(_sRate, 1200.f, _tilt, 2.f, 0.5f, TiltFiltertype::lowshelf)
        ,lowshelf2(_sRate, 1200.f, _tilt * (-1.f), 2.f, 0.5f, TiltFiltertype::lowshelf)
        ,drySmoother(_sRate, 0.032f)
        ,wetSmoother(_sRate, 0.032f)
        ,driveSmoother(_sRate, 0.032f)
        ,inCh1Delay(0.f)
        ,inCh2Delay(0.f)
    {
        setDrive(_drive);
        setSatL(_tilt);
        setCabLvl(_cabLvl);
        setMix(_mix);
    }

    ~Cabinet(){}

    /** @brief    applies the cabinet effect to the incoming sample depending on the channel
     *  @param    raw Sample
     *  @param    channel index, 0 - Left, 1 - Right
     *  @return   processed sample
    */
    float applyCab(float currSample, unsigned int chInd)
    {
        dry = drySmoother.smooth();                         //apply smoothers
        wet = wetSmoother.smooth();
        drive = driveSmoother.smooth();

        float output = 0.f;

        output = currSample * drive;                        // apply drive

        output = highpass1.applyFilter(output, chInd);      // apply biquad highpass filter

        output = lowshelf1.applyFilter(output, chInd);      // apply first biquad tilt lowshelf filters

        output = hypSinSatL(output, chInd);                 // apply hypSinSat

        output = lowshelf2.applyFilter(output, chInd);      // apply second biquad tilt lowshelf filters

        output = lowpass1.applyFilter(output, chInd);       // apply biquad lowpass filters
        output = lowpass2.applyFilter(output, chInd);

        output = xFade(currSample, output);                 // apply effect amount

        return output;
    }

    /** @brief    sets fold amount
     *  @param    fold amount [0 .. 1]
    */
    inline void setFold(float _fold)        //set FOLD amount
    {
        fold = _fold;
    }

    /** @brief    sets asym amount
     *  @param    asym amount [0 .. 1]
    */
    inline void setAsym(float _asym)         //set ASYM amount
    {
        asym = _asym;
    }

    /** @brief    sets satL amount
     *  @param    tilt amount [-50 .. 50] dB
    */
    inline void setSatL(float _tilt)        //set SETL amount
    {
        satL = Nl::db2af(0.5f * _tilt);
    }

    /** @brief    sets mix amount, calculate dry and wet amounts
     *  @param    mix amount [0 .. 1]
    */
    void setMix(float _mix)          //set MIX amount
    {
        mix = _mix;
        wet = mix * cabLvl;
        dry = 1.f - mix;

        drySmoother.initSmoother(dry);
        wetSmoother.initSmoother(wet);
    }

    /** @brief    sets cabinet level
     *  @param    fold amount [-50 .. 0] dB
    */
    void setCabLvl(float _cabLvl)           //set CABLVL
    {
        cabLvl = Nl::db2af(_cabLvl);
        setMix(mix);
    }

    /** @brief    sets drive level
     *  @param    drive level [0 .. 50] dB
    */
    void setDrive(float _drive)             //set DRIVE
    {
        drive = Nl::db2af(_drive);
        driveSmoother.initSmoother(drive);
    }

    /** @brief    sets hiCut for the two lowpass fiters
     *  @param    hiCut [ .. ] Hz
    */
    void setHiCut(float _hiCut)             //set HICUT
    {
        lowpass1.setCutFreq(_hiCut);
        lowpass2.setCutFreq(_hiCut * 1.333f);
    }

    /** @brief    sets loCut for the highpass fiter
     *  @param    loCut [ .. ] Hz
    */
    void setLoCut(float _loCut)             //set LOCUT
    {
        highpass1.setCutFreq(_loCut);
    }

    /** @brief    sets tilt level for the two lowshelf filters
     *  @param    tilt [-50 .. 50] dB
    */
    void setTilt(float _tilt)               //set TILT
    {
        lowshelf1.setTilt(_tilt);
        lowshelf2.setTilt(_tilt * (-1.f));
        setSatL(_tilt);
    }

private:
    float sRate;                /**< samplerate */
    float output;               /**< processed sample*/

    /** Cabinet Controls*/
    float drive;                /**< drive level [0 .. 50] dB, default 20dB */
    float cabLvl;               /**< cabinet level [-50 .. 0] dB, default -14dB */
    float mix;                  /**< mix amount [0 .. 1], default 0.0 */
    float fold;                 /**< fold amount [0 .. 1], default 0.25 */
    float asym;                 /**< asym amount [0 .. 1], default 0.1 */

    /** Resulting Parameters*/
    float satL;                 /**< saturation */
    float wet;                  /**< wet amount */
    float dry;                  /**< dry amount */

    /** filter objects */
    BiquadFilters lowpass1;     /**< first lowpass */
    BiquadFilters lowpass2;     /**< second lowpass */
    BiquadFilters highpass1;    /**< first highpass */
    TiltFilters lowshelf1;      /**< first lowshelf1 */
    TiltFilters lowshelf2;      /**< second lowshelf */

    /** Smoother objects*/
    Smoother drySmoother;       /**< dry level smoother */
    Smoother wetSmoother;       /**< wet level smoother */
    Smoother driveSmoother;     /**< drive level smoother */

    /** hp 1 delays */
    float inCh1Delay;           /**< channel 1 delay for internal 1. order highpass */
    float inCh2Delay;           /**< channel 2 delay for internal 1. order highpass */

    /** @brief    hyperbolic sine calculation
     *  @param    raw Sample
     *  @param    channel index, 0 - Left, 1 - Right
     *  @return   processed sample
    */
    float hypSinSatL(float currSample, unsigned int chInd)
    {
        currSample *= (0.1588f / satL);

        float ctrl = currSample;
        currSample = sinP3(currSample);

        if(ctrl < -0.25f)
        {
            currSample = (currSample + 1.f) * fold + (-1.f);
        }
        else if(ctrl > 0.25f)
        {
            currSample = (currSample + (-1.f)) * fold + 1.f;
        }

        currSample = ((1.f - asym) * currSample) + (hp1(currSample * currSample, chInd) * asym * 2);

        currSample *= satL;

        return currSample;
    }

    /** @brief    calculation of dry and wet amounts depending on mix amount
     *  @param    raw Sample
     *  @param    processed sample
     *  @return   a mix of both samples
    */
    inline float xFade(float sampleIn1, float sampleIn2)
    {
        return ((sampleIn1 * dry) + (sampleIn2 * wet));
    }


    /** @brief    sine calculation of an incoming value - might move to tools.h
     *  @param    value
     *  @return   sine value
    */
    inline float sinP3(float x)
    {
        x += -0.25f;
        float x_round = round(x);
        x -= x_round;!

        x += x;
        x = fabs(x);
        x = 0.5f - x;

        float x_square = x * x;
        x = x * ((2.26548 * x_square - 5.13274) * x_square + 3.14159);

        return x;
    }

    /** @brief    implementation of a 1. order highpass at 30Hz - might move to it's own file
     *  @param    raw Sample
     *  @param    channel Index
     *  @return   processed sample
    */
    float hp1(float sampleIN, unsigned int chInd)
    {
        float w0 = 30.f * (2 * M_PI / sRate);

        if(w0 > 0.8f)
            w0 = 0.8f;

        float sampleOUT;

        if (chInd == 0)
        {
            sampleOUT = sampleIN - inCh1Delay;
            inCh1Delay = sampleOUT * w0 + inCh1Delay;
        }

        else if (chInd == 1)
        {
            sampleOUT = sampleIN - inCh2Delay;
            inCh2Delay = sampleOUT * w0 + inCh2Delay;
        }

        return sampleOUT;
    }
};
