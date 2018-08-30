/******************************************************************************/
/** @file           ae_reverb.h
    @date           2018-07-30
    @version        1.0
    @author         Anton Schmied
    @brief          Reverb
    @todo
*******************************************************************************/

#pragma once

#include "pe_defines_config.h"              /// For Smoother Debugging

#include "dsp_defines_signallabels.h"
#include "nltoolbox.h"
#include <vector>

using namespace NlToolbox::Constants;


#define REVERB_BUFFER_SIZE 16384

#define REV_G_1 0.617748f
#define REV_G_2 0.630809f
#define REV_G_3 0.64093f
#define REV_G_4 0.653011f

/*********** Primes - 1 for 48 kHz ***********/
#define REV_DEL_L1 280          // 563
#define REV_DEL_L2 1122         // 2243
#define REV_DEL_L3 862          // 1723
#define REV_DEL_L4 466          // 937
#define REV_DEL_L5 718          // 1439
#define REV_DEL_L6 1030         // 2063
#define REV_DEL_L7 886          // 1777
#define REV_DEL_L8 1216         // 2437
#define REV_DEL_R1 378          // 757
#define REV_DEL_R2 1102         // 2003
#define REV_DEL_R3 928          // 1861
#define REV_DEL_R4 490          // 577
#define REV_DEL_R5 682          // 1361
#define REV_DEL_R6 1018         // 2039
#define REV_DEL_R7 858          // 1721
#define REV_DEL_R8 1366         // 1733

#define REV_DEL_L9 2916         // 5827
#define REV_DEL_R9 2676         // 5351

struct ae_reverb
{
    ae_reverb();        // Default Contructor

    float m_out_L, m_out_R, m_out_FX;

    void init(float _samplerate, uint32_t _upsampleFactor);
    void set(float *_signal);
    void apply(float _rawSample_L, float _rawSample_R, float *_signal, float _fadePoint);
    void resetDSP();

    int32_t m_slow_tick;
    int32_t m_slow_thrsh;

    //************************** Reverb Modulation ***************************//
    float m_mod_1a, m_mod_2a, m_mod_1b, m_mod_2b;
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
    float m_bal_half, m_bal_full;

    int32_t m_buffer_indx;
    int32_t m_buffer_sz_m1, m_buffer_sz_m2;

    float m_preDel_L, m_preDel_R;

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

    float m_stateVar_L1, m_stateVar_R1;
    float m_stateVar_L2, m_stateVar_R2;
    float m_stateVar_L3, m_stateVar_R3;
    float m_stateVar_L4, m_stateVar_R4;
    float m_stateVar_L5, m_stateVar_R5;
    float m_stateVar_L6, m_stateVar_R6;
    float m_stateVar_L7, m_stateVar_R7;
    float m_stateVar_L8, m_stateVar_R8;
    float m_stateVar_L9, m_stateVar_R9;

    //******************************* Smoothing ******************************//
    float m_smooth_inc;

    float m_depth_max, m_depth_min;
    float m_depth_target;
    float m_depth_inc;

    float m_size_max, m_size_min;
    float m_size;
    float m_size_target;
    float m_size_inc;

    float m_bal_max, m_bal_min;
    float m_bal;
    float m_bal_target;
    float m_bal_inc;

    float m_preDel_L_max, m_preDel_L_min;
    float m_preDel_L_target;
    float m_preDel_L_inc;

    float m_preDel_R_max, m_preDel_R_min;
    float m_preDel_R_target;
    float m_preDel_R_inc;

    float m_lp_omega_max, m_lp_omega_min;
    float m_hp_omega_max, m_hp_omega_min;
    float m_lp_omega_target, m_hp_omega_target;
    float m_lp_omega_inc, m_hp_omega_inc;
};
