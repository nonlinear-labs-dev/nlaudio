/******************************************************************************/
/** @file           ae_cabinet.h
    @date           2018-07-18
    @version        1.0
    @author         Anton Schmied
    @brief          Cabinet
    @todo
*******************************************************************************/

#pragma once

#include "nltoolbox.h"
#include "dsp_defines_signallabels.h"

struct ae_cabinet
{
    ae_cabinet();           // Default Constructor

    float m_sampleCabinet_L, m_sampleCabinet_R;

    float m_warpConst_2PI;
    float m_freqClip_max, m_freqClip_min;

    void init(float _samplerate, uint32_t _vn);
    void applyCabinet(float _rawSample_L, float _rawSample_R, float *_signal);
    void setCabinet(float *_signal, float _samplerate);


    //**************************** Biquad Highpass ****************************//
    float m_hpCoeff_b0, m_hpCoeff_b1, m_hpCoeff_b2;
    float m_hpCoeff_a1, m_hpCoeff_a2;

    float m_hpInStateVar_L1,  m_hpInStateVar_R1;
    float m_hpInStateVar_L2,  m_hpInStateVar_R2;
    float m_hpOutStateVar_L1, m_hpOutStateVar_R1;
    float m_hpOutStateVar_L2, m_hpOutStateVar_R2;

    //***************************** Biquad Lowpass ****************************//
    float m_lp1Coeff_b0, m_lp1Coeff_b1, m_lp1Coeff_b2;
    float m_lp1Coeff_a1, m_lp1Coeff_a2;

    float m_lp1InStateVar_L1,  m_lp1InStateVar_R1;
    float m_lp1InStateVar_L2,  m_lp1InStateVar_R2;
    float m_lp1OutStateVar_L1, m_lp1OutStateVar_R1;
    float m_lp1OutStateVar_L2, m_lp1OutStateVar_R2;

    float m_lp2Coeff_b0, m_lp2Coeff_b1, m_lp2Coeff_b2;
    float m_lp2Coeff_a1, m_lp2Coeff_a2;

    float m_lp2InStateVar_L1,  m_lp2InStateVar_R1;
    float m_lp2InStateVar_L2,  m_lp2InStateVar_R2;
    float m_lp2OutStateVar_L1, m_lp2OutStateVar_R1;
    float m_lp2OutStateVar_L2, m_lp2OutStateVar_R2;
};
