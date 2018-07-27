/******************************************************************************/
/** @file           ae_outputmixer.h
    @date           2018-05-09
    @version        1.0
    @author         Anton Schmied
    @brief          Outputmixer
    @todo           Filter auflösen!
*******************************************************************************/

#pragma once

#include "nltoolbox.h"
#include "dsp_defines_signallabels.h"
#include <vector>

struct ae_outputmixer
{
    ae_outputmixer();       // Default Constructor

    float m_out_L, m_out_R;

    float m_hp30_b0;

    std::vector<float> m_hp30_stateVar_L;
    std::vector<float> m_hp30_stateVar_R;

    void init(float _samplerate, uint32_t _numOfVoices);
    void combine(float _sampleA, float _sampleB, float _sampleComb, float _sampleSVFilter, float *_signal, uint32_t _voiceID);
    void filter_level(float *_signal);


    //*************************** Highpass Filters ****************************//
    struct OnePoleHighpassFilter
    {
        float m_inStateVar, m_outStateVar;
        float m_b0, m_b1, m_a1;

        void initFilter(float _samplerate, float _cutFrequency)
        {
            m_inStateVar = 0.f;
            m_outStateVar = 0.f;

            _cutFrequency = _cutFrequency * (3.14159f / _samplerate);
            _cutFrequency = NlToolbox::Math::tan(_cutFrequency);

            m_a1 = (1.f - _cutFrequency) / (1.f + _cutFrequency);
            m_b0 = 1.f / (1.f + _cutFrequency);
            m_b1 = (1.f / (1.f + _cutFrequency)) * -1.f;
        }

        inline float applyFilter(float _sample)
        {
            float tmpVar;

            tmpVar  = m_b0 * _sample;
            tmpVar += m_b1 * m_inStateVar;
            tmpVar += m_a1 * m_outStateVar;

            m_inStateVar  = _sample + DNC_CONST;
            m_outStateVar = tmpVar + DNC_CONST;

            return tmpVar;
        }
    }m_highpass_L, m_highpass_R;
};
