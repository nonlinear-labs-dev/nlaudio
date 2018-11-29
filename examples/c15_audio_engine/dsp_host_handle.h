#pragma once

/** @file       dsp_host_handle.cpp / dsp_host_handle.h
    @date       2018-03-07
    @brief      replacing the voice_manager as new main container
    @author     Matthias Seeber & Anton Schmied [2018-03-07]
**/

#include <audio/audiofactory.h>
#include "dsp_host.h"

namespace Nl {
namespace DSP_HOST_HANDLE {

    void processAudioFrames(uint8_t *out, const SampleSpecs &sampleSpecs);
    dsp_host &getDspHost();

    JobHandle dspHostTCDControl(const AlsaAudioCardIdentifier &audioOutCard,
                                const AlsaMidiCardIdentifier &midiIn,
                                unsigned int buffersize,
                                unsigned int samplerate,
                                unsigned int polyphony);
}   //namespace DSP_HOST
}   //namespace NL
