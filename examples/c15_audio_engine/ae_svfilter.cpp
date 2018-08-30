/******************************************************************************/
/** @file           ae_combfilter.cpp
    @date           2018-05-10
    @version        1.0
    @author         Anton Schmied
    @brief          Combfilter
    @todo
*******************************************************************************/


#include "ae_svfilter.h"

/******************************************************************************/
/** @brief
*******************************************************************************/

ae_svfilter::ae_svfilter()
{

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_svfilter::init(float _samplerate)
{
    m_out = 0.f;

    m_warpConst_2PI = 6.28319f / _samplerate;

    m_resonance = 0.f;

//    m_first_attenuation = 0.f;
//    m_second_attenuation = 0.f;

    m_first_fir_stateVar = 0.f;
    m_second_fir_stateVar = 0.f;
    m_first_int1_stateVar = 0.f;
    m_first_int2_stateVar = 0.f;
    m_second_int1_stateVar = 0.f;
    m_second_int2_stateVar = 0.f;

    m_first_sv_sample = 0.f;
    m_first_sat_stateVar = 0.f;
    m_second_sat_stateVar = 0.f;

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_svfilter::apply(float _sampleA, float _sampleB, float _sampleComb, float *_signal)
{
    //******************************** Sample Mix ****************************//
    float tmpVar = _signal[SVF_AB];
    float firstSample = _sampleB * (1.f - tmpVar) + _sampleA * tmpVar;
    tmpVar = _signal[SVF_CMIX];
    firstSample = firstSample * (1.f - std::abs(tmpVar)) + _sampleComb * tmpVar;

    float secondSample = firstSample * _signal[SVF_PAR_4];
    secondSample += (m_first_sv_sample * _signal[SVF_PAR_3]);
    secondSample += (m_second_sat_stateVar * 0.1f);

    firstSample += (m_first_sat_stateVar * 0.1f);


    //************************** Frequency Modulation ************************//
    tmpVar = _sampleA * _signal[SVF_FMAB] + _sampleB * (1.f - _signal[SVF_FMAB]);


    //************************** 1st Stage SV FILTER *************************//
    float omega = (_signal[SVF_F1_CUT] + tmpVar * _signal[SVF_F1_FM]) * m_warpConst_2PI;
//    omega = std::min(omega, 1.9f);
    omega = std::clamp(omega, 0.f, 1.5f);                                           /// new

    float attenuation = ((2.f + omega) * (2.f - omega) * m_resonance)               /// new
            / (((m_resonance * omega) + (2.f - omega)) * 2.f);

    float firOut = (m_first_fir_stateVar + firstSample) * 0.25f;
    m_first_fir_stateVar = firstSample + DNC_const;

//    m_first_sv_sample = firOut - (m_first_attenuation * m_first_int1_stateVar + m_first_int2_stateVar);
    m_first_sv_sample = firOut - (attenuation * m_first_int1_stateVar + m_first_int2_stateVar);     /// new

    float int1Out = m_first_sv_sample * omega + m_first_int1_stateVar;
    float int2Out = int1Out * omega + m_first_int2_stateVar;

    float lowpassOutput  = int2Out + m_first_int2_stateVar;
    float bandpassOutput = int1Out + int1Out;
//    float highpassOutput = firstSample - (int1Out * m_first_attenuation + lowpassOutput);
    float highpassOutput = firstSample - (int1Out * attenuation + lowpassOutput);           ///new

    m_first_int1_stateVar = int1Out + DNC_const;
    m_first_int2_stateVar = int2Out + DNC_const;

    m_first_sv_sample  =  lowpassOutput  * std::max(-(_signal[SVF_LBH_1]), 0.f);
    m_first_sv_sample += (bandpassOutput * (1.f - std::abs(_signal[SVF_LBH_1])));
    m_first_sv_sample += (highpassOutput * std::max(_signal[SVF_LBH_1], 0.f));


    //************************** 1st Stage Parabol Sat ***********************//
    m_first_sat_stateVar = std::clamp(bandpassOutput, -2.f, 2.f);
    m_first_sat_stateVar *= (1.f - std::abs(m_first_sat_stateVar) * 0.25f);


    //************************** 2nd Stage SV FILTER *************************//
    omega = (_signal[SVF_F2_CUT] + tmpVar * _signal[SVF_F2_FM]) * m_warpConst_2PI;
//    omega = std::min(omega, 1.9f);
    omega = std::clamp(omega, 0.f, 1.5f);                   ///new

    attenuation = ((2.f + omega) * (2.f - omega) * m_resonance)     ///new
                         / (((m_resonance * omega) + (2.f - omega)) * 2.f);

    firOut = (m_second_fir_stateVar + secondSample) * 0.25f;
    m_second_fir_stateVar = secondSample + DNC_const;

//    tmpVar = firOut - (m_second_attenuation * m_second_int1_stateVar + m_second_int2_stateVar);
    tmpVar = firOut - (attenuation * m_second_int1_stateVar + m_second_int2_stateVar);          ///new

    int1Out = tmpVar * omega + m_second_int1_stateVar;
    int2Out = int1Out * omega + m_second_int2_stateVar;

    lowpassOutput  = int2Out + m_second_int2_stateVar;
    bandpassOutput = int1Out + int1Out;
//    highpassOutput = tmpVar - (int1Out * m_second_attenuation + lowpassOutput);
    highpassOutput = tmpVar - (int1Out * attenuation + lowpassOutput);

    m_second_int1_stateVar = int1Out + DNC_const;
    m_second_int2_stateVar = int2Out + DNC_const;

    tmpVar  =  lowpassOutput  * std::max(-_signal[SVF_LBH_2], 0.f);
    tmpVar += (bandpassOutput * (1.f - std::abs(_signal[SVF_LBH_2])));
    tmpVar += (highpassOutput * std::max(_signal[SVF_LBH_2], 0.f));


    //************************* 2nd Stage Parabol Sat ************************//
    m_second_sat_stateVar = std::clamp(bandpassOutput, -2.f, 2.f);
    m_second_sat_stateVar *= (1.f - std::abs(m_second_sat_stateVar) * 0.25f);


    //****************************** Crossfades ******************************//
    m_out  = m_first_sv_sample * _signal[SVF_PAR_1];
    m_out += (tmpVar * _signal[SVF_PAR_2]);
}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_svfilter::set(float *_signal)
{
    float resonance = _signal[SVF_RES];
    resonance = 1.f - resonance;
    resonance += resonance;
//    resonance = std::max(resonance, 0.02f);
    m_resonance = std::max(resonance, 0.02f);

#if 0
    //****************************** 1st Stage ******************************//
    float omega = _signal[SVF_F1_CUT] * m_warpConst_2PI;
    omega = std::min(omega, 1.9f);

    m_first_attenuation = ((2.f + omega) * (2.f - omega) * resonance)
                        / (((resonance * omega) + (2.f - omega)) * 2.f);


    //****************************** 2nd Stage ******************************//
    omega = _signal[SVF_F2_CUT] * m_warpConst_2PI;
    omega = std::min(omega, 1.9f);

    m_second_attenuation = ((2.f + omega) * (2.f - omega) * resonance)
                         / (((resonance * omega) + (2.f - omega)) * 2.f);
#endif
}

/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_svfilter::resetDSP()
{
    m_out = 0.f;

    m_resonance = 0.f;

    m_first_fir_stateVar = 0.f;
    m_second_fir_stateVar = 0.f;
    m_first_int1_stateVar = 0.f;
    m_first_int2_stateVar = 0.f;
    m_second_int1_stateVar = 0.f;
    m_second_int2_stateVar = 0.f;

    m_first_sv_sample = 0.f;
    m_first_sat_stateVar = 0.f;
    m_second_sat_stateVar = 0.f;

}
