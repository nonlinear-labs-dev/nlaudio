/******************************************************************************/
/** @file           ae_reverb.h
    @date           2018-07-30
    @version        1.0
    @author         Anton Schmied
    @brief          Reverb
    @todo
*******************************************************************************/

#pragma once

#include "dsp_defines_signallabels.h"
#include "nltoolbox.h"
#include <vector>

using namespace NlToolbox::Constants;


#define REVERB_BUFFER_SIZE 16384

struct ae_reverb
{
    ae_reverb();        // Default Contructor

    float m_out_L, m_out_R, m_out_FX;

    void init(float _samplerate, uint32_t _upsampleFactor);
    void set(float *_signal);
    void apply(float _rawSample_L, float _rawSample_R, float *_signal, float _fadePoint);


    //************************** Reverb Modulation ***************************//
    float m_lfo_omega_1, m_lfo_omega_2;
    float m_lfo_stateVar_1, m_lfo_stateVar_2;
    float m_depth;

    //****************************** Loop Filter *****************************//
    float m_warpConst_PI;
    float m_omegaClip_max;

    float m_lp_a0, m_lp_a1, m_lp_omega;
    float m_hp_a0, m_hp_a1, m_hp_omega;

    float m_lp_stateVar_L, m_lp_stateVar_R;
    float m_hp_stateVar_L, m_hp_stateVar_R;

    //***************************** Delay Buffer *****************************//
    float m_fb_amnt;
    float m_absorb;

    int32_t m_buffer_indx;
    int32_t m_buffer_sz_m1, m_buffer_sz_m2;

    float m_preDel_time_L, m_preDel_time_R;

    std::vector<float> m_buffer_L;
    std::vector<float> m_buffer_R;

    std::vector<float> m_buffer_L1;
    std::vector<float> m_buffer_L2;
    std::vector<float> m_buffer_L3;
    std::vector<float> m_buffer_L4;
    std::vector<float> m_buffer_L5;
    std::vector<float> m_buffer_L6;
    std::vector<float> m_buffer_L7;
    std::vector<float> m_buffer_L8;
    std::vector<float> m_buffer_L9;

    std::vector<float> m_buffer_R1;
    std::vector<float> m_buffer_R2;
    std::vector<float> m_buffer_R3;
    std::vector<float> m_buffer_R4;
    std::vector<float> m_buffer_R5;
    std::vector<float> m_buffer_R6;
    std::vector<float> m_buffer_R7;
    std::vector<float> m_buffer_R8;
    std::vector<float> m_buffer_R9;

    float m_StateVar_L1, m_StateVar_R1;
    float m_StateVar_L2, m_StateVar_R2;
    float m_StateVar_L3, m_StateVar_R3;
    float m_StateVar_L4, m_StateVar_R4;
    float m_StateVar_L5, m_StateVar_R5;
    float m_StateVar_L6, m_StateVar_R6;
    float m_StateVar_L7, m_StateVar_R7;
    float m_StateVar_L8, m_StateVar_R8;
    float m_StateVar_L9, m_StateVar_R9;
};
