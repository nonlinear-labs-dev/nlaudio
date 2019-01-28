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
    float omega = std::clamp(_signal[FBM_HPF], m_freqClip_min, m_freqClip_max);
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
    float tmpVar, sample;
    tmpVar = _sampleFX * _signal[FBM_FX] + _sampleComb * _signal[FBM_CMB] + _sampleSVF * _signal[FBM_SVF];

    sample  = m_hp_b0 * tmpVar;                  // HP
    sample += m_hp_b1 * m_hp_stateVar_1;
    sample += m_hp_a1 * m_hp_stateVar_2;

    m_hp_stateVar_1 = tmpVar + DNC_const;
    m_hp_stateVar_2 = sample + DNC_const;

    sample *= _signal[FBM_DRV];

    const float hold = sample;
    sample = NlToolbox::Math::sinP3_wrap(sample);
    sample = NlToolbox::Others::threeRanges(sample, hold, _signal[FBM_FLD]);

    tmpVar  = sample * sample;
    tmpVar -= m_hp30hz_stateVar;                // HP 30Hz
    m_hp30hz_stateVar = tmpVar * m_hp30hz_b0 + m_hp30hz_stateVar + NlToolbox::Constants::DNC_const;

    sample = NlToolbox::Others::parAsym(sample, tmpVar, _signal[FBM_ASM]);

    m_out = sample * _signal[FBM_LVL];
}

/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_feedbackmixer::resetDSP()
{
    m_out = 0.f;

    //***************************** 30Hz Highpass ****************************//

    m_hp30hz_stateVar = 0.f;

    //*************************** 1 pole Highpass ****************************//

    m_hp_stateVar_1 = 0.f;
    m_hp_stateVar_2 = 0.f;
}
