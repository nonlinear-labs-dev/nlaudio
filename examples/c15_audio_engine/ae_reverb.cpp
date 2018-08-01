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
/** @brief
*******************************************************************************/

void ae_reverb::apply(float _rawSample_L, float _rawSample_R, float *_signal, float _fadePoint)
{
    float tmpVar;
//    int32_t ind_tm1, ind_t0, ind_tp1, ind_tp2;


    //**************************** Left Channel *****************************//
    tmpVar  = _rawSample_L * 1.f;            ///_signal[REV_FEED]
    tmpVar *= _fadePoint;

    m_buffer_L[m_buffer_indx] = tmpVar;




    //*************************** Right Channel *****************************//
    tmpVar  = _rawSample_R * 1.f;            ///_signal[REV_FEED]
    tmpVar *= _fadePoint;

    m_buffer_R[m_buffer_indx] = tmpVar;

}
