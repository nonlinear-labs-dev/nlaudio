/******************************************************************************/
/** @file		voicemanager.h
    @date		2016-07-26
    @version	0.1
    @author		Anton Schmied[2016-07-26]
    @brief		..
*******************************************************************************/

#pragma once

#include "sharedoutputs.h"

#include "nltoolbox.h"
#include "soundgenerator.h"
#include "outputmixer.h"
#include "echo.h"
#include "cabinet.h"


class VoiceManager{
public:
    VoiceManager();             // Default Constructor

    ~VoiceManager(){}           // Destructor

    float mainOut_L, mainOut_R; // fully processed samples

    void voiceLoop();
    void evalMidiEvents(unsigned char _instrID, unsigned char _ctrlID, float _ctrlVal);

private:

    Soundgenerator mSoundGenerator[NUM_VOICES];             // 12 Generatoren ... naja ...
    Outputmixer mOutputMixer;

    // Effects
    Echo mEcho;
    Cabinet mLeftCabinet, mRightCabinet;

#if 1
    void vallocInit();
    void vallocProcess(unsigned char _keyDirection, float _pitch, float _velocity);

    //--------------- Voice Allocation global variables
    int vVoiceState[NUM_VOICES] = {};                               // which voices are active? 1 - on, 0 - off

    int vOldestAssigned;
    int vYoungestAssigned;
    int vNextAssigned[NUM_VOICES] = {};                             // array with the next elements per voice
    int vPreviousAssigned[NUM_VOICES] = {};

    int vNumAssigned;

    int vOldestReleased;                                           // index of the earliest disabled voice (full use: earliest turned on)
    int vYoungestReleased;                                         // index of the last disabled voice (full use: last turned on)
    int vNextReleased[NUM_VOICES] = {};
#endif

    enum InstrID: unsigned char  // enums for Instrument IDs novation ReMOTE61
    {
        KEYUP_0             = 0x80,
        KEYUP_1             = 0x81,
        KEYUP_2             = 0x82,
        KEYUP_3             = 0x83,
        KEYUP_4             = 0x84,

        KEYDOWN_0           = 0x90,
        KEYDOWN_1           = 0x91,
        KEYDOWN_2           = 0x92,
        KEYDOWN_3           = 0x93,
        KEYDOWN_4           = 0x94,

        SG_A_PARAM          = 0xB0,
        SG_B_PARAM          = 0xB1,

        CABINET_PARAM       = 0xB2,
        OUTPUTMIXER_PARAM   = 0xB3,
        ECHO_PARAM          = 0xB4
    };

};





