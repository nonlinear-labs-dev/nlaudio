#include "inputtooutput.h"

#include <audio/audioalsainput.h>
#include <audio/audioalsaoutput.h>
#include <audio/audioalsaexception.h>

#include <common/stopwatch.h>
#include <common/tools.h>

using namespace Nl;

std::shared_ptr<StopWatch> sw(new StopWatch("AudioCallback", 10000, Nl::StopWatch::SUMMARY, std::chrono::microseconds(0)));



int main()
{
	initSignalHandler();

	try
	{
        AlsaAudioCardIdentifier audioIn(1,0,0, "USB Device");
        AlsaAudioCardIdentifier audioOut(1,0,0, "USB Device");

        const int buffersize = 16768;
		const int samplerate = 48000;

		auto handle = inputToOutput(audioIn, audioOut, buffersize, samplerate);

		while(getchar() != 'q')
		{
			std::cout << sw << std::endl;

			if (handle.audioOutput) std::cout << "Audio: Output Statistics:" << std::endl
											  << handle.audioOutput->getStats() << std::endl;
			if (handle.audioInput) std::cout << "Audio: Input Statistics:" << std::endl
											 << handle.audioInput->getStats() << std::endl;

			if (handle.inMidiBuffer) {
				unsigned long rxBytes, txBytes;
				handle.inMidiBuffer->getStat(&rxBytes, &txBytes);
				std::cout << "Midi: Input Statistics:" << std::endl
						  << "rxBytes=" << rxBytes << "  txBytes=" << txBytes << std::endl;
			}

			std::cout << "BufferCount: " << handle.audioInput->getBufferCount() << std::endl;
		}

		// Tell worker thread to cleanup and quit
		terminateWorkingThread(handle.workingThreadHandle);
		if (handle.audioOutput) handle.audioOutput->stop();
		if (handle.audioInput) handle.audioInput->stop();

    } catch (AudioAlsaException& e) {
		std::cout << "### Exception A ### " << std::endl << e.what() << std::endl;
	} catch (std::exception& e) {
		std::cout << "### Exception B ###" << std::endl <<  e.what() << std::endl;
	} catch(...) {
		std::cout << "### Exception C ###" << std::endl << "  default" << std::endl;
	}

	return 0;
}

// In to out example
void inToOutCallback(u_int8_t *in,
					 u_int8_t *out,
					 const SampleSpecs &sampleSpecs __attribute__ ((unused)),
                     std::any ptr __attribute__ ((unused)))
{
	//static int counter = 0;
	//StopBlockTime sft(sw, "val" + std::to_string(counter++));

	memcpy(out, in, sampleSpecs.buffersizeInBytes);
}

JobHandle inputToOutput(const AlsaAudioCardIdentifier &inCard, const AlsaAudioCardIdentifier &outCard, unsigned int buffersize, unsigned int samplerate)
{
	// In this example, we just copy data from input to output
	// Samplerate and buffersize can be set. A handle to stop the
	// working threads is returned
	// To terminate this example, call:
	// terminateWorkingThread(handle)
	JobHandle ret;

	ret.inBuffer = createBuffer("InputBuffer");
	ret.audioInput = createAlsaInputDevice(inCard, ret.inBuffer, buffersize);
	ret.audioInput->setSamplerate(samplerate);

	ret.outBuffer = createBuffer("OutputBuffer");
	ret.audioOutput = createAlsaOutputDevice(outCard, ret.outBuffer, buffersize);
	ret.audioOutput->setSamplerate(samplerate);

	// DANGER!!!!
	// TODO: Check sync mechanism here. If registerInOutCallbackOnBuffer called before
	//		 input/output->start(), we seem to have a deadlock!
	// TODO: Consider implementing something like autostart for the threads in the
	//		 audio chain. Eg. Reading/Writing threads on BlockingCircularBuffer !!!

	ret.audioOutput->start();
	ret.audioInput->start();

    ret.workingThreadHandle = registerInOutCallbackOnBuffer(ret.inBuffer, ret.outBuffer, inToOutCallback, 0);

	return ret;
}

