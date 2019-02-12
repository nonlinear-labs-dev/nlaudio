/******************************************************************************/
/** @file           ae_soundgenerator.cpp
    @date           2018-03-22
    @version        1.0
    @author         Anton Schmied
    @brief          Soundgenerator which contains both Oscillators and Shapers
                    receiving the rendered parameter signals from the
                    param engine
    @todo
*******************************************************************************/

#include "ae_soundgenerator.h"

/******************************************************************************/
/** @brief
*******************************************************************************/

ae_soundgenerator::ae_soundgenerator()
{

}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_soundgenerator::init(float _samplerate, uint32_t _vn)
{
    m_out_A = 0.f;
    m_out_B = 0.f;

    m_sample_interval = 1.f / _samplerate;
    m_warpConst_PI = 3.14159f / _samplerate;

    m_feedback_phase = 0.f;

    m_chiA_stateVar = 0.f;
    m_chiB_stateVar = 0.f;

    m_chiA_omega = 0.f;
    m_chiA_a0 = 0.f;
    m_chiA_a1 = 0.f;
    m_chiB_omega = 0.f;
    m_chiB_a0 = 0.f;
    m_chiB_a1 = 0.f;

    m_OscA_randVal_int = static_cast<int32_t>(_vn) + 1;
    m_OscB_randVal_int = static_cast<int32_t>(_vn) + 1 + 111;

    m_OscA_mute = 0;
    m_OscB_mute = 0;

}



/******************************************************************************/
/** @brief
*******************************************************************************/
void ae_soundgenerator::set(float *_signal)
{
    //*************************** Chirp Filter A *****************************//
    m_chiA_omega = _signal[OSC_A_CHI] * m_warpConst_PI;
    m_chiA_omega = NlToolbox::Math::tan(m_chiA_omega);

    m_chiA_a0 = 1.f / (m_chiA_omega + 1.f);
    m_chiA_a1 = m_chiA_omega - 1.f;

    //*************************** Chirp Filter B *****************************//
    m_chiB_omega = _signal[OSC_B_CHI] * m_warpConst_PI;
    m_chiB_omega = NlToolbox::Math::tan(m_chiB_omega);

    m_chiB_a0 = 1.f / (m_chiB_omega + 1.f);
    m_chiB_a1 = m_chiB_omega - 1.f;
}



/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_soundgenerator::resetPhase(float _phase)
{
   m_oscA_phase = _phase;
   m_oscB_phase = _phase;
#if test_phase_reset == 1
   /* */
   m_oscA_selfmix = 0.f;
   m_oscA_crossmix = 0.f;
   m_chiA_stateVar = 0.f;
   /* */
   m_oscB_selfmix = 0.f;
   m_oscB_crossmix = 0.f;
   m_chiB_stateVar = 0.f;
   /* */
   m_feedback_phase = 0.f;
#endif
}



/******************************************************************************/
/** @brief      version 1
*******************************************************************************/
#if 0
void ae_soundgenerator::generate_1(float _feedbackSample, float *_signal)
{
    float tmpVar;

    //**************************** Modulation A ******************************//
    float oscSampleA = m_oscA_selfmix * _signal[OSC_A_PMSEA];
    oscSampleA = oscSampleA + m_oscB_crossmix * _signal[OSC_A_PMBEB];
    oscSampleA = oscSampleA + m_feedback_phase * _signal[OSC_A_PMFEC];


    //**************************** Oscillator A ******************************//
    oscSampleA -= (m_chiA_a1 * m_chiA_stateVar);                // Chirp IIR
    oscSampleA *= m_chiA_a0;

    tmpVar = oscSampleA;

    oscSampleA = (oscSampleA + m_chiA_stateVar) * m_chiA_omega; // Chirp FIR
    m_chiA_stateVar = tmpVar + NlToolbox::Constants::DNC_const;

    oscSampleA += m_oscA_phase;

    oscSampleA += _signal[OSC_A_PHS] + _signal[UN_PHS];             // NEW Phase Offset
    oscSampleA += (-0.25f);                                         // Wrap
    oscSampleA -= NlToolbox::Conversion::float2int(oscSampleA);

    if (std::abs(m_oscA_phase_stateVar - oscSampleA) > 0.5f)            // Check edge
    {
        m_OscA_randVal_int = m_OscA_randVal_int * 1103515245 + 12345;
        m_OscA_randVal_float = static_cast<float>(m_OscA_randVal_int) * 4.5657e-10f;
    }

    float osc_freq = _signal[OSC_A_FRQ];
    m_oscA_phaseInc = ((m_OscA_randVal_float * _signal[OSC_A_FLUEC] * osc_freq) + osc_freq) * m_sample_interval;

    m_oscA_phase_stateVar = oscSampleA;

    m_oscA_phase += m_oscA_phaseInc;
    m_oscA_phase -= NlToolbox::Conversion::float2int(m_oscA_phase);

    oscSampleA = m_mute_state[m_OscA_mute] * NlToolbox::Math::sinP3_noWrap(oscSampleA);


    //**************************** Modulation B ******************************//
    float oscSampleB = m_oscB_selfmix * _signal[OSC_B_PMSEB];
    oscSampleB = oscSampleB + m_oscA_crossmix * _signal[OSC_B_PMAEA];
    oscSampleB = oscSampleB + m_feedback_phase * _signal[OSC_B_PMFEC];


    //**************************** Oscillator B ******************************//
    oscSampleB -= (m_chiB_a1 * m_chiB_stateVar);                // Chirp IIR
    oscSampleB *= m_chiB_a0;

    tmpVar = oscSampleB;

    oscSampleB = (oscSampleB + m_chiB_stateVar) * m_chiB_omega; // Chirp FIR
    m_chiB_stateVar = tmpVar + NlToolbox::Constants::DNC_const;

    oscSampleB += m_oscB_phase;

    oscSampleB += _signal[OSC_B_PHS] + _signal[UN_PHS];         // NEW Phase Offset
    oscSampleB += (-0.25f);                                     // Warp
    oscSampleB -= NlToolbox::Conversion::float2int(oscSampleB);

    if (std::abs(m_oscB_phase_stateVar - oscSampleB) > 0.5f)    // Check edge
    {
        m_OscB_randVal_int = m_OscB_randVal_int * 1103515245 + 12345;
        m_OscB_randVal_float = static_cast<float>(m_OscB_randVal_int) * 4.5657e-10f;
    }

    osc_freq = _signal[OSC_B_FRQ];
    m_oscB_phaseInc = ((m_OscB_randVal_float * _signal[OSC_B_FLUEC] * osc_freq) + osc_freq) * m_sample_interval;

    m_oscB_phase_stateVar = oscSampleB;

    m_oscB_phase += m_oscB_phaseInc;
    m_oscB_phase -=  NlToolbox::Conversion::float2int(m_oscB_phase);

    oscSampleB = m_mute_state[m_OscB_mute] * NlToolbox::Math::sinP3_noWrap(oscSampleB);


    //******************************* Shaper A *******************************//
    float shaperSampleA = oscSampleA * _signal[SHP_A_DRVEA];
    tmpVar = shaperSampleA;

    shaperSampleA = NlToolbox::Math::sinP3_wrap(shaperSampleA);
    shaperSampleA = NlToolbox::Others::threeRanges(shaperSampleA, tmpVar, _signal[SHP_A_FLD]);

    tmpVar = shaperSampleA * shaperSampleA + (-0.5f);

    shaperSampleA = NlToolbox::Others::parAsym(shaperSampleA, tmpVar, _signal[SHP_A_ASM]);


    //******************************* Shaper B *******************************//
    float shaperSampleB = oscSampleB * _signal[SHP_B_DRVEB];
    tmpVar = shaperSampleB;

    shaperSampleB = NlToolbox::Math::sinP3_wrap(shaperSampleB);
    shaperSampleB = NlToolbox::Others::threeRanges(shaperSampleB, tmpVar, _signal[SHP_B_FLD]);

    tmpVar = shaperSampleB * shaperSampleB + (-0.5f);

    shaperSampleB = NlToolbox::Others::parAsym(shaperSampleB, tmpVar, _signal[SHP_B_ASM]);

    //****************************** Crossfades ******************************//
    m_oscA_selfmix  = NlToolbox::Crossfades::bipolarCrossFade(oscSampleA, shaperSampleA, _signal[OSC_A_PMSSH]);
    m_oscA_crossmix = NlToolbox::Crossfades::bipolarCrossFade(oscSampleA, shaperSampleA, _signal[OSC_B_PMASH]);

    m_oscB_selfmix  = NlToolbox::Crossfades::bipolarCrossFade(oscSampleB, shaperSampleB, _signal[OSC_B_PMSSH]);
    m_oscB_crossmix = NlToolbox::Crossfades::bipolarCrossFade(oscSampleB, shaperSampleB, _signal[OSC_A_PMBSH]);

    float sample_A = NlToolbox::Crossfades::bipolarCrossFade(oscSampleA, shaperSampleA, _signal[SHP_A_MIX]);
    float sample_B = NlToolbox::Crossfades::bipolarCrossFade(oscSampleB, shaperSampleB, _signal[SHP_B_MIX]);


    //******************* Envelope Influence (Magnitudes) ********************//
    sample_A *= _signal[ENV_A_MAG];
    sample_B *= _signal[ENV_B_MAG];


    //**************************** Feedback Mix ******************************//
    tmpVar = _feedbackSample * _signal[SHP_A_FBEC];
    sample_A = NlToolbox::Crossfades::unipolarCrossFade(sample_A, tmpVar, _signal[SHP_A_FBM]);

    tmpVar = _feedbackSample * _signal[SHP_B_FBEC];
    sample_B = NlToolbox::Crossfades::unipolarCrossFade(sample_B, tmpVar, _signal[SHP_B_FBM]);


    //************************** Ring Modulation *****************************//
    tmpVar = sample_A * sample_B;

    m_out_A = NlToolbox::Crossfades::unipolarCrossFade(sample_A, tmpVar, _signal[SHP_A_RM]);
    m_out_B = NlToolbox::Crossfades::unipolarCrossFade(sample_B, tmpVar, _signal[SHP_B_RM]);

}
#endif

/******************************************************************************/
/** @brief version 2
*******************************************************************************/

void ae_soundgenerator::generate_2(float _feedbackSample, float *_signal)
{
    //************************ Get From Siganl Array **************************//
    const float env_a_mag   = _signal[ENV_A_MAG];
    const float env_b_mag   = _signal[ENV_B_MAG];

    const float osc_a_frq   = _signal[OSC_A_FRQ];
    const float osc_a_fluec = _signal[OSC_A_FLUEC];
    const float modVarA_1   = m_oscA_selfmix * _signal[OSC_A_PMSEA];
    const float osc_a_pmssh = _signal[OSC_A_PMSSH];
    const float modVarA_2   = m_oscB_crossmix * _signal[OSC_A_PMBEB];
    const float osc_a_pmbsh = _signal[OSC_A_PMBSH];
    const float modVarA_3   = m_feedback_phase * _signal[OSC_A_PMFEC];
    const float osc_a_phs   = _signal[OSC_A_PHS];

    const float shp_a_drvea = _signal[SHP_A_DRVEA];
    const float shp_a_fld   = _signal[SHP_A_FLD];
    const float shp_a_asm   = _signal[SHP_A_ASM];
    const float shp_a_mix   = _signal[SHP_A_MIX];
    const float shp_a_fbm   = _signal[SHP_A_FBM];
    const float shp_a_fbec  = _signal[SHP_A_FBEC];
    const float shp_a_rm    = _signal[SHP_A_RM];


    const float osc_b_frq   = _signal[OSC_B_FRQ];
    const float osc_b_fluec = _signal[OSC_B_FLUEC];
    const float modVarB_1   = m_oscB_selfmix * _signal[OSC_B_PMSEB];
    const float osc_b_pmssh = _signal[OSC_B_PMSSH];
    const float modVarB_2   = m_oscA_crossmix * _signal[OSC_B_PMAEA];
    const float osc_b_pmash = _signal[OSC_B_PMASH];
    const float modVarB_3   = m_feedback_phase * _signal[OSC_B_PMFEC];
    const float osc_b_phs   = _signal[OSC_B_PHS];

    const float shp_b_drveb = _signal[SHP_B_DRVEB];
    const float shp_b_fld   = _signal[SHP_B_FLD];
    const float shp_b_asm   = _signal[SHP_B_ASM];
    const float shp_b_mix   = _signal[SHP_B_MIX];
    const float shp_b_fbm   = _signal[SHP_B_FBM];
    const float shp_b_fbec  = _signal[SHP_B_FBEC];
    const float shp_b_rm    = _signal[SHP_B_RM];

    const float un_phs = _signal[UN_PHS];


    //**************************** Modulation A ******************************//
    const float modSampleA = modVarA_1 + modVarA_2 + modVarA_3;


    //**************************** Oscillator A ******************************//
    const float chirpIIRSampleA = (modSampleA - m_chiA_a1 * m_chiA_stateVar) * m_chiA_a0; // Chirp IIR
    const float holdChirpA = chirpIIRSampleA;

    const float chirpFIRSampleA = (chirpIIRSampleA + m_chiA_stateVar) * m_chiA_omega;       // Chirp FIR
    m_chiA_stateVar = holdChirpA + NlToolbox::Constants::DNC_const;

    const float phsA = m_oscA_phase + osc_a_phs + un_phs + (-0.25f);
    const float phsSampleA_1 = chirpFIRSampleA + phsA;
    const float phsSampleA_2 = phsSampleA_1 - NlToolbox::Conversion::float2int(phsSampleA_1);

    /// geht das hier auch anders??
    if (std::abs(m_oscA_phase_stateVar - phsSampleA_2) > 0.5f)            // Check edge
    {
        m_OscA_randVal_int = m_OscA_randVal_int * 1103515245 + 12345;
    }

    const float rndValA = static_cast<float>(m_OscA_randVal_int) * 4.5657e-10f;
    m_oscA_phase_stateVar = phsSampleA_2;

    const float phsInc_A_1 = ((rndValA * osc_a_fluec * osc_a_frq) + osc_a_frq) * m_sample_interval;
    const float phsInc_A_2 = m_oscA_phase + phsInc_A_1;
    m_oscA_phase = phsInc_A_2 - NlToolbox::Conversion::float2int(phsInc_A_2);

    const float oscSampleA = m_mute_state[m_OscA_mute] * NlToolbox::Math::sinP3_noWrap(phsSampleA_2);


    //**************************** Modulation B ******************************//
    const float modSampleB = modVarB_1 + modVarB_2 + modVarB_3;


    //**************************** Oscillator B ******************************//
    const float chirpIIRSampleB = (modSampleB - (m_chiB_a1 * m_chiB_stateVar)) * m_chiB_a0;  // Chirp IIR
    const float holdChirpB = chirpIIRSampleB;

    const float chirpFIRSampleB = (chirpIIRSampleB + m_chiB_stateVar) * m_chiB_omega;        // Chirp FIR
    m_chiB_stateVar = holdChirpB + NlToolbox::Constants::DNC_const;

    const float phsB = m_oscB_phase + osc_b_phs + un_phs + (-0.25f);
    const float phsSampleB_1 = chirpFIRSampleB + phsB;
    const float phsSampleB_2 = phsSampleB_1 - NlToolbox::Conversion::float2int(phsSampleB_1);

    /// geht das hier auch anders ???
    if (std::abs(m_oscB_phase_stateVar - phsSampleB_2) > 0.5f)    // Check edge
    {
        m_OscB_randVal_int = m_OscB_randVal_int * 1103515245 + 12345;
    }

    const float rndValB  = static_cast<float>(m_OscB_randVal_int) * 4.5657e-10f;
    m_oscB_phase_stateVar = phsSampleB_2;

    const float phsInc_B_1 = ((rndValB * osc_b_fluec * osc_b_frq) + osc_b_frq) * m_sample_interval;
    const float phsInc_B_2 = m_oscB_phase + phsInc_B_1;
    m_oscB_phase = phsInc_B_2 - NlToolbox::Conversion::float2int(phsInc_B_2);

    const float oscSampleB = m_mute_state[m_OscB_mute] * NlToolbox::Math::sinP3_noWrap(phsSampleB_2);


    //******************************* Shaper A *******************************//
    const float shpSampleA_1 = oscSampleA * shp_a_drvea;
    const float shpHoldA_1 = shpSampleA_1;

    const float shpSampleA_2 = NlToolbox::Math::sinP3_wrap(shpSampleA_1);
    const float shpSampleA_3 = NlToolbox::Others::threeRanges(shpSampleA_2, shpHoldA_1, shp_a_fld);

    const float shpHoldA_2 = shpSampleA_3 * shpSampleA_3 + (-0.5f);

    const float shpSampleA = NlToolbox::Others::parAsym(shpSampleA_3, shpHoldA_2, shp_a_asm);


    //******************************* Shaper B *******************************//
    const float shpSampleB_1 = oscSampleB * shp_b_drveb;
    const float shpHoldB_1 = shpSampleB_1;

    const float shpSampleB_2 = NlToolbox::Math::sinP3_wrap(shpSampleB_1);
    const float shpSampleB_3 = NlToolbox::Others::threeRanges(shpSampleB_2, shpHoldB_1, shp_b_fld);

    const float shpHoldB_2 = shpSampleB_3 * shpSampleB_3 + (-0.5f);

    const float shpSampleB = NlToolbox::Others::parAsym(shpSampleB_3, shpHoldB_2, shp_b_asm);


    //****************************** Crossfades ******************************//
    m_oscA_selfmix  = NlToolbox::Crossfades::bipolarCrossFade(oscSampleA, shpSampleA, osc_a_pmssh);
    m_oscA_crossmix = NlToolbox::Crossfades::bipolarCrossFade(oscSampleA, shpSampleA, osc_b_pmash);

    m_oscB_selfmix  = NlToolbox::Crossfades::bipolarCrossFade(oscSampleB, shpSampleB, osc_b_pmssh);
    m_oscB_crossmix = NlToolbox::Crossfades::bipolarCrossFade(oscSampleB, shpSampleB, osc_a_pmbsh);

    const float oscShpSample_A = NlToolbox::Crossfades::bipolarCrossFade(oscSampleA, shpSampleA, shp_a_mix) * env_a_mag;
    const float oscShpSample_B = NlToolbox::Crossfades::bipolarCrossFade(oscSampleB, shpSampleB, shp_b_mix) * env_b_mag;


    //**************************** Feedback Mix ******************************//
    const float oscShpFdbSample_A = NlToolbox::Crossfades::unipolarCrossFade(oscShpSample_A, _feedbackSample * shp_a_fbec, shp_a_fbm);
    const float oscShpFdbSample_B = NlToolbox::Crossfades::unipolarCrossFade(oscShpSample_B, _feedbackSample * shp_b_fbec, shp_b_fbm);


    //************************** Ring Modulation *****************************//
    const float ringSample = oscShpFdbSample_A * oscShpFdbSample_B;

    m_out_A = NlToolbox::Crossfades::unipolarCrossFade(oscShpFdbSample_A, ringSample, shp_a_rm);
    m_out_B = NlToolbox::Crossfades::unipolarCrossFade(oscShpFdbSample_B, ringSample, shp_b_rm);
}

/******************************************************************************/
/** @brief
*******************************************************************************/

void ae_soundgenerator::resetDSP()
{
    m_out_A = 0.f;
    m_out_B = 0.f;

    m_chiA_stateVar = 0.f;
    m_chiB_stateVar = 0.f;

    m_oscA_selfmix = 0.f;
    m_oscA_crossmix = 0.f;
    m_oscA_phase_stateVar = 0.f;

    m_oscB_selfmix = 0.f;
    m_oscB_crossmix = 0.f;
    m_oscB_phase_stateVar = 0.f;

    m_feedback_phase = 0.f;
}
