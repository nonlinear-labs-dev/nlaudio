/***
  Copyright (c) 2018 Nonlinear Labs GmbH

  Authors: Pascal Huerst <pascal.huerst@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
***/

#pragma once

#include <alsa/asoundlib.h>

#include <atomic>
#include <thread>
#include <iosfwd>

#include "audio/audio.h"
#include "common/alsa/alsacardidentifier.h"
#include "common/alsa/alsacardinfo.h"
#include "common/bufferstatistics.h"
#include "common/blockingcircularbuffer.h"

namespace Nl {

class AudioAlsa : public Audio
{
public:
	typedef Audio basetype;

    AudioAlsa(const AlsaAudioCardIdentifier& card, SharedBufferHandle buffer, bool isInput);
	virtual ~AudioAlsa();

	virtual void open() = 0; // Might throw, therefore not in constructor
	virtual void close();

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void init() = 0;

	//TODO: Changing buffer size, while playback is running might have strange sideeffects!
	virtual void setBuffersize(unsigned int buffersize);
	virtual unsigned int getBuffersize();

	virtual void setBufferCount(unsigned int buffercount);
	virtual unsigned int getBufferCount();

	virtual samplerate_t getSamplerate() const;
	virtual void setSamplerate(samplerate_t rate);

	virtual std::list<sampleformat_t> getAvailableSampleformats() const;
	virtual sampleformat_t getSampleFormat() const;
	virtual void setSampleFormat(sampleformat_t format);

	virtual void setChannelCount(channelcount_t n);
	virtual channelcount_t getChannelCount();

	virtual BufferStatistics getStats();

protected:
	void openCommon();
	void throwOnDeviceClosed(const std::string &file, const std::string &func, int line) const;
	void throwOnDeviceRunning(const std::string& file, const std::string& func, int line) const;

	void setTerminateRequest() { m_requestTerminate.store(true); }
	void resetTerminateRequest() { m_requestTerminate.store(false); }
	bool getTerminateRequest() const { return m_requestTerminate; }
	SampleSpecs getSpecs();

	static int xrunRecovery(AudioAlsa *ptr, int err);

protected:
	snd_pcm_t *m_handle;
	std::thread *m_audioThread;
	snd_pcm_hw_params_t *m_hwParams;
	std::atomic<bool> m_requestTerminate;
	std::atomic<unsigned int> m_xrunRecoveryCounter;
	SharedBufferHandle m_audioBuffer;

	void throwOnAlsaError(const std::string &file, const std::string &func, int line, int e) const;
private:
    AlsaAudioCardIdentifier m_card;

	bool m_deviceOpen;
	bool m_isInput;

};

} // namespace Nl
