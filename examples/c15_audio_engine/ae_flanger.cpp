/******************************************************************************/
/** @file           ae_flanger.cpp
    @date           2018-07-26
    @version        1.0
    @author         Anton Schmied
    @brief          Flanger
    @todo
*******************************************************************************/


#include "ae_flanger.h"

/******************************************************************************/
/** @brief
*******************************************************************************/

ae_flanger::ae_flanger()
{

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_flanger::init(float _samplerate, uint32_t _upsampleFactor)
{
    m_out_L = 0.f;
    m_out_R = 0.f;

    m_warpConst_PI = pi / static_cast<float>(_samplerate);
    m_freqClip_min = static_cast<float>(_samplerate) / 24576.f;
    m_freqClip_max = static_cast<float>(_samplerate) / 2.125f;

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

    m_lp2hz_stateVar_TL = 0.f;
    m_lp2hz_stateVar_TR = 0.f;
    m_lp2hz_stateVar_D  = 0.f;




}
