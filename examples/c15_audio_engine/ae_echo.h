/******************************************************************************/
/** @file           ae_echo.h
    @date           2018-07-26
    @version        1.0
    @author         Anton Schmied
    @brief          Echo
    @todo
*******************************************************************************/

#pragma once

#include "nltoolbox.h"
#include "dsp_defines_signallabels.h"


struct ae_echo
{
    ae_echo();              // Default Constructor

    float m_out_L, m_out_R;

    void init(float _samplerate);
    void apply(float _rawSsample_L, float _rawSsample_R, float *_signal);
    void set(float *_signal);


    //*************************** 1 pole Highpass ****************************//


    //**************************** 1 pole Lowpass ****************************//

    //****************************** 2Hz Lowpass *****************************//





};

#endif // AE_ECHO_H
