/******************************************************************************/
/** @file           ae_reverb.cpp
    @date           2018-07-30
    @version        1.0
    @author         Anton Schmied
    @brief          Reverb
    @todo
*******************************************************************************/


#include "ae_reverb.h"

/******************************************************************************/
/** @brief
*******************************************************************************/

ae_reverb::ae_reverb()
{

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_reverb::init(float _samplerate, uint32_t _upsampleFactor)
{
    m_out_L = 0.f;
    m_out_R = 0.f;
    m_out_FX = 0.f;

    m_slow_tick = 0;
    m_slow_thrsh = 2 * _upsampleFactor - 1;

    //************************** Reverb Modulation ***************************//
    m_mod_1a = 0.f;
    m_mod_2a = 0.f;
    m_mod_1b = 0.f;
    m_mod_2b = 0.f;
    m_lfo_omega_1 = 0.86306f * 2.f / _samplerate;
    m_lfo_omega_2 = 0.6666f * 2.f / _samplerate;

    //****************************** Loop Filter *****************************//
    m_warpConst_PI = pi / _samplerate;
    m_omegaClip_max = _samplerate / 2.f;

    m_lp_stateVar_L = 0.f;
    m_lp_stateVar_R = 0.f;
    m_hp_stateVar_L = 0.f;
    m_hp_stateVar_R = 0.f;

    //***************************** Delay Buffer *****************************//
    m_buffer_indx = 0;

    m_buffer_sz_m1 = REVERB_BUFFER_SIZE * _upsampleFactor - 1;
    m_buffer_sz_m2 = REVERB_BUFFER_SIZE * _upsampleFactor - 2;

    m_buffer_L.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L1.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L2.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L3.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L4.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L5.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L6.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L7.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L8.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L9.resize(REVERB_BUFFER_SIZE * _upsampleFactor);

    m_buffer_R.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R1.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R2.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R3.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R4.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R5.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R6.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R7.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R8.resize(REVERB_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R9.resize(REVERB_BUFFER_SIZE * _upsampleFactor);

    std::fill(m_buffer_L.begin(), m_buffer_L.end(), 0.f);
    std::fill(m_buffer_L1.begin(), m_buffer_L1.end(), 0.f);
    std::fill(m_buffer_L2.begin(), m_buffer_L2.end(), 0.f);
    std::fill(m_buffer_L3.begin(), m_buffer_L3.end(), 0.f);
    std::fill(m_buffer_L4.begin(), m_buffer_L4.end(), 0.f);
    std::fill(m_buffer_L5.begin(), m_buffer_L5.end(), 0.f);
    std::fill(m_buffer_L6.begin(), m_buffer_L6.end(), 0.f);
    std::fill(m_buffer_L7.begin(), m_buffer_L7.end(), 0.f);
    std::fill(m_buffer_L8.begin(), m_buffer_L8.end(), 0.f);
    std::fill(m_buffer_L9.begin(), m_buffer_L9.end(), 0.f);

    std::fill(m_buffer_R.begin(), m_buffer_R.end(), 0.f);
    std::fill(m_buffer_R1.begin(), m_buffer_R1.end(), 0.f);
    std::fill(m_buffer_R2.begin(), m_buffer_R2.end(), 0.f);
    std::fill(m_buffer_R3.begin(), m_buffer_R3.end(), 0.f);
    std::fill(m_buffer_R4.begin(), m_buffer_R4.end(), 0.f);
    std::fill(m_buffer_R5.begin(), m_buffer_R5.end(), 0.f);
    std::fill(m_buffer_R6.begin(), m_buffer_R6.end(), 0.f);
    std::fill(m_buffer_R7.begin(), m_buffer_R7.end(), 0.f);
    std::fill(m_buffer_R8.begin(), m_buffer_R8.end(), 0.f);
    std::fill(m_buffer_R9.begin(), m_buffer_R9.end(), 0.f);

    m_stateVar_L1 = 0.f;
    m_stateVar_L2 = 0.f;
    m_stateVar_L3 = 0.f;
    m_stateVar_L4 = 0.f;
    m_stateVar_L5 = 0.f;
    m_stateVar_L6 = 0.f;
    m_stateVar_L7 = 0.f;
    m_stateVar_L8 = 0.f;
    m_stateVar_L9 = 0.f;

    m_stateVar_R1 = 0.f;
    m_stateVar_R2 = 0.f;
    m_stateVar_R3 = 0.f;
    m_stateVar_R4 = 0.f;
    m_stateVar_R5 = 0.f;
    m_stateVar_R6 = 0.f;
    m_stateVar_R7 = 0.f;
    m_stateVar_R8 = 0.f;
    m_stateVar_R9 = 0.f;

    //******************************* Smoothing ******************************//
    m_smooth_inc = 1.f / std::max(50.f * (0.001f * _samplerate / 2.f), 1.e-12f);            /// 50ms als DEfine Bitte!
}



/******************************************************************************/
/** @brief  Chorus
*******************************************************************************/

void ae_reverb::set(float *_signal)
{
    float tmpVar;

#if test_reverbSmoother == 1

    tmpVar = _signal[REV_SIZE];
    m_depth_target = _signal[REV_CHO] * (tmpVar * -200.f + 311.f);
    m_depth_inc = (m_depth_target - m_depth) * m_smooth_inc;
    m_depth_max = std::max(m_depth, m_depth_target);
    m_depth_min = std::min(m_depth, m_depth_target);

    m_size_target = tmpVar * (0.5f - std::abs(tmpVar) * -0.5f);
    m_size_inc = (m_size_target - m_size) * m_smooth_inc;
    m_size_max = std::max(m_size, m_size_target);
    m_size_min = std::min(m_size, m_size_target);

    m_bal_target = _signal[REV_BAL];
    m_bal_inc = (m_bal_target - m_bal) * m_smooth_inc;
    m_bal_max = std::max(m_bal, m_bal_target);
    m_bal_min = std::min(m_bal, m_bal_target);

    tmpVar = _signal[REV_PRE];
    m_preDel_L_target = std::round(tmpVar);
    m_preDel_L_inc = (m_preDel_L_target - m_preDel_L) * m_smooth_inc;
    m_preDel_L_max = std::max(m_preDel_L, m_preDel_L_target);
    m_preDel_L_min = std::min(m_preDel_L, m_preDel_L_target);

    m_preDel_R_target = std::round(tmpVar * 1.18933f);
    m_preDel_R_inc = (m_preDel_R_target - m_preDel_R) * m_smooth_inc;
    m_preDel_R_max = std::max(m_preDel_R, m_preDel_R_target);
    m_preDel_R_min = std::min(m_preDel_R, m_preDel_R_target);

    tmpVar = std::clamp(_signal[REV_LPF], 0.1f, m_omegaClip_max);
    m_lp_omega_target = NlToolbox::Math::tan(tmpVar * m_warpConst_PI);
    m_lp_omega_inc = (m_lp_omega_target - m_lp_omega) * m_smooth_inc;
    m_lp_omega_max = std::max(m_lp_omega, m_lp_omega_target);
    m_lp_omega_min = std::min(m_lp_omega, m_lp_omega_target);

    tmpVar = std::clamp(_signal[REV_HPF], 0.1f, m_omegaClip_max);
    m_hp_omega_target = NlToolbox::Math::tan(tmpVar * m_warpConst_PI);
    m_hp_omega_inc = (m_hp_omega_target - m_hp_omega) * m_smooth_inc;
    m_hp_omega_max = std::max(m_hp_omega, m_hp_omega_target);
    m_hp_omega_min = std::min(m_hp_omega, m_hp_omega_target);

#endif

#if test_reverbSmoother == 0
    tmpVar = _signal[REV_SIZE];
    m_depth = _signal[REV_CHO] * (tmpVar * -200.f + 311.f);         /// Smoothing??

    tmpVar = _signal[REV_SIZE];
    tmpVar = tmpVar * (0.5f - std::abs(tmpVar) * -0.5f);            /// Smoothing??
    m_absorb  = tmpVar * 0.334f + 0.666f;
    m_fb_amnt = tmpVar * 0.667f + 0.333f;

    tmpVar = _signal[REV_BAL];                                      /// Smoothing??
    m_bal_full = tmpVar * (2.f - tmpVar);
    tmpVar = 1.f - tmpVar;
    m_bal_half = tmpVar * (2.f - tmpVar);

    tmpVar = _signal[REV_PRE];
    m_preDel_L = std::round(tmpVar);                           /// Smoothing?
    m_preDel_R = std::round(tmpVar * 1.18933f);                /// Smoothing?

    tmpVar = std::clamp(_signal[REV_LPF], 0.1f, m_omegaClip_max);
    m_lp_omega = NlToolbox::Math::tan(tmpVar * m_warpConst_PI);     /// Smoothing??

    m_lp_a0 = 1.f / (m_lp_omega + 1.f);
    m_lp_a1 = m_lp_omega - 1.f;

    tmpVar = std::clamp(_signal[REV_HPF], 0.1f, m_omegaClip_max);
    m_hp_omega = NlToolbox::Math::tan(tmpVar * m_warpConst_PI);     /// Smoothing??

    m_hp_a0 = 1.f / (m_hp_omega + 1.f);
    m_hp_a1 = m_hp_omega - 1.f;
#endif
}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_reverb::apply(float _rawSample_L, float _rawSample_R, float *_signal)
{
    float tmpVar;
    int32_t ind_t0, ind_tm1, ind_tp1, ind_tp2;
    float wetSample_L, wetSample_R;

    //************************** Reverb Modulation ***************************//
    if (!m_slow_tick)
    {
#if test_reverbSmoother == 1
        m_depth = std::clamp(m_depth + m_depth_inc, m_depth_min, m_depth_max);

        m_size = std::clamp(m_size + m_size_inc, m_size_min, m_size_max);
        m_absorb  = m_size * 0.334f + 0.666f;
        m_fb_amnt = m_size * 0.667f + 0.333f;

        m_bal = std::clamp(m_bal + m_bal_inc, m_size_min, m_bal_max);
        tmpVar = m_bal;
        m_bal_full = tmpVar * (2.f - tmpVar);
        tmpVar = 1.f - tmpVar;
        m_bal_half = tmpVar * (2.f - tmpVar);

        m_preDel_L = std::clamp(m_preDel_L + m_preDel_L_inc, m_preDel_L_min, m_preDel_L_max);
        m_preDel_R = std::clamp(m_preDel_R + m_preDel_R_inc, m_preDel_R_min, m_preDel_R_max);

        m_lp_omega = std::clamp(m_lp_omega + m_lp_omega_inc, m_lp_omega_min, m_lp_omega_max);
        m_lp_a0 = 1.f / (m_lp_omega + 1.f);
        m_lp_a1 = m_lp_omega - 1.f;

        m_hp_omega = std::clamp(m_hp_omega + m_hp_omega_inc, m_hp_omega_min, m_hp_omega_max);
        m_hp_a0 = 1.f / (m_hp_omega + 1.f);
        m_hp_a1 = m_hp_omega - 1.f;
#endif

        tmpVar = m_lfo_stateVar_1 + m_lfo_omega_1;
        tmpVar = tmpVar - std::round(tmpVar);
        m_lfo_stateVar_1 = tmpVar;

        tmpVar = (8.f - std::abs(tmpVar) * 16.f) * tmpVar;
        tmpVar += 1.f;
        m_mod_1a = tmpVar * m_depth;
        m_mod_2a = (1.f - tmpVar) * m_depth;

        tmpVar = m_lfo_stateVar_2 + m_lfo_omega_2;
        tmpVar = tmpVar - std::round(tmpVar);
        m_lfo_stateVar_2 = tmpVar;

        tmpVar = (8.f - std::abs(tmpVar) * 16.f) * tmpVar;
        tmpVar += 1.f;
        m_mod_1b = tmpVar * m_depth;
        m_mod_2b = (1.f - tmpVar) * m_depth;
    }

    m_slow_tick = (m_slow_tick + 1) & m_slow_thrsh;

    //************************************************************************//
    //**************************** Left Channel ******************************//
    wetSample_L  = _rawSample_L * _signal[REV_FEED];


    //****************************** Asym 2 L ********************************//
    m_buffer_L[m_buffer_indx] = wetSample_L;

    tmpVar = std::clamp(m_preDel_L, 0.f, static_cast<float>(m_buffer_sz_m1));      /// this can be in a setter!

    ind_t0 = static_cast<int32_t>(std::round(tmpVar - 0.5f));
    tmpVar = tmpVar - static_cast<float>(ind_t0);

    ind_tm1 = ind_t0 + 1;

    ind_t0  = m_buffer_indx - ind_t0;
    ind_tm1 = m_buffer_indx - ind_tm1;

    ind_t0  &= m_buffer_sz_m1;
    ind_tm1 &= m_buffer_sz_m1;

    wetSample_L = m_buffer_L[ind_t0] + tmpVar * (m_buffer_L[ind_tm1] - m_buffer_L[ind_t0]);

    wetSample_L += (m_stateVar_R9 * m_fb_amnt);


    //**************************** Loop Filter L *****************************//
    wetSample_L = (wetSample_L - m_lp_stateVar_L * m_lp_a1) * m_lp_a0;
    tmpVar = m_lp_stateVar_L;
    m_lp_stateVar_L = wetSample_L;

    wetSample_L = (wetSample_L + tmpVar) * m_lp_omega;

    wetSample_L = (wetSample_L - m_hp_stateVar_L * m_hp_a1) * m_hp_a0;
    tmpVar = m_hp_stateVar_L;
    m_hp_stateVar_L = wetSample_L;

    wetSample_L = wetSample_L - tmpVar;


    //****************************** Del 4p L1 *******************************//
    tmpVar = m_stateVar_L1 * m_absorb;
    wetSample_L += (tmpVar * REV_G_1);

    m_buffer_L1[m_buffer_indx] = wetSample_L;

    wetSample_L = wetSample_L * -REV_G_1 + tmpVar;

    tmpVar = REV_DEL_L1 + m_mod_2a;
    tmpVar = std::clamp(tmpVar, 1.f, static_cast<float>(m_buffer_sz_m2));

    ind_t0 = static_cast<int32_t>(std::round(tmpVar - 0.5f));
    tmpVar = tmpVar - static_cast<float>(ind_t0);

    ind_tm1 = std::max(ind_t0, 1) - 1;
    ind_tp1 = ind_t0 + 1;
    ind_tp2 = ind_t0 + 2;

    ind_tm1 = m_buffer_indx - ind_tm1;
    ind_t0  = m_buffer_indx - ind_t0;
    ind_tp1 = m_buffer_indx - ind_tp1;
    ind_tp2 = m_buffer_indx - ind_tp2;

    ind_tm1 &= m_buffer_sz_m1;
    ind_t0  &= m_buffer_sz_m1;
    ind_tp1 &= m_buffer_sz_m1;
    ind_tp2 &= m_buffer_sz_m1;

    m_stateVar_L1 = NlToolbox::Math::interpolRT(tmpVar,
                                                m_buffer_L1[ind_tm1],
                                                m_buffer_L1[ind_t0],
                                                m_buffer_L1[ind_tp1],
                                                m_buffer_L1[ind_tp2]);


    //***************************** Del 1p L2 ******************************//
    tmpVar = m_stateVar_L2 * m_absorb;
    wetSample_L = wetSample_L + (tmpVar * REV_G_2);

    m_buffer_L2[m_buffer_indx] = wetSample_L;

    wetSample_L = wetSample_L * -REV_G_2 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_L2;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_L2 = m_buffer_L2[ind_t0];


    //***************************** Del 1p L3 ******************************//
    tmpVar = m_stateVar_L3 * m_absorb;
    wetSample_L = wetSample_L + (tmpVar * REV_G_3);

    m_buffer_L3[m_buffer_indx] = wetSample_L;

    wetSample_L = wetSample_L * -REV_G_3 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_L3;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_L3 = m_buffer_L3[ind_t0];


    //***************************** Del 1p L4 ******************************//
    tmpVar = m_stateVar_L4 * m_absorb;
    wetSample_L = wetSample_L + (tmpVar * REV_G_4);

    m_buffer_L4[m_buffer_indx] = wetSample_L;

    float wetSample_L2 = wetSample_L * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_L4;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_L4 = m_buffer_L4[ind_t0];


    //***************************** Del 1p L5 ******************************//
    tmpVar = m_stateVar_L5 * m_absorb;
    wetSample_L = wetSample_L2 + (tmpVar * REV_G_4);

    m_buffer_L5[m_buffer_indx] = wetSample_L;

    wetSample_L = wetSample_L * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_L5;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_L5 = m_buffer_L5[ind_t0];


    //***************************** Del 1p L6 ******************************//
    tmpVar = m_stateVar_L6 * m_absorb;
    wetSample_L = wetSample_L + (tmpVar * REV_G_4);

    m_buffer_L6[m_buffer_indx] = wetSample_L;

    wetSample_L = wetSample_L * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_L6;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_L6 = m_buffer_L6[ind_t0];


    //***************************** Del 1p L7 ******************************//
    tmpVar = m_stateVar_L7 * m_absorb;
    wetSample_L = wetSample_L + (tmpVar * REV_G_4);

    m_buffer_L7[m_buffer_indx] = wetSample_L;

    wetSample_L = wetSample_L * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_L7;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_L7 = m_buffer_L7[ind_t0];


    //***************************** Del 1p L8 ******************************//
    tmpVar = m_stateVar_L8 * m_absorb;
    wetSample_L = wetSample_L + (tmpVar * REV_G_4);

    m_buffer_L8[m_buffer_indx] = wetSample_L;

    wetSample_L = wetSample_L * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_L8;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_L8 = m_buffer_L8[ind_t0];


    //************************************************************************//
    //*************************** Right Channel ******************************//
    wetSample_R  = _rawSample_R * _signal[REV_FEED];


    //****************************** Asym 2 R ********************************//
    m_buffer_R[m_buffer_indx] = wetSample_R;

    tmpVar = std::clamp(m_preDel_R, 0.f, static_cast<float>(m_buffer_sz_m1));

    ind_t0 = static_cast<int32_t>(std::round(tmpVar - 0.5f));
    tmpVar = tmpVar - static_cast<float>(ind_t0);

    ind_tm1 = ind_t0 + 1;

    ind_t0  = m_buffer_indx - ind_t0;
    ind_tm1 = m_buffer_indx - ind_tm1;

    ind_t0  &= m_buffer_sz_m1;
    ind_tm1 &= m_buffer_sz_m1;

    wetSample_R = m_buffer_R[ind_t0] + tmpVar * (m_buffer_R[ind_tm1] - m_buffer_R[ind_t0]);

    wetSample_R += (m_stateVar_L9 * m_fb_amnt);


    //**************************** Loop Filter R *****************************//
    wetSample_R = (wetSample_R - m_lp_stateVar_R * m_lp_a1) * m_lp_a0;
    tmpVar = m_lp_stateVar_R;
    m_lp_stateVar_R = wetSample_R;

    wetSample_R = (wetSample_R + tmpVar) * m_lp_omega;

    wetSample_R = (wetSample_R - m_hp_stateVar_R * m_hp_a1) * m_hp_a0;
    tmpVar = m_hp_stateVar_R;
    m_hp_stateVar_R = wetSample_R;

    wetSample_R = wetSample_R - tmpVar;


    //****************************** Del 4p R1 *******************************//
    tmpVar = m_stateVar_R1 * m_absorb;
    wetSample_R += (tmpVar * REV_G_1);

    m_buffer_R1[m_buffer_indx] = wetSample_R;

    wetSample_R = wetSample_R * -REV_G_1 + tmpVar;

    tmpVar = REV_DEL_R1 + m_mod_2b;
    tmpVar = std::clamp(tmpVar, 1.f, static_cast<float>(m_buffer_sz_m2));

    ind_t0 = static_cast<int32_t>(std::round(tmpVar - 0.5f));
    tmpVar = tmpVar - static_cast<float>(ind_t0);

    ind_tm1 = std::max(ind_t0, 1) - 1;
    ind_tp1 = ind_t0 + 1;
    ind_tp2 = ind_t0 + 2;

    ind_tm1 = m_buffer_indx - ind_tm1;
    ind_t0  = m_buffer_indx - ind_t0;
    ind_tp1 = m_buffer_indx - ind_tp1;
    ind_tp2 = m_buffer_indx - ind_tp2;

    ind_tm1 &= m_buffer_sz_m1;
    ind_t0  &= m_buffer_sz_m1;
    ind_tp1 &= m_buffer_sz_m1;
    ind_tp2 &= m_buffer_sz_m1;

    m_stateVar_R1 = NlToolbox::Math::interpolRT(tmpVar,
                                                m_buffer_R1[ind_tm1],
                                                m_buffer_R1[ind_t0],
                                                m_buffer_R1[ind_tp1],
                                                m_buffer_R1[ind_tp2]);


    //***************************** Del 1p R2 ******************************//
    tmpVar = m_stateVar_R2 * m_absorb;
    wetSample_R = wetSample_R + (tmpVar * REV_G_2);

    m_buffer_R2[m_buffer_indx] = wetSample_R;

    wetSample_R = wetSample_R * -REV_G_2 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_R2;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_R2 = m_buffer_R2[ind_t0];


    //***************************** Del 1p R3 ******************************//
    tmpVar = m_stateVar_R3 * m_absorb;
    wetSample_R = wetSample_R + (tmpVar * REV_G_3);

    m_buffer_R3[m_buffer_indx] = wetSample_R;

    wetSample_R = wetSample_R * -REV_G_3 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_R3;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_R3 = m_buffer_R3[ind_t0];


    //***************************** Del 1p R4 ******************************//
    tmpVar = m_stateVar_R4 * m_absorb;
    wetSample_R = wetSample_R + (tmpVar * REV_G_4);

    m_buffer_R4[m_buffer_indx] = wetSample_R;

    float wetSample_R2 = wetSample_R * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_R4;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_R4 = m_buffer_R4[ind_t0];


    //***************************** Del 1p R5 ******************************//
    tmpVar = m_stateVar_R5 * m_absorb;
    wetSample_R = wetSample_R2 + (tmpVar * REV_G_4);

    m_buffer_R5[m_buffer_indx] = wetSample_R;

    wetSample_R = wetSample_R * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_R5;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_R5 = m_buffer_R5[ind_t0];



    //***************************** Del 1p R6 ******************************//
    tmpVar = m_stateVar_R6 * m_absorb;
    wetSample_R = wetSample_R + (tmpVar * REV_G_4);

    m_buffer_R6[m_buffer_indx] = wetSample_R;

    wetSample_R = wetSample_R * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_R6;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_R6 = m_buffer_R6[ind_t0];


    //***************************** Del 1p R7 ******************************//
    tmpVar = m_stateVar_R7 * m_absorb;
    wetSample_R = wetSample_R + (tmpVar * REV_G_4);

    m_buffer_R7[m_buffer_indx] = wetSample_R;

    wetSample_R = wetSample_R * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_R7;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_R7 = m_buffer_R7[ind_t0];


    //***************************** Del 1p R8 ******************************//
    tmpVar = m_stateVar_R8 * m_absorb;
    wetSample_R = wetSample_R + (tmpVar * REV_G_4);

    m_buffer_R8[m_buffer_indx] = wetSample_R;

    wetSample_R = wetSample_R * -REV_G_4 + tmpVar;

    ind_t0  = m_buffer_indx - REV_DEL_R8;
    ind_t0 &= m_buffer_sz_m1;

    m_stateVar_R8 = m_buffer_R8[ind_t0];


    //************************************************************************//
    //*************************** Feedback Delay *****************************//
    //****************************** Del 4p L9 *******************************//
    m_buffer_L9[m_buffer_indx] = wetSample_L;

    tmpVar = REV_DEL_L9 + m_mod_1a;
    tmpVar = std::clamp(tmpVar, 0.f, static_cast<float>(m_buffer_sz_m2));

    ind_t0 = static_cast<int32_t>(std::round(tmpVar - 0.5f));
    tmpVar = tmpVar - static_cast<float>(ind_t0);

    ind_tm1 = std::max(ind_t0, 1) - 1;
    ind_tp1 = ind_t0 + 1;
    ind_tp2 = ind_t0 + 2;

    ind_tm1 = m_buffer_indx - ind_tm1;
    ind_t0  = m_buffer_indx - ind_t0;
    ind_tp1 = m_buffer_indx - ind_tp1;
    ind_tp2 = m_buffer_indx - ind_tp2;

    ind_tm1 &= m_buffer_sz_m1;
    ind_t0  &= m_buffer_sz_m1;
    ind_tp1 &= m_buffer_sz_m1;
    ind_tp2 &= m_buffer_sz_m1;

    m_stateVar_L9 = NlToolbox::Math::interpolRT(tmpVar,
                                                m_buffer_L9[ind_tm1],
                                                m_buffer_L9[ind_t0],
                                                m_buffer_L9[ind_tp1],
                                                m_buffer_L9[ind_tp2]);


    //***************************** Del 4p R9 ******************************//
    m_buffer_R9[m_buffer_indx] = wetSample_R;

    tmpVar = REV_DEL_R9 + m_mod_1b;
    tmpVar = std::clamp(tmpVar, 0.f, static_cast<float>(m_buffer_sz_m2));

    ind_t0 = static_cast<int32_t>(std::round(tmpVar - 0.5f));
    tmpVar = tmpVar - static_cast<float>(ind_t0);

    ind_tm1 = std::max(ind_t0, 1) - 1;
    ind_tp1 = ind_t0 + 1;
    ind_tp2 = ind_t0 + 2;

    ind_tm1 = m_buffer_indx - ind_tm1;
    ind_t0  = m_buffer_indx - ind_t0;
    ind_tp1 = m_buffer_indx - ind_tp1;
    ind_tp2 = m_buffer_indx - ind_tp2;

    ind_tm1 &= m_buffer_sz_m1;
    ind_t0  &= m_buffer_sz_m1;
    ind_tp1 &= m_buffer_sz_m1;
    ind_tp2 &= m_buffer_sz_m1;

    m_stateVar_R9 = NlToolbox::Math::interpolRT(tmpVar,
                                                m_buffer_R9[ind_tm1],
                                                m_buffer_R9[ind_t0],
                                                m_buffer_R9[ind_tp1],
                                                m_buffer_R9[ind_tp2]);

    m_buffer_indx = (m_buffer_indx + 1) & m_buffer_sz_m1;


    //************************************************************************//
    //**************************** Output Mixer ******************************//
    wetSample_L = wetSample_L * m_bal_full + wetSample_L2 * m_bal_half;
    wetSample_R = wetSample_R * m_bal_full + wetSample_R2 * m_bal_half;

    m_out_L = _rawSample_L * _signal[REV_DRY] + wetSample_L * _signal[REV_WET];
    m_out_R = _rawSample_R * _signal[REV_DRY] + wetSample_R * _signal[REV_WET];

    m_out_FX = ((_rawSample_L + _rawSample_R) * (1.f - _signal[FBM_REV]))
            + ((wetSample_L + wetSample_R) * _signal[FBM_REV]);
}

/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_reverb::resetDSP()
{
    m_out_L = 0.f;
    m_out_R = 0.f;
    m_out_FX = 0.f;

    //****************************** Loop Filter *****************************//

    m_lp_stateVar_L = 0.f;
    m_lp_stateVar_R = 0.f;
    m_hp_stateVar_L = 0.f;
    m_hp_stateVar_R = 0.f;

    //***************************** Delay Buffer *****************************//

    std::fill(m_buffer_L.begin(), m_buffer_L.end(), 0.f);
    std::fill(m_buffer_L1.begin(), m_buffer_L1.end(), 0.f);
    std::fill(m_buffer_L2.begin(), m_buffer_L2.end(), 0.f);
    std::fill(m_buffer_L3.begin(), m_buffer_L3.end(), 0.f);
    std::fill(m_buffer_L4.begin(), m_buffer_L4.end(), 0.f);
    std::fill(m_buffer_L5.begin(), m_buffer_L5.end(), 0.f);
    std::fill(m_buffer_L6.begin(), m_buffer_L6.end(), 0.f);
    std::fill(m_buffer_L7.begin(), m_buffer_L7.end(), 0.f);
    std::fill(m_buffer_L8.begin(), m_buffer_L8.end(), 0.f);
    std::fill(m_buffer_L9.begin(), m_buffer_L9.end(), 0.f);

    std::fill(m_buffer_R.begin(), m_buffer_R.end(), 0.f);
    std::fill(m_buffer_R1.begin(), m_buffer_R1.end(), 0.f);
    std::fill(m_buffer_R2.begin(), m_buffer_R2.end(), 0.f);
    std::fill(m_buffer_R3.begin(), m_buffer_R3.end(), 0.f);
    std::fill(m_buffer_R4.begin(), m_buffer_R4.end(), 0.f);
    std::fill(m_buffer_R5.begin(), m_buffer_R5.end(), 0.f);
    std::fill(m_buffer_R6.begin(), m_buffer_R6.end(), 0.f);
    std::fill(m_buffer_R7.begin(), m_buffer_R7.end(), 0.f);
    std::fill(m_buffer_R8.begin(), m_buffer_R8.end(), 0.f);
    std::fill(m_buffer_R9.begin(), m_buffer_R9.end(), 0.f);

    m_stateVar_L1 = 0.f;
    m_stateVar_L2 = 0.f;
    m_stateVar_L3 = 0.f;
    m_stateVar_L4 = 0.f;
    m_stateVar_L5 = 0.f;
    m_stateVar_L6 = 0.f;
    m_stateVar_L7 = 0.f;
    m_stateVar_L8 = 0.f;
    m_stateVar_L9 = 0.f;

    m_stateVar_R1 = 0.f;
    m_stateVar_R2 = 0.f;
    m_stateVar_R3 = 0.f;
    m_stateVar_R4 = 0.f;
    m_stateVar_R5 = 0.f;
    m_stateVar_R6 = 0.f;
    m_stateVar_R7 = 0.f;
    m_stateVar_R8 = 0.f;
    m_stateVar_R9 = 0.f;
}
