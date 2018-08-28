/*! \mainpage NlAudio - A lightwight C++ wrapper for alsa and jack
 *
 * \section intro_sec This documentation is split into the following subsections:
 * \ref Audio\n
 * \ref Midi\n
 * \ref Tools\n
 * \ref Factory\n
 * \n
 * More has to be done, but first a want to make a proper library from that
 *
 * \section install_sec Installation
 *
 * sudo make install blub und so
 *
 * \subsection step1 Step 1: Opening the box
 *
 * This could be a subsection...
 *
 */

#include <iostream>
#include <sstream>
#include <ostream>
#include <stdio.h>
#include <getopt.h>

#include <audio/audioalsainput.h>
#include <audio/audioalsaoutput.h>
#include <audio/audiofactory.h>
#include <audio/audioalsa.h>
#include <common/alsa/alsacardidentifier.h>
#include <audio/audioalsaexception.h>

#include <midi/midi.h>
#include <midi/rawmididevice.h>

#include <common/tools.h>
#include <common/stopwatch.h>
#include <common/blockingcircularbuffer.h>
#include <common/debugbuffer.h>
#include <common/commandbuffer.h>
#include <common/specialkeyboard.h>

// new:
#include "c15_audio_engine/dsp_host_handle.h"


#include <chrono>

using namespace std;

//
//#include "c15_audio_engine/soundgenerator.h"

void usage(const char* name)
{
    std::cout << "usage:" << std::endl <<
                 "   " << name << ":" << std::endl <<
                 "        -s" << " Samplerate in Hz (default=48000)" << std::endl <<
                 "        -v" << " Voice count (default=20)" << std::endl <<
                 "        -t" << " Mode" << std::endl <<
                 "        -a" << " Audio Device" << std::endl <<
                 "        -m" << " Midi Device" << std::endl;

    exit(EXIT_SUCCESS);
}

enum cmd_opts {
    OPT_SAMPLERATE,
    OPT_VOICECOUNT,
    OPT_MODE,
    OPT_AUDIODEVICE,
    OPT_MIDIDEVICE,
    OPT_NUM_ITEMS
};


int main(int argc, char **argv)
{

    int32_t opts[OPT_NUM_ITEMS];
    std::fill_n(opts, OPT_NUM_ITEMS, -1);

    // Add default values here!
    opts[OPT_SAMPLERATE] = 48000;
    opts[OPT_VOICECOUNT] = 20;

    int index = 0;
    if (argc == 1) {
        std::cout << std::endl << "Audio Devices:" << std::endl;

        auto availableDevices = Nl::AlsaAudioCardIdentifier::getCardIdentifiers();
        for(auto it=availableDevices.begin(); it!=availableDevices.end(); ++it, index++)
            std::cout << "[" << index << "]  " << *it << std::endl;

        std::cout << std::endl;
        usage(argv[0]);
    }

    char c = 0;
    while ((c = static_cast<char>(getopt(argc, argv, "hs:v:t:a:m:"))) != -1) {
        switch (c)
        {
        case 'h':
            usage(argv[0]);
            break;
        case 's': // Samplerate
            opts[OPT_SAMPLERATE] = atoi(optarg);
            break;
        case 'v': // Voice count
            opts[OPT_VOICECOUNT] = atoi(optarg);
            break;
        case 't': // Mode
            opts[OPT_MODE] = atoi(optarg);
            break;
        case 'a': // Audio Device
            opts[OPT_AUDIODEVICE] = atoi(optarg);
            break;
        case 'm': // Midi Device
            opts[OPT_MIDIDEVICE] = atoi(optarg);
            break;
        default:
            usage(argv[0]);
        }
    }

    // Get real name for audio device, and check if selection is valid in order to provide better information to the user
    bool hasInvalidOpts = true;
    std::string strAudioDevive = "invalid";

    auto availableCards = Nl::AlsaAudioCardIdentifier::getCardIdentifiers();
    int32_t numDevices = availableCards.size();

    if (opts[OPT_AUDIODEVICE] < numDevices && opts[OPT_AUDIODEVICE] > 0) {
        std::stringstream ss;
        ss << availableCards.at(opts[OPT_AUDIODEVICE]);
        strAudioDevive = ss.str();
        hasInvalidOpts = false;
    }

    for (unsigned i=0; i<OPT_NUM_ITEMS && !hasInvalidOpts; i++) {
        if (opts[i] < 0) {
            hasInvalidOpts = true;
        }
    }

    if (hasInvalidOpts) {
        std::cout << "Invalid Arguments! " << std::endl <<
                     "Samplerate       : " << (opts[OPT_SAMPLERATE] < 0 ? "invalid" :  std::to_string(opts[OPT_SAMPLERATE])) << std::endl <<
                     "Voice Count      : " << (opts[OPT_VOICECOUNT] < 0 ? "invalid" : std::to_string(opts[OPT_VOICECOUNT])) << std::endl <<
                     "Mode             : " << (opts[OPT_MODE] < 0 ? "invalid" : std::to_string(opts[OPT_MODE])) << std::endl <<
                     "Audio Device     : " << strAudioDevive  << std::endl <<
                     "Midi Device      : " << (opts[OPT_MIDIDEVICE] < 0 ? "invalid" : std::to_string(opts[OPT_MIDIDEVICE])) << std::endl <<
                     std::endl;

        exit(EXIT_FAILURE);
    }


    // Start the real stuff now
    try
    {
        Nl::AlsaAudioCardIdentifier audioOut = availableCards.at(opts[OPT_AUDIODEVICE]);
        Nl::AlsaMidiCardIdentifier midiIn(opts[OPT_MIDIDEVICE],0,0, "Midi In"); //TODO: Add lib function to look for midi devices

        const int buffersize = 256;
        const int samplerate = opts[OPT_SAMPLERATE];
        // Matthias: require number of voices, too (implemented)
        const int polyphony = opts[OPT_VOICECOUNT];

        // We can use the opts[OPT_MODE] command line flag here, to select a mode!
        std::cout << "[MODE=" << opts[OPT_MODE] << "][RUNNING] ";

        Nl::JobHandle handle;
        switch(opts[OPT_MODE]) {
        case 0:
            //            std::cout << "Nl::MINISYNTH::miniSynthMidiControl()" << std::endl;
            //            handle = Nl::MINISYNTH::miniSynthMidiControl(audioOut, midiIn, buffersize, samplerate);
            std::cout << ">>> NO MORE MINISYNTH MODE<<<" << std::endl;
            exit(EXIT_FAILURE);
        case 1:
            std::cout << "Nl::DSP_HOST_HANDLE::dspHostTCDControl()" << std::endl;
            handle = Nl::DSP_HOST_HANDLE::dspHostTCDControl(audioOut, midiIn, buffersize, samplerate, polyphony);
            break;
        default:
            std::cout << ">>> INVALID MODE <<<" << std::endl;
            exit(EXIT_FAILURE);
        }

        SpecialKeyboard sk;
        bool exit = false;
        while(true) {
            // nonblocking Keyboard Read
            char key = sk.kbhit();
            switch (key) {
            case 'a':
                handle.cmdBuffer->set(Nl::CommandBuffer::CMD_GET_PARAM);
                break;
            case 'b':
                handle.cmdBuffer->set(Nl::CommandBuffer::CMD_GET_SIGNAL);
                break;
            case 'c':
                handle.cmdBuffer->set(Nl::CommandBuffer::CMD_GET_TCD_INPUT);
                break;
            case 'd':
                handle.cmdBuffer->set(Nl::CommandBuffer::CMD_GET_CPU_LOAD);
                break;
            case 'm':
                if (handle.inMidiBuffer) {
                    unsigned long rxBytes, txBytes;
                    handle.inMidiBuffer->getStat(&rxBytes, &txBytes);
                    std::cout << "Midi: Input Statistics:" << std::endl
                              << "  rx=" << rxBytes << "  txBytes=" << txBytes << std::endl;
                }
                break;
            case 'n':
                if (handle.audioOutput) {
                    std::cout << "Audio: Output Statistics:" << std::endl
                              << handle.audioOutput->getStats() << std::endl;
                }
                if (handle.audioInput) {
                    std::cout << "Audio: Input Statistics:" << std::endl
                              << handle.audioInput->getStats() << std::endl;
                }

                break;
            case 'q':
                exit = true;
                break;
            default:
                if (handle.debugBuffer->canRead())
                    std::cout << *handle.debugBuffer.get() << std::endl;

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            if (exit) break;
        }

        // Tell worker thread to cleanup and quit
        Nl::terminateWorkingThread(handle.workingThreadHandle);
        if (handle.audioOutput) handle.audioOutput->stop();
        if (handle.audioInput) handle.audioInput->stop();

    } catch (Nl::AudioAlsaException& e) {
        std::cout << "### Exception ###" << std::endl << "  " << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cout << "### Exception ###" << std::endl << "  " << e.what() << std::endl;
    } catch(...) {
        std::cout << "### Exception ###" << std::endl << "  default: most likely libasound.so" << std::endl;
    }
}

