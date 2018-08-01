/******************************************************************************/
/** @file		ae_feedbackmixer.cpp
    @date		2017-07-30
    @version	1.0
    @author		Anton Schmied
    @brief		Feedbackmixer
*******************************************************************************/


#include "ae_feedbackmixer.h"


/******************************************************************************/
/** @brief
*******************************************************************************/

ae_feedbackmixer::ae_feedbackmixer()
{

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_feedbackmixer::init(float _samplerate)
{
    m_out = 0.f;

    m_warpConst_PI = pi / _samplerate;
    m_freqClip_min = _samplerate / 24000.f;
    m_freqClip_max = _samplerate / 3.f;

    //***************************** 30Hz Highpass ****************************//
    m_hp30hz_b0 = (twopi / _samplerate) * 30.f;
    m_hp30hz_b0 = std::min(m_hp30hz_b0, 0.8f);

    m_hp30hz_stateVar = 0.f;

    //*************************** 1 pole Highpass ****************************//
    m_hp_b0 = 0.f;
    m_hp_b1 = 0.f;
    m_hp_a1 = 0.f;

    m_hp_stateVar_1 = 0.f;
    m_hp_stateVar_2 = 0.f;
}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_feedbackmixer::set(float *_signal)
{
    float omega = std::clamp(0.f, m_freqClip_min, m_freqClip_max);          ///_signal[FEEDB_HPF]
    omega = NlToolbox::Math::tan(omega * m_warpConst_PI);

    m_hp_a1 = (1.f - omega) / (1.f + omega);
    m_hp_b0 = 1.f / (1.f + omega);
    m_hp_b1 = (1.f / (1.f + omega)) * -1.f;
}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_feedbackmixer::apply(float _sampleComb, float _sampleSVF, float _sampleFX, float *_signal)
{
    float tmpVar = _sampleFX * 0.f + _sampleComb * 0.f + _sampleSVF * 0.f;      /// _signal[FEEDB_CMB] _signal[FEEDB_SVF] _signal[FEEDB_FX]

    m_out  = m_hp_b0 * tmpVar;                  // HP
    m_out += m_hp_b1 * m_hp_stateVar_1;
    m_out += m_hp_a1 * m_hp_stateVar_2;

    m_hp_stateVar_1 = tmpVar + DNC_CONST;
    m_hp_stateVar_2 = m_out + DNC_CONST;

    m_out *= 0.f;               /// _signal[FEEDB_DRV]

    tmpVar = m_out;
    m_out = NlToolbox::Math::sinP3_wrap(m_out);
    m_out = NlToolbox::Others::threeRanges(m_out, tmpVar, 0.f);     /// _signal[FEEDB_FLD]

    tmpVar  = m_out * m_out;
    tmpVar -= m_hp30hz_stateVar;                // HP 30Hz
    m_hp30hz_stateVar = tmpVar * m_hp30hz_b0 + m_hp30hz_stateVar + DNC_CONST;

    m_out = NlToolbox::Others::parAsym(m_out, tmpVar, 0.f);         /// _signal[FEEDB_ASM]

    m_out = tmpVar * 0.f;           /// _signal[FEEDB_LVL]
}
