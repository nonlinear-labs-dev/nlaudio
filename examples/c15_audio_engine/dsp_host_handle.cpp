#include "dsp_host_handle.h"

#include <audio/audioalsainput.h>
#include <audio/audioalsaoutput.h>
#include <midi/rawmididevice.h>

#include <common/stopwatch.h>
#include "paramengine.h"
#include <any>

namespace Nl {
namespace DSP_HOST_HANDLE {

    dsp_host m_host;    // renamed member dsp_host to m_host (Matthias)
    SharedStopWatchHandle sw = nullptr;

    /** @brief    Callback function for Sine Generator and Audio Input - testing with ReMote 61
            @param    Input Buffer
            @param    Output Buffer

            @param    buffer size
            @param    Sample Specs
    */
    void dspHostCallback(uint8_t *out, const SampleSpecs &sampleSpecs, std::any ptr)
    {

        if (sw == nullptr) {
            sw.reset(new StopWatch("AudioCallback", 100, StopWatch::SUMMARY, sampleSpecs.latency));
        }
        //TODO: Fixme. This RAII variant seems not to work
        //StopBlockTime(sw, "dsp_host");
        sw->start("callback");

       // std::this_thread::sleep_for(std::chrono::milliseconds(100));

        JobHandle jh = std::any_cast<JobHandle>(ptr);

        Nl::CommandBuffer::Command c;
        while ((c = jh.cmdBuffer->get()) != Nl::CommandBuffer::CMD_NO_CMD) {
            switch (c) {
            case Nl::CommandBuffer::CMD_GET_PARAM:
                    jh.debugBuffer->insert(pack<::examine_param>(m_host.m_param_status));
                break;
            case Nl::CommandBuffer::CMD_GET_SIGNAL:
                    jh.debugBuffer->insert(pack<::examine_signal>(m_host.m_signal_status));
                break;
            case Nl::CommandBuffer::CMD_GET_TCD_INPUT:
                    jh.debugBuffer->insert(pack<::examine_tcd_input_log>(m_host.m_tcd_input_log));
                    m_host.m_tcd_input_log.reset();
                break;
            case Nl::CommandBuffer::CMD_GET_CPU_LOAD:
                    jh.debugBuffer->insert(pack<SharedStopWatchHandle>(sw));
                break;
            case Nl::CommandBuffer::CMD_RESET:
                    m_host.reset();
                    jh.debugBuffer->insert(pack<std::string>("Reset executed"));
                break;
            case Nl::CommandBuffer::CMD_NO_CMD:
                // Just to suppress the warning (NEVER use this element)
                break;
            }
        }

        auto midiBuffer = getBufferForName("MidiBuffer");

        //---------------- Retrieve Midi Information if midi values have changed
        if (midiBuffer)
        {
            unsigned char midiByteBuffer[3];                                // MidiByteBuffer Structure: [0] - , [1] - Played Note Address, [2] - Velocity

            while (midiBuffer->availableToRead() >= 3)
            {
                midiBuffer->get(midiByteBuffer, 3);

                // printf("%02X %02X %02X\n", midiByteBuffer[0], midiByteBuffer[1], midiByteBuffer[2]);      // MIDI Value Control Output

/* run the program either in pure TCD mode (0) or test functionality (1) - defined by test_inputModeFlag in pe_defines_config.h */
#if test_inputModeFlag
                m_host.testMidi(midiByteBuffer[0], midiByteBuffer[1], midiByteBuffer[2]);
#else
                m_host.evalMidi(midiByteBuffer[0], midiByteBuffer[1], midiByteBuffer[2]);
#endif
            }
        }

        for (unsigned int frameIndex = 0; frameIndex < sampleSpecs.buffersizeInFramesPerPeriode; ++frameIndex)
        {
            m_host.tickMain();

            float outputSample;

            for (unsigned int channelIndex = 0; channelIndex < sampleSpecs.channels; ++channelIndex)
            {
                if (channelIndex)
                {
                     outputSample = m_host.m_mainOut_R;
                }
                else if (!channelIndex)
                {
                     outputSample = m_host.m_mainOut_L;
                }


                if (outputSample > 1.f || outputSample < -1.f)                  // Clipping
                {
                    printf("WARNING!!! C15 CLIPPING!!!\n");
                }

                setSample(out, outputSample, frameIndex, channelIndex, sampleSpecs);
            }
        }
        sw->stop();

    }

    // Matthias: added polyphony as argument
    JobHandle dspHostTCDControl(const AlsaAudioCardIdentifier &audioOutCard,
                                const AlsaMidiCardIdentifier &midiInCard,
                                unsigned int buffersize,
                                unsigned int samplerate,
                                unsigned int polyphony)
    {
        m_host.init(samplerate, polyphony);
        JobHandle ret;

        ret.debugBuffer = createSharedDebugBuffer();
        ret.cmdBuffer = createSharedCommandBuffer();

        // No input here
        ret.inBuffer = nullptr;
        ret.audioInput = nullptr;

        ret.outBuffer = createBuffer("OutputBuffer");
        ret.audioOutput = createAlsaOutputDevice(audioOutCard, ret.outBuffer, buffersize);
        ret.audioOutput->setSamplerate(samplerate);

        ret.inMidiBuffer = createBuffer("MidiBuffer");
        ret.midiInput = createRawMidiDevice(midiInCard, ret.inMidiBuffer);

        ret.audioOutput->start();
        ret.midiInput->start();

        ret.workingThreadHandle = registerOutputCallbackOnBuffer(ret.outBuffer, dspHostCallback, ret);

        return ret;
    }
} // namespace DSP_HOST
} // namespace Nl
