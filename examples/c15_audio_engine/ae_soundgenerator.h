/******************************************************************************/
/** @file           ae_soundgenerator.h
    @date           2018-03-22
    @version        1.0
    @author         Anton Schmied
    @brief          Soundgenerator which contains both Oscillators and Shapers
                    receiving the rendered parameter signals from the
                    param engine
    @todo
*******************************************************************************/

#pragma once

#include <cmath>
#include "nltoolbox.h"
#include "dsp_defines_signallabels.h"

#define test_phase_reset    1       // 0: reset phase only, 1: reset phase, self- & cross-mix, chirp state var

struct ae_soundgenerator
{
    ae_soundgenerator();            // Default Constructor

    float m_out_A, m_out_B;       // Generated Samples

    void init(float _samplerate, uint32_t _vn);
    void generate(float _feedbackSample, float *_signal);
    void set(float *_signal);
    void resetPhase(float _phase);
    void resetDSP();

    //************************** Shared Variables *****************************//
    float m_sample_interval;

    //*********************** Oscillator A Variables **************************//
    float m_oscA_selfmix;
    float m_oscA_crossmix;

    float m_oscA_phase;
    float m_oscA_phase_stateVar;
    float m_oscA_phaseInc;

    int32_t m_OscA_randVal_int;
    float m_OscA_randVal_float;


    //*********************** Oscillator B Variables **************************//
    float m_oscB_selfmix;
    float m_oscB_crossmix;

    float m_oscB_phase;
    float m_oscB_phase_stateVar;
    float m_oscB_phaseInc;

    int32_t m_OscB_randVal_int;
    float m_OscB_randVal_float;

    //***************************** Chirp Filter ******************************//
    float m_warpConst_PI;
    float m_chiA_stateVar, m_chiB_stateVar;

    float m_chiA_omega, m_chiA_a0, m_chiA_a1;
    float m_chiB_omega, m_chiB_a0, m_chiB_a1;
};
