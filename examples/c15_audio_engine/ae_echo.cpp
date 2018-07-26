/******************************************************************************/
/** @file           ae_echo.cpp
    @date           2018-07-26
    @version        1.0
    @author         Anton Schmied
    @brief          Echo
    @todo
*******************************************************************************/


#include "ae_echo.h"

/******************************************************************************/
/** @brief
*******************************************************************************/

ae_echo::ae_echo()
{

}



/******************************************************************************/
/** @brief
*******************************************************************************/
void ae_echo::init(uint32_t _samplerate, uint32_t _upsampleFactor)
{
    m_out_L = 0.f;
    m_out_R = 0.f;

    m_warpConst_PI = pi / static_cast<float>(_samplerate);
    m_freqClip_min = static_cast<float>(_samplerate) / 24000.f;
    m_freqClip_max = static_cast<float>(_samplerate) / 2.18f;


    //*************************** 1 pole Highpass ****************************//
    float omega = NlToolbox::Math::tan(50.f * m_warpConst_PI);
    m_hp_a1 = (1.f - omega) / (1.f + omega);
    m_hp_b0 = 1.f / (1.f + omega);
    m_hp_b1 = (1.f / (1.f + omega)) * -1.f;

    m_hp_stateVar_L1 = 0.f;
    m_hp_stateVar_L2 = 0.f;
    m_hp_stateVar_R1 = 0.f;
    m_hp_stateVar_R2 = 0.f;


    //**************************** 1 pole Lowpass ****************************//
    m_lp_b0 = 0.f;
    m_lp_b1 = 0.f;
    m_lp_a1 = 0.f;

    m_lp_stateVar_L1 = 0.f;
    m_lp_stateVar_L2 = 0.f;
    m_lp_stateVar_R1 = 0.f;
    m_lp_stateVar_R2 = 0.f;


    //****************************** 2Hz Lowpass *****************************//
    m_lp2hz_b0 = 2.f * (twopi / static_cast<float>(_samplerate));
    m_lp2hz_b0 = std::min(m_lp2hz_b0, 1.9f);

    m_lp2hz_stateVar_L = 0.f;
    m_lp2hz_stateVar_R = 0.f;

    //***************************** Delay Buffer *****************************//
    m_stateVar_L = 0.f;
    m_stateVar_R = 0.f;

    m_buffer_indx = 0;
    m_buffer_L.resize(ECHO_BUFFER_SIZE * _upsampleFactor);
    m_buffer_L = {0.f};
    m_buffer_R.resize(ECHO_BUFFER_SIZE * _upsampleFactor);
    m_buffer_R = {0.f};
}



/******************************************************************************/
/** @brief
*******************************************************************************/
void ae_echo::set(float *_signal)
{


}



/******************************************************************************/
/** @brief
*******************************************************************************/
void ae_echo::apply(float _rawSsample_L, float _rawSsample_R, float *_signal)
{


}
