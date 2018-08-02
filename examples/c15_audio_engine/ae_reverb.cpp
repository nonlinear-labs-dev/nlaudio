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


    //************************** Reverb Modulation ***************************//
    m_lfo_omega_1 = 0.86306f / _samplerate;
    m_lfo_omega_2 = 0.6666f / _samplerate;

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

    m_StateVar_L1 = 0.f;
    m_StateVar_L2 = 0.f;
    m_StateVar_L3 = 0.f;
    m_StateVar_L4 = 0.f;
    m_StateVar_L5 = 0.f;
    m_StateVar_L6 = 0.f;
    m_StateVar_L7 = 0.f;
    m_StateVar_L8 = 0.f;
    m_StateVar_L9 = 0.f;

    m_StateVar_R1 = 0.f;
    m_StateVar_R2 = 0.f;
    m_StateVar_R3 = 0.f;
    m_StateVar_R4 = 0.f;
    m_StateVar_R5 = 0.f;
    m_StateVar_R6 = 0.f;
    m_StateVar_R7 = 0.f;
    m_StateVar_R8 = 0.f;
    m_StateVar_R9 = 0.f;
}



/******************************************************************************/
/** @brief  Chorus
*******************************************************************************/

void ae_reverb::set(float *_signal)
{
    float tmpVar;

    tmpVar = _signal[REV_SIZE];
    m_depth = _signal[REV_CHO] * (tmpVar * -200.f + 311.f);         /// Smoothing??

    tmpVar = tmpVar * (0.5f - std::abs(tmpVar * -0.5f));
    m_absorb  = tmpVar * 0.334f + 0.666f;                           /// Smoothing??
    m_fb_amnt = tmpVar * 0.667f + 0.333f;                           /// Smoothing??

    tmpVar = _signal[REV_PRE];
    m_preDel_time_L = std::round(tmpVar);                           /// Smoothing?
    m_preDel_time_R = std::round(tmpVar * 1.18933f);                /// Smoothing?

    tmpVar = std::clamp(_signal[REV_LPF], 0.1f, m_omegaClip_max);
    m_lp_omega = NlToolbox::Math::tan(tmpVar * m_warpConst_PI);     /// Smoothing??

    m_lp_a0 = 1.f / (m_lp_omega + 1.f);
    m_lp_a1 = m_lp_omega - 1.f;

    tmpVar = std::clamp(_signal[REV_HPF], 0.1f, m_omegaClip_max);
    m_hp_omega = NlToolbox::Math::tan(tmpVar * m_warpConst_PI);     /// Smoothing??

    m_hp_a0 = 1.f / (m_hp_omega + 1.f);
    m_hp_a1 = m_hp_omega - 1.f;
}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_reverb::apply(float _rawSample_L, float _rawSample_R, float *_signal, float _fadePoint)
{
    float tmpVar;
    float mod_1a, mod_2a, mod_1b, mod_2b;
    int32_t ind_t0, ind_tm1, ind_tp1, ind_tp2;
    float wetSample_L, wetSample_R;

    //************************** Reverb Modulation ***************************//
    /// Half Clock!!! Smoothing here!?!?
    ///
    tmpVar = m_lfo_stateVar_1 + m_lfo_omega_1;
    tmpVar = tmpVar - std::round(tmpVar);
    m_lfo_stateVar_1 = tmpVar;

    tmpVar = (8.f - std::abs(tmpVar) * 16.f) * tmpVar;
    tmpVar += 1.f;
    mod_1a = tmpVar * m_depth;
    mod_2a = (1.f - tmpVar) * m_depth;

    tmpVar = m_lfo_stateVar_2 + m_lfo_omega_2;
    tmpVar = tmpVar - std::round(tmpVar);
    m_lfo_stateVar_2 = tmpVar;

    tmpVar = (8.f - std::abs(tmpVar) * 16.f) * tmpVar;
    tmpVar += 1.f;
    mod_1b = tmpVar * m_depth;
    mod_2b = (1.f - tmpVar) * m_depth;



    //***************************** Left Channel *****************************//
    wetSample_L  = _rawSample_L * _signal[REV_FEED];

    wetSample_L *= _fadePoint;                          // Asym
    m_buffer_L[m_buffer_indx] = wetSample_L;

    tmpVar = std::clamp(m_preDel_time_L, 0.f, static_cast<float>(m_buffer_sz_m1));

    ind_t0 = static_cast<int32_t>(std::round(tmpVar - 0.5f));
    tmpVar = tmpVar - static_cast<float>(ind_t0);

    ind_tm1 = ind_t0 - 1;

    ind_t0  = m_buffer_indx - ind_t0;
    ind_tm1 = m_buffer_indx - ind_tm1;

    ind_t0  &= m_buffer_sz_m1;
    ind_tm1 &= m_buffer_sz_m1;

    wetSample_L = m_buffer_L[ind_t0] + tmpVar * (m_buffer_L[ind_tm1] - m_buffer_L[ind_t0]);
    wetSample_L *= _fadePoint;

    wetSample_L += (m_StateVar_L9 * m_fb_amnt);

    wetSample_L = (wetSample_L - m_lp_stateVar_L * m_lp_a1) * m_lp_a0;      // Loop Filter
    tmpVar = m_lp_stateVar_L;
    m_lp_stateVar_L = wetSample_L;

    wetSample_L = (wetSample_L + tmpVar) * m_lp_omega;

    wetSample_L = (wetSample_L - m_hp_stateVar_L * m_hp_a1) * m_hp_a0;
    tmpVar = m_hp_stateVar_L;
    m_hp_stateVar_L = wetSample_L;

    wetSample_L = wetSample_L - tmpVar;


    //**************************** Right Channel *****************************//
    wetSample_R  = _rawSample_R * _signal[REV_FEED];

    wetSample_R *= _fadePoint;                          // Asym
    m_buffer_R[m_buffer_indx] = wetSample_R;

    tmpVar = std::clamp(m_preDel_time_R, 0.f, static_cast<float>(m_buffer_sz_m1));

    ind_t0 = static_cast<int32_t>(std::round(tmpVar - 0.5f));
    tmpVar = tmpVar - static_cast<float>(ind_t0);

    ind_tm1 = ind_t0 - 1;

    ind_t0  = m_buffer_indx - ind_t0;
    ind_tm1 = m_buffer_indx - ind_tm1;

    ind_t0  &= m_buffer_sz_m1;
    ind_tm1 &= m_buffer_sz_m1;

    wetSample_R = m_buffer_R[ind_t0] + tmpVar * (m_buffer_R[ind_tm1] - m_buffer_R[ind_t0]);
    wetSample_R *= _fadePoint;

    wetSample_R += (m_StateVar_R9 * m_fb_amnt);

    wetSample_R = (wetSample_R - m_lp_stateVar_R * m_lp_a1) * m_lp_a0;      // Loop Filter
    tmpVar = m_lp_stateVar_R;
    m_lp_stateVar_R = wetSample_R;

    wetSample_R = (wetSample_R + tmpVar) * m_lp_omega;

    wetSample_R = (wetSample_R - m_hp_stateVar_R * m_hp_a1) * m_hp_a0;
    tmpVar = m_hp_stateVar_R;
    m_hp_stateVar_R = wetSample_R;

    wetSample_R = wetSample_R - tmpVar;


    //**************************** Output Mixer ******************************//
    m_out_L = _rawSample_L * _signal[REV_DRY] + wetSample_L * _signal[REV_WET];
    m_out_R = _rawSample_R * _signal[REV_DRY] + wetSample_R * _signal[REV_WET];

    m_out_FX = ((_rawSample_L + _rawSample_R) * (1.f - _signal[FBM_REV]))
            + ((wetSample_L + wetSample_R) * _signal[FBM_REV]);
}
