#include "nlaudioalsaoutput.h"

NlAudioAlsaOutput::NlAudioAlsaOutput(const devicename_t &name, std::shared_ptr<CircularAudioBuffer<char> > buffer) :
	basetype(name, buffer, false)
{
}

void NlAudioAlsaOutput::open()
{
	basetype::openCommon();
}

void NlAudioAlsaOutput::start()
{
	throwOnDeviceClosed();
	resetTerminateRequest();
	throwOnAlsaError(snd_pcm_hw_params(m_handle, m_hwParams), __func__);

	snd_pcm_format_t sampleFormat;
	snd_pcm_hw_params_get_format(m_hwParams, &sampleFormat);

	unsigned int channels = 0;
	throwOnAlsaError(snd_pcm_hw_params_get_channels(m_hwParams, &channels), __func__);

	SampleSpecs specs;
	specs.channels = channels;
	specs.buffersizeInFrames = getBuffersize();
	specs.buffersizeInFramesPerPeriode = getBuffersize() / getBufferCount();
	specs.bytesPerSample = snd_pcm_hw_params_get_sbits(m_hwParams) / 8;
	specs.bytesPerFrame = specs.bytesPerSample * specs.channels;
	specs.buffersizeInBytes = specs.bytesPerSample * specs.channels * specs.buffersizeInFrames;
	specs.buffersizeInBytesPerPeriode = specs.buffersizeInBytes / getBufferCount();
	std::cout << "NlAudioAlsaOutput Specs: " << std::endl << specs;

	m_audioThread = new std::thread(NlAudioAlsaOutput::worker, specs, this);
}

void NlAudioAlsaOutput::stop()
{
	throwOnDeviceClosed();
	setTerminateRequest();

	m_audioThread->join();
	delete m_audioThread;
	m_audioThread = nullptr;
}

//static
void NlAudioAlsaOutput::worker(SampleSpecs specs, NlAudioAlsaOutput *ptr)
{
	char *buffer = new char[specs.buffersizeInBytesPerPeriode];
	memset(buffer, 0, specs.buffersizeInBytesPerPeriode);

	std::cout << __func__ << " Output in" << std::endl;

	int counter = 0;

	while(!ptr->getTerminateRequest()) {

		// Might block, if nothing to read
		ptr->basetype::m_audioBuffer->get(buffer, specs.buffersizeInBytesPerPeriode);
		int ret = snd_pcm_writei(ptr->m_handle, buffer, specs.buffersizeInFramesPerPeriode);

//		counter++;
//		if (counter % 2 == 0)
//			memset(buffer, 0x7F, specs.buffersizeInBytesPerPeriode);
//		else
//			memset(buffer, 0xFF, specs.buffersizeInBytesPerPeriode);

		if (ret < 0)
			ptr->basetype::xrunRecovery(ptr, ret);

	}

	snd_pcm_abort(ptr->m_handle);

	delete[] buffer;
	std::cout << __func__ << " Output out" << std::endl;
}

#if 0
//Static
void AlsaDevice::generateSin(char *buf, unsigned int samples_per_channel, double freq, unsigned int rate, unsigned int channels)
{
	double ramp_increment = freq / static_cast<double>(rate);
	static double ramp = 0.f;

	for (unsigned int i=0; i<samples_per_channel*channels; i=i+channels) {
		ramp += ramp_increment;
		if (ramp >= 1.f)
			ramp -= 1.f;

		for (int channel=0; channel<channels; channel++)
			buf[i+channel] = sin(2.f * M_PI * ramp) * 10000;
	}
}
#endif
