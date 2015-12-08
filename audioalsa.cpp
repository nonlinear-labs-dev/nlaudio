#include "audioalsa.h"
#include "audio.h"
#include "tools.h"

#include <iostream>

namespace Nl {

/** \ingroup Audio
 *
 * \brief Constructor
 * \param device Alsa device id such as "hw:0,1"
 * \param buffer
 * \param isInput If true, the device is opened as input, otherwise as output.
 *
 * Constructor for AudioAlsa
 *
*/
AudioAlsa::AudioAlsa(const AlsaCardIdentifier& card, std::shared_ptr<BlockingCircularBuffer<uint8_t>> buffer, bool isInput) :
	m_handle(nullptr),
	m_hwParams(nullptr),
	m_xrunRecoveryCounter(0),
	m_audioBuffer(buffer),
	m_card(card),
	m_deviceOpen(false),
	m_isInput(isInput)

{
	std::cout << "New " << __func__ << " as " << (isInput ? "input" : "output") << std::endl;
}

/** \ingroup Audio
 *
 * \brief Destructor
 *
 * Destructor for AudioAlsa
 *
*/
AudioAlsa::~AudioAlsa()
{
	close();
}

/** \ingroup Audio
 *
 * \brief Throws a \ref AudioAlsaException on error
 * \param x Call to alsa library function
 *
 * This macro adds the file name, the function name and the line number to the \ref throwOnAlsaError() call.
 *
 * \code
 * THROW_ON_ALSA_ERROR(snd_pcm_hw_params_set_access(m_handle, m_hwParams, SND_PCM_ACCESS_RW_INTERLEAVED));
 * \endcode
 *
 *
 */
#define THROW_ON_ALSA_ERROR(x) { throwOnAlsaError(__FILE__, __func__, __LINE__, x); }

/** \ingroup Audio
 *
 * \brief Generates and throws a \ref AudioAlsaException, if \a e < 0
 * \param file File name where the error happened
 * \param func Function name where the error happened
 * \param line Line number of where the error happened
 * \param e Error number
 * \throw AudioAlsaException is thrown if \a e < 0
 *
 * This function checks the return value of an alsa library call and throws an \ref AudioAlsaException, if
 * the return value, which has to be passed to the function in \a e, is < 0
 *
 * See helper macro \ref THROW_ON_ALSA_ERROR about usage.
 *
 */
void AudioAlsa::throwOnAlsaError(const std::string& file, const std::string& func, int line, int e) const
{
	if (e < 0) {
		throw AudioAlsaException(func, file, line, e, snd_strerror(e));
	}
}

/** \ingroup Audio
 *
 * \brief Generates and throws a \ref AudioAlsaException, if the device has not been opened.
 * \param file File name where the error happened
 * \param func Function name where the error happened
 * \param line Line number of where the error happened
 * \throw AudioAlsaException is thrown if the device has not beend opened
 *
 * This function checks if the device has been opened and throws a \ref AudioAlsaException if not.
 *
 */
void AudioAlsa::throwOnDeviceClosed(const std::string& file, const std::string& func, int line) const
{
	if (!m_deviceOpen)
		throw(AudioAlsaException(func, file, line, -1, "Device is not opened, yet."));
}

/** \ingroup Audio
 *
 * \brief Generates and throws a \ref AudioAlsaException, if the device has not been started.
 * \param file File name where the error happened
 * \param func Function name where the error happened
 * \param line Line number of where the error happened
 * \throw AudioAlsaException is thrown if the device has not beend opened
 *
 * This function checks if the device has been started and throws a \ref AudioAlsaException if not.
 *
 */
void AudioAlsa::throwOnDeviceRunning(const std::string &file, const std::string &func, int line) const
{
	if (!m_audioThread)
		throw(AudioAlsaException(func, file, line, -1, "Device is not opened, yet."));
}

/** \ingroup Audio
 *
 * \brief Common open function, used by AudioAlsaInput::open() and AudioAlsaOutput::open()
 * \throw AudioAlsaException is thrown on error.
 *
 * This function is called by the input/output derivates in their open() function. See:
 *  - AudioAlsaInput::open()
 *  - AudioAlsaOutput::open()
 *
 */
void AudioAlsa::openCommon()
{
	THROW_ON_ALSA_ERROR(snd_pcm_open(&m_handle, m_card.getCardString().c_str(), m_isInput ? SND_PCM_STREAM_CAPTURE : SND_PCM_STREAM_PLAYBACK, SND_PCM_ASYNC));
	THROW_ON_ALSA_ERROR(snd_pcm_hw_params_malloc(&m_hwParams));
	THROW_ON_ALSA_ERROR(snd_pcm_hw_params_any(m_handle, m_hwParams));
	THROW_ON_ALSA_ERROR(snd_pcm_hw_params_set_access(m_handle, m_hwParams, SND_PCM_ACCESS_RW_INTERLEAVED));

	m_deviceOpen = true;
}

/** \ingroup Audio
 *
 * \brief Closes the device
 * \throw AudioAlsaException is thrown on error.
 *
 * This function closed the audio device. On error a \ref throwOnAlsaError() is thrown
 *
 */
void AudioAlsa::close()
{
	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_close(m_handle));
	snd_pcm_hw_params_free(m_hwParams);
	m_hwParams = nullptr;

	m_deviceOpen = false;
}

void AudioAlsa::setBuffersize(unsigned int buffersize)
{
	THROW_ON_ALSA_ERROR(snd_pcm_hw_params_set_buffer_size(m_handle, m_hwParams, static_cast<snd_pcm_uframes_t>(buffersize)));
}

unsigned int AudioAlsa::getBuffersize()
{
	snd_pcm_uframes_t buffersize;
	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_get_buffer_size(m_hwParams, &buffersize));

	return static_cast<unsigned int>(buffersize);
}

void AudioAlsa::setBufferCount(unsigned int buffercount)
{
	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_set_periods(m_handle, m_hwParams, buffercount, 0));
}

unsigned int AudioAlsa::getBufferCount()
{
	int dir = 0;
	unsigned int buffercount = 0;
	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_get_periods(m_hwParams, &buffercount, &dir));

	return buffercount;
}

samplerate_t AudioAlsa::getSamplerate() const
{
	int dir = 0;
	samplerate_t rate = 0;

	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_get_rate(m_hwParams, &rate, &dir));

	return rate;
}

void AudioAlsa::setSamplerate(samplerate_t rate)
{
	throwOnDeviceClosed(__FILE__, __func__, __LINE__);

	int dir = 0;
	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_set_rate_near(m_handle, m_hwParams, &rate, &dir));
}

std::list<sampleformat_t> AudioAlsa::getAvailableSampleformats() const
{
	throwOnDeviceClosed(__FILE__, __func__, __LINE__);

	snd_pcm_format_mask_t *formatMask = nullptr;
	snd_pcm_format_mask_malloc(&formatMask);
	snd_pcm_hw_params_get_format_mask(m_hwParams, formatMask);

	std::list<sampleformat_t> ret;
	for (int format=0; format<=SND_PCM_FORMAT_LAST; ++format) {
		if (snd_pcm_format_mask_test(formatMask, static_cast<snd_pcm_format_t>(format)))
			//ret.push_back(snd_pcm_format_name(static_cast<snd_pcm_format_t>(format)));
			ret.insert(ret.end(), snd_pcm_format_name(static_cast<snd_pcm_format_t>(format)));
	}

	snd_pcm_format_mask_free(formatMask);
	return ret;
}

sampleformat_t AudioAlsa::getSampleFormat() const
{
	throwOnDeviceClosed(__FILE__, __func__, __LINE__);

	snd_pcm_format_t val;

	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_get_format(m_hwParams, &val));

	return snd_pcm_format_name(val);
}

void AudioAlsa::setSampleFormat(sampleformat_t format)
{
	throwOnDeviceClosed(__FILE__, __func__, __LINE__);

	snd_pcm_format_t alsaFormat = snd_pcm_format_value(format.c_str());
	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_set_format(m_handle, m_hwParams, alsaFormat));
}

void AudioAlsa::setChannelCount(channelcount_t n)
{
	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_set_channels(m_handle, m_hwParams, n));
}

channelcount_t AudioAlsa::getChannelCount()
{
	channelcount_t channels = 0;
	throwOnAlsaError(__FILE__, __func__, __LINE__, snd_pcm_hw_params_get_channels(m_hwParams, &channels));
	return channels;
}

/** \ingroup Audio
 *
 * \brief Common open function, used by AudioAlsaInput::open() and AudioAlsaOutput::open()
 * \throw AudioAlsaException is thrown on error.
 *
 * This function is called by the input/output derivates in their open() function. See:
 *  - AudioAlsaInput::open()
 *  - AudioAlsaOutput::open()
 *
 */
SampleSpecs AudioAlsa::getSpecs()
{
	snd_pcm_format_t sampleFormat;
	snd_pcm_hw_params_get_format(m_hwParams, &sampleFormat);

	SampleSpecs specs;
	specs.samplerate = getSamplerate();
	specs.isSigned = snd_pcm_format_signed(sampleFormat) == 1;
	specs.isLittleEndian = snd_pcm_format_little_endian(sampleFormat) == 1;
	specs.isFloat = snd_pcm_format_float(sampleFormat);

	specs.channels = getChannelCount();

	// 1 Frame in Bytes: Channels * BytesPerSample
	specs.buffersizeInFrames = getBuffersize();
	specs.buffersizeInFramesPerPeriode = specs.buffersizeInFrames / getBufferCount();

	// 1 Sample in Bytes: BytesPerSample
	specs.buffersizeInSamples = specs.buffersizeInFrames * getChannelCount();
	specs.buffersizeInSamplesPerPeriode = specs.buffersizeInSamples / getBufferCount();

	specs.bytesPerSample = snd_pcm_hw_params_get_sbits(m_hwParams) / 8;
	specs.bytesPerSamplePhysical = snd_pcm_format_physical_width(sampleFormat) / 8;
	specs.bytesPerFrame = specs.bytesPerSample * specs.channels;

	specs.buffersizeInBytes = specs.bytesPerSample * specs.channels * specs.buffersizeInFrames;
	specs.buffersizeInBytesPerPeriode = specs.buffersizeInBytes / getBufferCount();

	return specs;
}

/** \ingroup Audio
 *
 * \brief Print BufferStatistics using operator<<
 * \param lhs Left hand Side
 * \param rhs Right hand Side
 * \return std::ostream with string data
 *
 * Helper overload of operator<< for BufferStatistics
 * so it can be used as:
 *
 * \code{.cpp}
 *	std::cout << "Statistics: " << std::endl << handle->getStats() << std::endl;
 * \endcode
*/
std::ostream& operator<<(std::ostream& lhs, const BufferStatistics& rhs)
{
	lhs << "  Bytes Read From Buffer:   " << rhs.bytesReadFromBuffer << std::endl
		<< "  Bytes Written To Buffer:  " << rhs.bytesWrittenToBuffer << std::endl
		<< "  Over-/Underrun Count:     " << rhs.xrunCount << std::endl;

	return lhs;
}

/** \ingroup Audio
 *
 * \brief Returns current buffer statistics on interface
 *
 * This function returns a \ref BufferStatistics object. This can be used to print
 * infromation on buffer access and Ober-/Underruns:
 * \code{.cpp}
 *  std::cout << "Statistics: " << std::endl << handle->getStats() << std::endl;
 * \endcode
 */
BufferStatistics AudioAlsa::getStats()
{
	BufferStatistics ret;
	m_audioBuffer->getStat(&ret.bytesReadFromBuffer, &ret.bytesWrittenToBuffer);
	ret.xrunCount = m_xrunRecoveryCounter;

	return ret;
}

/** \ingroup Audio
 *
 * \brief Static function, that returns available devices
 * \return All available cards on the plattform, represented by a list of \ref AlsaCardInfo
 *
 * Returns a list of available cards on the plattform, represented by \ref AlsaCardInfo objects,
 * stored in a std::list
 *
 */
std::list<AlsaCardInfo> AudioAlsa::getDetailedCardInfos()
{
	int card = -1;
	int dev = -1;

	std::list<AlsaCardInfo> ret;

	while (snd_card_next(&card) >= 0 && card >= 0) {

		AlsaCardInfo currentCardInfo;

		std::string controlName = "hw:" + std::to_string(card);
		snd_ctl_t *handle;
		if (snd_ctl_open(&handle, controlName.c_str(), 0) == 0) {

			snd_ctl_card_info_t *cardinfo;
			snd_ctl_card_info_alloca(&cardinfo);
			if (snd_ctl_card_info(handle, cardinfo) == 0) {

				//snd_ctl_elem_info_get_interface()

				dev = -1;
				while (snd_ctl_pcm_next_device(handle, &dev) == 0 && dev >= 0) {

					snd_pcm_info_t *pcminfo;
					snd_pcm_info_alloca(&pcminfo);

					snd_pcm_info_set_device(pcminfo, dev);
					snd_pcm_info_set_subdevice(pcminfo, 0);

					snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;
					snd_pcm_info_set_stream(pcminfo, stream);

					if (snd_ctl_pcm_info(handle, pcminfo) == 0) {

						AlsaDeviceInfo currentDeviceInfo;

						int count = snd_pcm_info_get_subdevices_count(pcminfo);
						for (int i=0; i<count; i++) {
							snd_pcm_info_set_subdevice(pcminfo, i);


							AlsaSubdeviceInfo currentSubdeviceInfo;
							currentSubdeviceInfo.subdeviceId = i;
							currentSubdeviceInfo.name = snd_pcm_info_get_subdevice_name(pcminfo);
							currentDeviceInfo.subdevices.push_back(currentSubdeviceInfo);
						}

						currentDeviceInfo.deviceId = dev;
						currentDeviceInfo.id = snd_pcm_info_get_id(pcminfo); // USB Audio
						currentDeviceInfo.name = snd_pcm_info_get_name(pcminfo); // USB Audio #1

						currentCardInfo.devices.push_back(currentDeviceInfo);
						currentCardInfo.cardId = card;
						currentCardInfo.components = snd_ctl_card_info_get_components(cardinfo); // USB0a92:0054
						currentCardInfo.driver = snd_ctl_card_info_get_driver(cardinfo); // USB-Audio
						currentCardInfo.id = snd_ctl_card_info_get_id(cardinfo); // nano
						currentCardInfo.longname = snd_ctl_card_info_get_longname(cardinfo); // ESI Audiotechnik GmbH Dr. DAC nano at usb-0000:00:14.0-1, full speed
						currentCardInfo.name = snd_ctl_card_info_get_name(cardinfo); // Dr. DAC nano
						currentCardInfo.mixername = snd_ctl_card_info_get_mixername(cardinfo); // USB Mixer
					}
				}
			} else {
				std::cout << "EEE2" << std::endl;
			}
		} else {
			std::cout << "EEE1" << std::endl;
		}

		ret.push_back(currentCardInfo);
	}
	return ret;
}

std::ostream& operator<<(std::ostream& lhs, const AlsaSubdeviceInfo& rhs)
{
	lhs << "Subdevice[" << rhs.subdeviceId << "] "
		   "Name: " << rhs.name;
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const AlsaDeviceInfo& rhs)
{
	lhs << "Device[" << rhs.deviceId << "] "
		   "Name: " << rhs.name << ", " <<
		   "Id: " << rhs.id << ", " <<
		   "Subdevices: " << rhs.subdevices.size();

	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const AlsaCardInfo& rhs)
{
	lhs << " CardId:      " << rhs.cardId << std::endl <<
		   " Name:        " << rhs.name << std::endl <<
		   " Long name:   " << rhs.longname << std::endl <<
		   " Mixer name:  " << rhs.mixername << std::endl <<
		   " Id:          " << rhs.id << std::endl <<
		   " Driver:      " << rhs.driver << std::endl <<
		   " Components:  " << rhs.components << std::endl <<
		   " Devices:     " << rhs.devices.size() << std::endl;

	for (auto it=rhs.devices.begin(); it!=rhs.devices.end(); ++it) {

		lhs << "   " << *it << std::endl;

		for (auto subit=it->subdevices.begin(); subit!=it->subdevices.end(); ++subit) {
			std::cout << "     [hw:" << rhs.cardId << "," << it->deviceId << "," << subit->subdeviceId << "] ";
			lhs << *subit << std::endl;
		}
	}
	return lhs;
}

std::list<AlsaCardIdentifier> AudioAlsa::getCardIdentifiers()
{
	std::list<AlsaCardIdentifier> ret;

	auto cardInfoList = AudioAlsa::getDetailedCardInfos();

	for (auto cardIt=cardInfoList.begin(); cardIt!=cardInfoList.end(); ++cardIt)
		for (auto deviceIt=cardIt->devices.begin(); deviceIt!=cardIt->devices.end(); ++deviceIt)
			for (auto subdeviceIt=deviceIt->subdevices.begin(); subdeviceIt!=deviceIt->subdevices.end(); ++subdeviceIt) {
				int card = cardIt->cardId;
				int device = deviceIt->deviceId;
				int subdevice = subdeviceIt->subdeviceId;
				std::string name = cardIt->name;
				ret.push_back( AlsaCardIdentifier(card, device, subdevice, name));
			}

	return ret;
}
std::ostream& operator<<(std::ostream& lhs, const AlsaCardIdentifier& rhs)
{
	lhs << rhs.getCardStringExtended();
	return lhs;
}


/** \ingroup Audio
 *
 * \brief Static function, that recovers the interface from buffer over-/underruns
 * \param ptr A pointer to an AudioAlsa instance
 * \param err The error number, which indicates what has to be fixed.
 * \return An error number
 *
 * Static function, that recovers from errors such as over-/underflows and returns an error code.
 *
 */
int AudioAlsa::xrunRecovery(AudioAlsa *ptr, int err)
{
	//Atomic
	ptr->m_xrunRecoveryCounter++;

	if (err == -EPIPE) {    /* under-run */
		err = snd_pcm_prepare(ptr->m_handle);
		if (err < 0)
			printf("Can't recovery from underrun, prepare failed: %s\n", snd_strerror(err));
		return 0;
	} else if (err == -ESTRPIPE) {
		while ((err = snd_pcm_resume(ptr->m_handle)) == -EAGAIN)
			sleep(1);       /* wait until the suspend flag is released */
		if (err < 0) {
			err = snd_pcm_prepare(ptr->m_handle);
			if (err < 0)
				printf("Can't recover from suspend, prepare failed: %s\n", snd_strerror(err));
		}
		return 0;
	}
	return err;
}

} // namespace Nl