/******************************************************************************/
/** @file		dsp_host.h
    @date
    @version
    @author
    @brief		main container object holding param and audio engine
                (including shared rendering signals, tcd decoder)
    @todo
*******************************************************************************/

#pragma once

#include <stdint.h>
#include <vector>
#include "pe_defines_config.h"
#include "paramengine.h"
#include "tcd_decoder.h"

#include "dsp_host_examine.h"

/* for testing purposes */
#if test_inputModeFlag == 1
#include "pe_defines_testconfig.h"
#endif

/* Audio Engine */
#include "ae_soundgenerator.h"
#include "ae_combfilter.h"
#include "ae_svfilter.h"
#include "ae_outputmixer.h"
#include "ae_cabinet.h"
#include "ae_gapfilter.h"
#include "ae_echo.h"
#include "ae_flanger.h"
#include "ae_feedbackmixer.h"
#include "ae_reverb.h"

/* dsp_host: main dsp object, holding TCD Decoder, Parameter Engine, Audio Engine, shared Signal Array, main signal (L, R) */
class dsp_host
{
public:
    dsp_host();                                                         // default Constructor (signal initialization only)
    /* local variables */
    uint32_t m_samplerate;                                              // project sample rate is given at program startup by commandline
    uint32_t m_voices;                                                  // project polyphony is given at program startup by commandline
    uint32_t m_clockPosition[dsp_clock_types] = {0, 0, 0, 0};           // sample clock data structure
    uint32_t m_clockDivision[dsp_clock_types] = {0, 1, 5, 120};         // clock division settings (defaults to 48000 Hz sampleRate)
    uint32_t m_upsampleFactor = 1;                                      // time conversion handle (sampleRate / 48000)
    /* hosting shared param signal array */
    float m_paramsignaldata[dsp_number_of_voices][sig_number_of_signal_items] = {};
    /* main signal output (left, right) */
    float m_mainOut_R, m_mainOut_L;                                     // final stereo (monophonic) audio (output) signal
    /* local data structures */
    decoder m_decoder;                                                  // TCD command evaluation
    paramengine m_params;                                               // parameter and envelope rendering
    /* proper init (samplerate & polyphony) */
    void init(uint32_t _samplerate, uint32_t _polyphony);               // proper initialization
    void loadInitialPreset();                                           // load initial preset for valid values in signal array (before rendering begins)
    /* the two main interaction methods */
    void tickMain();                                                    // main trigger for sample clock operations
    void evalMidi(uint32_t _status, uint32_t _data0, uint32_t _data1);  // main trigger for MIDI input (TCD)
    /* main TCD mechanism commands */
    void voiceSelectionUpdate();                                        // evaluation of the voice selection mechanism
    void paramSelectionUpdate();                                        // evaluation of the param selection mechanism
    void preloadUpdate(uint32_t _mode, uint32_t _listId);               // evaluation of the preload mechanism
    void destinationUpdate(float _value);                               // distribution of an incoming destination (to selection)
    void timeUpdate(float _value);                                      // distribution of an incoming time (to selection)
    void utilityUpdate(float _value);                                   // evaluation of the utility mechanism
    void listUpdate(float _dest);                                       // evaluation of the list mechanism
    void keyUp(uint32_t _voiceId, float _velocity);                     // key up event trigger
    void keyDown(uint32_t _voiceId, float _velocity);                   // key down event trigger
    void keyApply(uint32_t _voiceId);                                   // key application and distribution (to voice selection)
    /* test stuff */
#if test_inputModeFlag == 1
    uint32_t m_test_voiceId = 0;                                        // a rather sloppy voice allocation approach
    uint32_t m_test_noteId[128] = {};                                   // active note tracking
    const float m_test_normalizeMidi = (1.f / 127.f);                   // normalize midi values
    uint32_t m_test_selectedGroup = 0;                                  // a group selector
    uint32_t m_test_midiMode = 1;                                       // a mode selector (init to GLOBAL MODE)
    int32_t m_test_selectedParam = 0;                                   // a param selector
    void testMidi(uint32_t _status, uint32_t _data0, uint32_t _data1);  // testing the engine
    void testRouteControls(uint32_t _id, uint32_t _value);              // control routing
    void testNoteOn(uint32_t _pitch, uint32_t _velocity);               // testing note on messages
    void testNoteOff(uint32_t _pitch, uint32_t _velocity);              // testing note off messages
    void testSetGlobalTime(uint32_t _value);                            // testing times
    void testSetReference(uint32_t _value);                             // testing reference tone
    void testLoadPreset(uint32_t _presetId);                            // testing simple preset recall sequence
    void testFlush();                                                   // testing flush
    void testGetSignalData();                                           // print signal
    void testGetParamHeadData();                                        // print param configuration
    void testGetParamRenderData();                                      // print param rendering state
    void testParseDestination(int32_t _value);                          // send destinations accordingly
    void testInit();
#endif
    /* Debug Stuff */
    examine_tcd_input_log m_tcd_input_log;
    examine_param m_param_status;
    examine_signal m_signal_status;
    void examineParameter();
    void examineSignal();

    /* Audio Engine */
    ae_soundgenerator m_soundgenerator[dsp_number_of_voices];
    ae_combfilter m_combfilter[dsp_number_of_voices];
    ae_svfilter m_svfilter[dsp_number_of_voices];
    ae_feedbackmixer m_feedbackmixer[dsp_number_of_voices];
    ae_outputmixer m_outputmixer;
    ae_cabinet m_cabinet;
    ae_gapfilter m_gapfilter;
    ae_echo m_echo;
    ae_flanger m_flanger;
    ae_reverb m_reverb;

    void initAudioEngine();
    void makePolySound(float *_signal, uint32_t _voiceID);
    void makeMonoSound(float *_signal);

    inline void setPolySlowFilterCoeffs(float *_signal, uint32_t _voiceID);
    inline void setMonoSlowFilterCoeffs(float *_signal);
    inline void setMonoFastFilterCoeffs(float *_signal);

    /*fadepoint for flushing*/
    bool m_flush;
    uint32_t m_table_indx;
    uint32_t m_flush_indx;
    std::vector<float> m_raised_cos_table;

    /* Audio Engine Reset */
    void resetDSP(bool _resetEnvs);
};
