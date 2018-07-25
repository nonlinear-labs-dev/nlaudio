/******************************************************************************/
/** @file           ae_gapfilter.cpp
    @date           2018-07-25
    @version        1.0
    @author         Anton Schmied
    @brief          Gapfilter
    @todo
*******************************************************************************/


#include "ae_gapfilter.h"

/******************************************************************************/
/** @brief
*******************************************************************************/

ae_gapfilter::ae_gapfilter()
{

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_gapfilter::init(float _samplerate, uint32 _vn)
{
    m_gf_out_L = 0.f;
    m_gf_out_R = 0.f;

    m_warpConst_2PI = 6.28319f / _samplerate;
    m_freqClip_max = _samplerate / 2.125f;
    m_freqClip_min = _samplerate / 24576.f;
    m_freqScale_max = _samplerate / 3.f;
    m_freqScale_min = _samplerate / 2.f;

    //************************** Biquad Highpass L/R **************************//
    m_hp_l1_b0 = 0.f;
    m_hp_l1_b1 = 0.f;
    m_hp_l1_a1 = 0.f;
    m_hp_l1_a2 = 0.f;

    m_hp_l2_b0 = 0.f;
    m_hp_l2_b1 = 0.f;
    m_hp_l2_a1 = 0.f;
    m_hp_l2_a2 = 0.f;

    m_hp_l1_stateVar_1 = 0.f;
    m_hp_l1_stateVar_2 = 0.f;
    m_hp_l1_stateVar_3 = 0.f;
    m_hp_l1_stateVar_4 = 0.f;

    m_hp_l2_stateVar_1 = 0.f;
    m_hp_l2_stateVar_2 = 0.f;
    m_hp_l2_stateVar_3 = 0.f;
    m_hp_l2_stateVar_4 = 0.f;

    m_hp_r1_b0 = 0.f;
    m_hp_r1_b1 = 0.f;
    m_hp_r1_a1 = 0.f;
    m_hp_r1_a2 = 0.f;

    m_hp_r2_b0 = 0.f;
    m_hp_r2_b1 = 0.f;
    m_hp_r2_a1 = 0.f;
    m_hp_r2_a2 = 0.f;

    m_hp_r1_stateVar_1 = 0.f;
    m_hp_r1_stateVar_2 = 0.f;
    m_hp_r1_stateVar_3 = 0.f;
    m_hp_r1_stateVar_4 = 0.f;

    m_hp_r2_stateVar_1 = 0.f;
    m_hp_r2_stateVar_2 = 0.f;
    m_hp_r2_stateVar_3 = 0.f;
    m_hp_r2_stateVar_4 = 0.f;

    //*************************** Biquad Lowpass L/R **************************//
    m_lp_l1_b0 = 0.f;
    m_lp_l1_b1 = 0.f;
    m_lp_l1_a1 = 0.f;
    m_lp_l1_a2 = 0.f;

    m_lp_l2_b0 = 0.f;
    m_lp_l2_b1 = 0.f;
    m_lp_l2_a1 = 0.f;
    m_lp_l2_a2 = 0.f;

    m_lp_l1_stateVar_1 = 0.f;
    m_lp_l1_stateVar_2 = 0.f;
    m_lp_l1_stateVar_3 = 0.f;
    m_lp_l1_stateVar_4 = 0.f;

    m_lp_l2_stateVar_1 = 0.f;
    m_lp_l2_stateVar_2 = 0.f;
    m_lp_l2_stateVar_3 = 0.f;
    m_lp_l2_stateVar_4 = 0.f;

    m_lp_r1_b0 = 0.f;
    m_lp_r1_b1 = 0.f;
    m_lp_r1_a1 = 0.f;
    m_lp_r1_a2 = 0.f;

    m_lp_r2_b0 = 0.f;
    m_lp_r2_b1 = 0.f;
    m_lp_r2_a1 = 0.f;
    m_lp_r2_a2 = 0.f;

    m_lp_r1_stateVar_1 = 0.f;
    m_lp_r1_stateVar_2 = 0.f;
    m_lp_r1_stateVar_3 = 0.f;
    m_lp_r1_stateVar_4 = 0.f;

    m_lp_r2_stateVar_1 = 0.f;
    m_lp_r2_stateVar_2 = 0.f;
    m_lp_r2_stateVar_3 = 0.f;
    m_lp_r2_stateVar_4 = 0.f;
}



/******************************************************************************/
/** @brief
*******************************************************************************/
void ae_gapfilter::set(float *_signal, float _samplerate)
{



}
