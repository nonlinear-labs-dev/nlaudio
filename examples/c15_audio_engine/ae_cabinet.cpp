/******************************************************************************/
/** @file           ae_cabinet.cpp
    @date           2018-07-18
    @version        1.0
    @author         Anton Schmied
    @brief          Cabinet
    @todo
*******************************************************************************/

#include "ae_cabinet.h"

/******************************************************************************/
/** @brief
*******************************************************************************/

ae_cabinet::ae_cabinet()
{

}




/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_cabinet::init(float _samplerate, uint32_t _vn)
{
    m_sampleCabinet_L = 0.f;
    m_sampleCabinet_R = 0.f;

    m_warpConst_2PI = 6.28319f / _samplerate;
    m_freqClip_max = _samplerate / 2.125f;
    m_freqClip_min = _samplerate / 24576.f;

    //*************************** Biquad Highpass ****************************//
    m_hpCoeff_b0 = 0.f;
    m_hpCoeff_b1 = 0.f;
    m_hpCoeff_b2 = 0.f;
    m_hpCoeff_a1 = 0.f;
    m_hpCoeff_a2 = 0.f;

    m_hpInStateVar_L1 = 0.f;
    m_hpInStateVar_R1 = 0.f;
    m_hpInStateVar_L2 = 0.f;
    m_hpInStateVar_R2 = 0.f;;
    m_hpOutStateVar_L1 = 0.f;
    m_hpOutStateVar_R1 = 0.f;
    m_hpOutStateVar_L2 = 0.f;
    m_hpOutStateVar_R2 = 0.f;

    //************************** Biquad Lowpasses ****************************//
    m_lp1Coeff_b0 = 0.f;
    m_lp1Coeff_b1 = 0.f;
    m_lp1Coeff_b2 = 0.f;
    m_lp1Coeff_a1 = 0.f;
    m_lp1Coeff_a2 = 0.f;

    m_lp1InStateVar_L1 = 0.f;
    m_lp1InStateVar_R1 = 0.f;
    m_lp1InStateVar_L2 = 0.f;
    m_lp1InStateVar_R2 = 0.f;
    m_lp1OutStateVar_L1 = 0.f;
    m_lp1OutStateVar_R1 = 0.f;
    m_lp1OutStateVar_L2 = 0.f;
    m_lp1OutStateVar_R2 = 0.f;

    m_lp2Coeff_b0 = 0.f;
    m_lp2Coeff_b1 = 0.f;
    m_lp2Coeff_b2 = 0.f;
    m_lp2Coeff_a1 = 0.f;
    m_lp2Coeff_a2 = 0.f;

    m_lp2InStateVar_L1 = 0.f;
    m_lp2InStateVar_R1 = 0.f;
    m_lp2InStateVar_L2 = 0.f;
    m_lp2InStateVar_R2 = 0.f;
    m_lp2OutStateVar_L1 = 0.f;
    m_lp2OutStateVar_R1 = 0.f;
    m_lp2OutStateVar_L2 = 0.f;
    m_lp2OutStateVar_R2 = 0.f;

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_cabinet::setCabinet(float *_signal, float _samplerate)
{
    //*************************** Biquad Highpass ****************************//
    float frequency = _signal[CAB_HPF];

    if (frequency < m_freqClip_min)
    {
        frequency = m_freqClip_min;
    }

    if (frequency > m_freqClip_max)
    {
        frequency = m_freqClip_max;
    }

    frequency *= m_warpConst_2PI;
    float tmpVar = NlToolbox::Math::cos(frequency);

    m_hpCoeff_a1 = tmpVar * -2.f;
    m_hpCoeff_b0 = (1.f + tmpVar) / 2.f;
    m_hpCoeff_b1 = (1.f + tmpVar) * -1.f;
    m_hpCoeff_b2 = m_hpCoeff_b0;

    tmpVar = NlToolbox::Math::sin(frequency) * 0.5f;

    m_hpCoeff_a2 = 1.f - tmpVar;
    tmpVar = 1.f + tmpVar;

    m_hpCoeff_a1 = m_hpCoeff_a1 * (1.f / tmpVar) * -1.f;
    m_hpCoeff_a2 = m_hpCoeff_a2 * (1.f / tmpVar) * -1.f;
    m_hpCoeff_b0 = m_hpCoeff_b0 * (1.f / tmpVar);
    m_hpCoeff_b1 = m_hpCoeff_b1 * (1.f / tmpVar);
    m_hpCoeff_b2 = m_hpCoeff_b2 * (1.f / tmpVar);

    //*************************** Biquad Lowpass 1 ***************************//
    frequency = _signal[CAB_LPF];

    if (frequency < m_freqClip_min)
    {
        frequency = m_freqClip_min;
    }

    if (frequency > m_freqClip_max)
    {
        frequency = m_freqClip_max;
    }

    frequency *= m_warpConst_2PI;
    tmpVar = NlToolbox::Math::cos(frequency);

    m_lp1Coeff_a1 = tmpVar * -2.f;
    m_lp1Coeff_b0 = (1.f - tmpVar) / 2.f;
    m_lp1Coeff_b1 = 1.f - tmpVar;
    m_lp1Coeff_b2 = m_lp1Coeff_b0;

    tmpVar = NlToolbox::Math::sin(frequency) * 0.5f;

    m_lp1Coeff_a2 = 1.f - tmpVar;
    tmpVar = 1.f + tmpVar;

    m_lp1Coeff_a1 = m_lp1Coeff_a1 * (1.f / tmpVar) * -1.f;
    m_lp1Coeff_a2 = m_lp1Coeff_a2 * (1.f / tmpVar) * -1.f;
    m_lp1Coeff_b0 = m_lp1Coeff_b0 * (1.f / tmpVar);
    m_lp1Coeff_b1 = m_lp1Coeff_b1 * (1.f / tmpVar);
    m_lp1Coeff_b2 = m_lp1Coeff_b2 * (1.f / tmpVar);

    //*************************** Biquad Lowpass 2 ***************************//
    frequency = _signal[CAB_LPF] * 1.333f;

    if (frequency < m_freqClip_min)
    {
        frequency = m_freqClip_min;
    }

    if (frequency > m_freqClip_max)
    {
        frequency = m_freqClip_max;
    }

    frequency *= m_warpConst_2PI;
    tmpVar = NlToolbox::Math::cos(frequency);

    m_lp2Coeff_a1 = tmpVar * -2.f;
    m_lp2Coeff_b0 = (1.f - tmpVar) / 2.f;
    m_lp2Coeff_b1 = 1.f - tmpVar;
    m_lp2Coeff_b2 = m_lp2Coeff_b0;

    tmpVar = NlToolbox::Math::sin(frequency) * 0.5f;

    m_lp2Coeff_a2 = 1.f - tmpVar;
    tmpVar = 1.f + tmpVar;

    m_lp2Coeff_a1 = m_lp2Coeff_a1 * (1.f / tmpVar) * -1.f;
    m_lp2Coeff_a2 = m_lp2Coeff_a2 * (1.f / tmpVar) * -1.f;
    m_lp2Coeff_b0 = m_lp2Coeff_b0 * (1.f / tmpVar);
    m_lp2Coeff_b1 = m_lp2Coeff_b1 * (1.f / tmpVar);
    m_lp2Coeff_b2 = m_lp2Coeff_b2 * (1.f / tmpVar);

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_cabinet::applyCabinet(float _rawSample_L, float _rawSample_R, float *_signal)
{
    float tmpVar;

    //********************************* Drive ********************************//
    float sample_L = _rawSample_L * _signal[CAB_DRV];
    float sample_R = _rawSample_R * _signal[CAB_DRV];


    //************************** Biquad Highpass L ***************************//
    tmpVar  = m_hpCoeff_b0 * sample_L;
    tmpVar += m_hpCoeff_b1 * m_hpInStateVar_L1;
    tmpVar += m_hpCoeff_b2 * m_hpInStateVar_L2;

    tmpVar += m_hpCoeff_a1 * m_hpOutStateVar_L1;
    tmpVar += m_hpCoeff_a2 * m_hpOutStateVar_L2;

    m_hpInStateVar_L2 = m_hpInStateVar_L1 + DNC_CONST;
    m_hpInStateVar_L1 = sample_L  + DNC_CONST;

    m_hpOutStateVar_L2 = m_hpOutStateVar_L1 + DNC_CONST;
    m_hpOutStateVar_L1 = tmpVar + DNC_CONST;

    sample_L = tmpVar;


    //************************** Biquad Highpass R ***************************//
    tmpVar  = m_hpCoeff_b0 * sample_R;
    tmpVar += m_hpCoeff_b1 * m_hpInStateVar_R1;
    tmpVar += m_hpCoeff_b2 * m_hpInStateVar_R2;

    tmpVar += m_hpCoeff_a1 * m_hpOutStateVar_R1;
    tmpVar += m_hpCoeff_a2 * m_hpOutStateVar_R2;

    m_hpInStateVar_R2 = m_hpInStateVar_R1 + DNC_CONST;
    m_hpInStateVar_R1 = sample_R  + DNC_CONST;

    m_hpOutStateVar_R2 = m_hpOutStateVar_R1 + DNC_CONST;
    m_hpOutStateVar_R1 = tmpVar + DNC_CONST;

    sample_R = tmpVar;


    //*************************** Tilt Lowshelf L1 ***************************//
    //*************************** Tilt Lowshelf R1 ***************************//


    //******************************* Shaper L *******************************//

    //******************************* Shaper R *******************************//


    //*************************** Tilt Lowshelf L2 ***************************//
    //*************************** Tilt Lowshelf R2 ***************************//


    //************************* 2 x Biquad Lowpass L *************************//
    tmpVar  = m_lp1Coeff_b0 * sample_L;
    tmpVar += m_lp1Coeff_b1 * m_lp1InStateVar_L1;
    tmpVar += m_lp1Coeff_b2 * m_lp1InStateVar_L2;

    tmpVar += m_lp1Coeff_a1 * m_lp1OutStateVar_L1;
    tmpVar += m_lp1Coeff_a2 * m_lp1OutStateVar_L2;

    m_lp1InStateVar_L2 = m_lp1InStateVar_L1 + DNC_CONST;
    m_lp1InStateVar_L1 = sample_L  + DNC_CONST;

    m_lp1OutStateVar_L2 = m_lp1OutStateVar_L1 + DNC_CONST;
    m_lp1OutStateVar_L1 = tmpVar + DNC_CONST;

    sample_L = tmpVar;

    tmpVar  = m_lp2Coeff_b0 * sample_L;
    tmpVar += m_lp2Coeff_b1 * m_lp2InStateVar_L1;
    tmpVar += m_lp2Coeff_b2 * m_lp2InStateVar_L2;

    tmpVar += m_lp2Coeff_a1 * m_lp2OutStateVar_L1;
    tmpVar += m_lp2Coeff_a2 * m_lp2OutStateVar_L2;

    m_lp2InStateVar_L2 = m_lp2InStateVar_L1 + DNC_CONST;
    m_lp2InStateVar_L1 = sample_L  + DNC_CONST;

    m_lp2OutStateVar_L2 = m_lp2OutStateVar_L1 + DNC_CONST;
    m_lp2OutStateVar_L1 = tmpVar + DNC_CONST;

    sample_L = tmpVar;

    //************************* 2 x Biquad Lowpass R *************************//
    tmpVar  = m_lp1Coeff_b0 * sample_R;
    tmpVar += m_lp1Coeff_b1 * m_lp1InStateVar_R1;
    tmpVar += m_lp1Coeff_b2 * m_lp1InStateVar_R2;

    tmpVar += m_lp1Coeff_a1 * m_lp1OutStateVar_R1;
    tmpVar += m_lp1Coeff_a2 * m_lp1OutStateVar_R2;

    m_lp1InStateVar_R2 = m_lp1InStateVar_R1 + DNC_CONST;
    m_lp1InStateVar_R1 = sample_R  + DNC_CONST;

    m_lp1OutStateVar_R2 = m_lp1OutStateVar_R1 + DNC_CONST;
    m_lp1OutStateVar_R1 = tmpVar + DNC_CONST;

    sample_R = tmpVar;

    tmpVar  = m_lp2Coeff_b0 * sample_R;
    tmpVar += m_lp2Coeff_b1 * m_lp2InStateVar_R1;
    tmpVar += m_lp2Coeff_b2 * m_lp2InStateVar_R2;

    tmpVar += m_lp2Coeff_a1 * m_lp2OutStateVar_R1;
    tmpVar += m_lp2Coeff_a2 * m_lp2OutStateVar_R2;

    m_lp2InStateVar_R2 = m_lp2InStateVar_R1 + DNC_CONST;
    m_lp2InStateVar_R1 = sample_R  + DNC_CONST;

    m_lp2OutStateVar_R2 = m_lp2OutStateVar_R1 + DNC_CONST;
    m_lp2OutStateVar_R1 = tmpVar + DNC_CONST;

    sample_R = tmpVar;

    //******************************* Crossfade ******************************//
    m_sampleCabinet_L = NlToolbox::Crossfades::crossFade(_rawSample_L, sample_L, _signal[CAB_DRY], _signal[CAB_WET]);
    m_sampleCabinet_R = NlToolbox::Crossfades::crossFade(_rawSample_R, sample_R, _signal[CAB_DRY], _signal[CAB_WET]);
}
