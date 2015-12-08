#pragma once

/** \defgroup Audio
 *
 * \brief Audio subsystem for NlAudio Framework
 *
*/

#include <cstdint>
#include <list>
#include <queue>
#include <string>


namespace Nl {

/** A typedef for sample rates */
typedef unsigned int samplerate_t;
/** A typedef for sample formats */
typedef std::string sampleformat_t;
/** A typedef for device names */
//typedef std::string devicename_t;
/** A typedef for channel counts */
typedef unsigned int channelcount_t;

/** \ingroup Audio
 *
 * \brief Pure virtual base class for all audio classes
 *
 * This defines the interface for all audio classes, such as:
 *  - Nl::AudioAlsaInput
 *  - Nl::AudioAlsaOutput
 *  - Nl::AudioJackInput
 *  - Nl::AudioJackOutput
 *
*/
class Audio
{
public:
	/** \ingroup Audio
	 *
	 * \brief Open the audio device
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Opens the audio device, represented by that class.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual void open() = 0;

	/** \ingroup Audio
	 *
	 * \brief Close the audio device
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Closes the audio device, represented by that class
	 *
	*/
	virtual void close() = 0;

	/** \ingroup Audio
	 *
	 * \brief Sets the buffersize in frames
	 * \param buffersize The buffersize in frames
	 * \throws AudioAlsaException is thrown on error
	 *
	 * This is the actual value, that influences the latency:
	 * \f$ latency = buffersize * \frac{1}{sample rate} \f$
	 *
	 * Sets the buffersize in frames.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual void setBuffersize(unsigned int buffersize) = 0;

	/** \ingroup Audio
	 *
	 * \brief Returns the buffersize in frames
	 * \return The buffersize in frames
	 * \throws AudioAlsaException is thrown on error
	 *
	 * This is the actual value, that influences the latency:
	 * \f$ latency = buffersize * \frac{1}{sample rate} \f$
	 *
	 * Returns the buffersize in frames.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual unsigned int getBuffersize() = 0;

	/** \ingroup Audio
	 *
	 * \brief Sets the number of buffers used
	 * \param buffercount The buffercount
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Sets the number of buffers, used by the audio driver.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual void setBufferCount(unsigned int buffercount) = 0;

	/** \ingroup Audio
	 *
	 * \brief Returns the number of buffers used
	 * \return The buffercount
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Returns the number of buffers, used by the audio driver.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual unsigned int getBufferCount() = 0;

	/** \ingroup Audio
	 *
	 * \brief Sets the sample rate
	 * \param rate The sample rate
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Sets the sample rate to \a rate.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual void setSamplerate(samplerate_t rate) = 0;

	/** \ingroup Audio
	 *
	 * \brief Returns the sample rate
	 * \return The sample rate
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Sets the number of buffers, used by the audio driver.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual samplerate_t getSamplerate() const = 0;

	/** \ingroup Audio
	 *
	 * \brief Returns a list of available sample formats
	 * \return A list of available sample formats
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Return a list with available sample formats.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual std::list<sampleformat_t> getAvailableSampleformats() const = 0;

	/** \ingroup Audio
	 *
	 * \brief Returns the currently selected sample format
	 * \return The currently selected sample format
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Returns the currently selected sample format.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual sampleformat_t getSampleFormat() const = 0;

	/** \ingroup Audio
	 *
	 * \brief Sets the currently selected sample format
	 * \param format The sample format
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Sets the currently selected sample format.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual void setSampleFormat(sampleformat_t format) = 0;

	/** \ingroup Audio
	 *
	 * \brief Sets the number of channels
	 * \param n Number of channels
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Sets the number of channels to the given value.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual void setChannelCount(channelcount_t n) = 0;

	/** \ingroup Audio
	 *
	 * \brief Returns the number of channels
	 * \return Number of channels
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Returns the number of channels.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual channelcount_t getChannelCount() = 0;

	/** \ingroup Audio
	 *
	 * \brief Starts the working thread for the interface
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Returns the number of channels.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual void start() = 0;

	/** \ingroup Audio
	 *
	 * \brief Stopps the working thread for the interface
	 * \throws AudioAlsaException is thrown on error
	 *
	 * Returns the number of channels.
	 * On error a \ref AudioAlsaException is thrown.
	 *
	*/
	virtual void stop() = 0;

protected:


};

} // Namespace Nl

