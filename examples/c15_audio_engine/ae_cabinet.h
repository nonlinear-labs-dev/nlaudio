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


    void init(float _samplerate, uint32_t _vn);
    void applyCabinet(float _sample_L, float _sample_R, float *_signal);


    //***************************** Biquad Filters ****************************//
    struct biquadFilter
    {
        float m_warpConst_2PI;
        float m_freqClip_max, m_freqClip_min;

        float m_b0, m_b1, m_b2, m_a0, m_a1, m_a2;

        float m_inStateVar_L1,  m_inStateVar_R1;
        float m_inStateVar_L2,  m_inStateVar_R2;
        float m_outStateVar_L1, m_outStateVar_R1;
        float m_outStateVar_L2, m_outStateVar_R2;

        void init(float _sampleRate)
        {
            m_warpConst_2PI = 6.28319f / _sampleRate;
            m_freqClip_max = _sampleRate / 2.125f;
            m_freqClip_min = _sampleRate / 24576.f;

            m_b0 = 0.f;
            m_b1 = 0.f;
            m_b2 = 0.f;
            m_a0 = 0.f;
            m_a1 = 0.f;
            m_a2 = 0.f;

            m_inStateVar_L1 = 0.f;
            m_inStateVar_L2 = 0.f;
            m_outStateVar_L1 = 0.f;
            m_outStateVar_L2 = 0.f;
            m_inStateVar_R1 = 0.f;
            m_inStateVar_R2 = 0.f;
            m_outStateVar_R1 = 0.f;
            m_outStateVar_R2 = 0.f;
        }

        inline void setLowpassCoeffs(float _cutFreq)
        {
            if (_cutFreq < m_freqClip_min)
            {
                _cutFreq = m_freqClip_min;
            }

            if (_cutFreq > m_freqClip_max)
            {
                _cutFreq = m_freqClip_max;
            }

            _cutFreq *= m_warpConst_2PI;
            float tmpVar = NlToolbox::Math::sin(_cutFreq) * 0.5f;

            m_a0 = 1.f + tmpVar;
            m_a2 = 1.f - tmpVar;

            tmpVar = NlToolbox::Math::sin(_cutFreq);

            m_a1 = tmpVar * -2.f;
            m_b0 = (1.f - tmpVar) / 2.f;
            m_b1 = 1.f - tmpVar;
            m_b2 = m_b0;

        }

        inline void setHighpassCoeffs(float _cutFreq)
        {
            if (_cutFreq < m_freqClip_min)
            {
                _cutFreq = m_freqClip_min;
            }

            if (_cutFreq > m_freqClip_max)
            {
                _cutFreq = m_freqClip_max;
            }

            _cutFreq *= m_warpConst_2PI;
            float tmpVar = NlToolbox::Math::sin(_cutFreq) * 0.5f;

            m_a0 = 1.f + tmpVar;
            m_a2 = 1.f - tmpVar;

            tmpVar = NlToolbox::Math::sin(_cutFreq);

            m_a1 = tmpVar * -2.f;
            m_b0 = (1.f + tmpVar) / 2.f;
            m_b1 = (1.f + tmpVar) * -1.f;
            m_b2 = m_b0;
        }

        inline float applyFilter_L(float _currSample)
        {
            float output;

            output  = m_b0 * _currSample;
            output += m_b1 * m_inStateVar_L1;
            output += m_b2 * m_inStateVar_L2;

            output += m_a1 * m_outStateVar_L1;
            output += m_a2 * m_outStateVar_L2;

            m_inStateVar_L2 = m_inStateVar_L1 + DNC_CONST;
            m_inStateVar_L1 = _currSample  + DNC_CONST;

            m_outStateVar_L2 = m_outStateVar_L1 + DNC_CONST;
            m_outStateVar_L1 = output + DNC_CONST;

            return output;
        }

        inline float applyFilter_R(float _currSample)
        {
            float output;

            output  = m_b0 * _currSample;
            output += m_b1 * m_inStateVar_R1;
            output += m_b2 * m_inStateVar_R2;

            output += m_a1 * m_outStateVar_R1;
            output += m_a2 * m_outStateVar_R2;

            m_inStateVar_R2 = m_inStateVar_R1 + DNC_CONST;
            m_inStateVar_R1 = _currSample  + DNC_CONST;

            m_outStateVar_R2 = m_outStateVar_R1 + DNC_CONST;
            m_outStateVar_R1 = output + DNC_CONST;

            return output;
        }

    }m_biHighpass, m_biLowpass_1, m_biLowpass_2;
};
