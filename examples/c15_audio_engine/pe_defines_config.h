/******************************************************************************/
/** @file       pe_defines_config.h
    @date       2018-03-13
    @version    1.0
    @author     Matthias Seeber
    @brief      crucial definitions of the param engine architecture
                ..
    @todo
*******************************************************************************/

#pragma once

#include <stdint.h>

/* Test Flags                                       THINGS TO DEFINE, testing candidates and new functionalities */

#define test_milestone              150             // Define Milestone: 150 (1.5), 155 (1.55, internal unison handling, echor/reverb sends)
#define test_key_update_pan         1               // (should pan values be updated on key? (probably yes)
#define test_note_shift             0               // [-48 ... 48] testing the note shift (sent on init)

#define test_tone_initial_freq      500.0f          // Test Tone initial Frequency
#define test_tone_initial_gain      -6.0f           // Test Tone initial Gain (in decibel)
#define test_tone_initial_state     0               // Test Tone initial State (0: disabled, 1: enabled)

#define test_comb_decay_gate_mode   1               // 0: apply in slow post processing (like prototype), 1: audio fade min, max by gate signal (recommended)

#define test_svf_types              1               // 0: SVF first Proto NAN, 1: SVF noFIR, 2: SVF FIR, 3: SVF Original Primary (later)
#define test_svf_fm_limit           1.5f            // SVF fm clipping maximum

#define test_fast_fold_asym         1               // 0: slow clock (producing audible artifacts), 1: fast clock (recommended)
#define test_preload_update         1               // 0: non-optimized preload update, 1: optimized preload update (recommended)
#define test_flushModeFlag          1               // 0: flushes ONLY Buffers, 1: flushes Buffers AND Filter State Variables
#define test_inputModeFlag          0               // 0: receive TCD MIDI, 1: receive Remote MIDI (and produce TCD internally)
#define test_whichEnvelope          1               // specify which env engine should be used: old (0) or new (1)

#define test_reverbParams           1               // 0: fast rendering (like Reaktor), 1: slow rendering (experimental)
#define test_reverbSmoother         1               // 0: no internal smoothers (experimental), 1: internal smoothers (like Reaktor)

#define test_phase_reset            1               // 0: reset phase only, 1: reset phase, self- & cross-mix and feedback, chirp state var
#define test_flanger_phs            1               // 0: slow (default, artifacts), 1: fast (seems okay), 2: audio (optimum)
#define test_flanger_env            2               // 0: slow (default, artifacts), 1: fast (artifacts), 2: audio (recommended)

#define test_initialize_time        1               // leave at 1 until LPC transmits full init sequence (including time)
#define test_initialize_fx_sends    1               // leave at 1 until LPC can handle fx sends (echo, reverb) (inits sends to 100%, maintaining compability)

/* Log Settings                                     THINGS TO PRINT into the terminal: TCD MIDI Input, single Parameter, single Signal */

#define log_examine                 1               // Examine Mechanism (Log, Param, Signal) - 0: disabled, 1: enabled
#define log_param_id                0               // Parameter ID of observed Parameter (internal ID, not TCD ID)
#define log_signal_id               0               // Signal ID of observed Signal
#define log_force_mono              0               // force monophonic rendering (map any voice to id 0)

#if test_inputModeFlag == 1

    /* Test poly Key Parameters (in Remote Mode only) */

    #define test_unisonCluster      0               // 0: transmit only played note, 1: transmit played note and second one (one octave apart)
    #define par_unisono_phase       0               // instead of two separate phases (as used previously), only one Unisono Phase needs to be transmitted
    #define par_voice_pan           0               // constant values to be sent during KeyDown sequence, tcd range: [-8000 ... 8000]#endif

#endif

/* Main Configuration                               (prepared for maximal 20 Voices) */

#define dsp_poly_types              2               // two polyphony types (mono, poly) - (later, a dual type needs to be implemented)
#define dsp_clock_types             4               // four different parameter types (sync, audio, fast, slow)
#define dsp_number_of_voices        20              // maximum allowed number of voices

const uint32_t dsp_clock_rates[2] = {               // sub-audio clocks are defined in rates (Hz) now

                                    9600,           // fast rate is 9600 Hz
                                    400             // slow rate is 400 Hz

};

#if test_milestone == 150

/* Main Parameter Definition                        -> see Linux Engine LPC Status */

#define sig_number_of_params        192             // see Linux Engine LPC Status / Overview, Parameter List
#define sig_number_of_param_items   268             // number of required (single-voice) rendering items for all parameters
#define sig_number_of_signal_items  136             // signals shared between the parameter and audio engine

/* TCD List Handling */

#define lst_recall_length           183             // preset-relevant parameters
#define lst_keyEvent_length         4               // 4 key event parameters
#define lst_number_of_lists         2               // predefined paramId lists (simplifying recall and key event update TCD sequences)

#elif test_milestone == 155

/* Main Parameter Definition                        -> see Linux Engine LPC Status */

#define sig_number_of_params        191             // see Linux Engine LPC Status / Overview, Parameter List
#define sig_number_of_param_items   248             // number of required (single-voice) rendering items for all parameters
#define sig_number_of_signal_items  136             // signals shared between the parameter and audio engine

/* TCD List Handling */

#define lst_recall_length           183             // preset-relevant parameters
#define lst_keyEvent_length         3               // 3 key event parameters
#define lst_number_of_lists         2               // predefined paramId lists (simplifying recall and key event update TCD sequences)

#endif

/* Utility Parameters and Envelope Definition */

#define sig_number_of_utilities     5               // four Utility Parameters: Velocity, Reference Tone, Test Tone Freq, Amp, State
#define sig_number_of_envelopes     5               // five Envelope Units: A, B, C, Gate, Flanger
#define sig_number_of_env_items     81              // 4 POLY Envelopes (A..Gate) = 4 * 20 = 80 items, 1 MONO (Flanger Decay), total: 81 items
#define sig_number_of_env_segments  4               // four segments for ADBDSR-type Envelopes (A, B, C): Attack, Decay 1, Decay 2, Release
#define sig_number_of_env_types     3               // three Envelope types: ADBDSR (A, B, C), Gate (Gate), Decay (Flanger)
#define sig_number_of_env_events    3               // three Envelope Event objects for Envelopes A, B, C (managing Velocity and KeyPos responses)

/* Internal IDs of crucial TCD parameters */

#define par_envelopeA               0               // item pointer to (consecutive) envelope parameters A (internal ids)
#define par_envelopeB               15              // item pointer to (consecutive) envelope parameters B (internal ids)
#define par_envelopeC               30              // item pointer to (consecutive) envelope parameters C (internal ids)

/* DSP Helper Values */

#define dsp_samples_to_ms           1.e-3f          // 1000 ms = 1 s, therefore: 1 ms = 1 / 1000 s = 1e-3 s
#define dsp_init_pitch_reference    440.f           // standard Frequency of A3 Note
#define dsp_expon_osc_pitch_from    -20             // lowest logarithmic Pitch value for Oscillator unit
#define dsp_expon_osc_pitch_range   150             // range of logarithmic Pitch value for Oscillator unit ([-20 ... 130] ST = 150 ST)
#define dsp_expon_lin_pitch_from    -150            // lowest logarithmic Pitch value for linear conversion
#define dsp_expon_lin_pitch_range   300             // range of logarithmic Pitch value for linear conversion ([-150 ... 150] ST = 300 ST)
#define dsp_expon_level_from        -300            // lowest logarithmic Level value for gain conversion (-300 dB)
#define dsp_expon_level_range       400             // range of logarithmic Level value for gain conversion ([-300 ... 100] dB = 400 dB)
#define dsp_expon_time_from         -20             // lowest logarithmic Time value for time conversion (-20 dB)
#define dsp_expon_time_range        110             // range of logarithmic Time value for time conversion ([-20 ... 90] dB = 110 dB)
#define dsp_expon_time_factor       104.0781f       // measured value to produce exactly time of 16000 (equals highest time)
#define dsp_comb_max_freqFactor     19.0166f        // measured value of highest frequency factor for the Comb Filter to run without bypass (corresponding to Pitch of 119.99 ST)
#define dsp_render_min              1.e-9f          // minimal rendered value for exponential transitions
#define dsp_initial_time            10              // initial smoothing time (in milliseconds, no more than 340ms!)

#define env_norm_peak               0.023766461f    // equals 1 / 42.0761 (taken from prototype)
#define env_clip_peak               1.412537545f    // measured value for LevelKT Clipping, equals +3 dB (candidate)
#define env_init_gateRelease        10              // release time of gate envelopes (in milliseconds) -- 1ms problematic (key up noise), 10ms okay (like prototype)
                                                    // (due to current comb decay gate implementation)
#define env_highest_finite_time     16000.f         // highest allowed finite time
