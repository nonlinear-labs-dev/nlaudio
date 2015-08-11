#include "audiobuffer.h"

#include <string.h> //memset

AudioBuffer::AudioBuffer(unsigned int size) :
	m_buffer(new float[size]),
	m_size(size),
	m_bytesRead(0),
	m_bytesWritten(0)
{
	memset(m_buffer, 0, m_size);
}

AudioBuffer::~AudioBuffer()
{
	delete[] m_buffer;
}

// Block callee, if nothing to read
unsigned int AudioBuffer::get(void *buffer, unsigned int size)
{
	std::unique_lock<std::mutex> mlock(m_mutex);
	while ((m_bytesWritten - m_bytesRead) < size)
		m_condition.wait(mlock);

	m_bytesRead += size;
	memcpy(buffer, m_buffer, size);

	return size;
}

// Block callee, if read in progress.
// Wake up sleeping readers, if any
void AudioBuffer::set(void *buffer, unsigned int size)
{
	std::unique_lock<std::mutex> mlock(m_mutex);
	m_bytesWritten += size;
	memcpy(m_buffer, buffer, size);
	mlock.unlock();
	m_condition.notify_one();
}

void AudioBuffer::getStat(unsigned long *readBytes, unsigned long *writtenBytes)
{
	std::unique_lock<std::mutex> mlock(m_mutex);
	*readBytes = m_bytesRead;
	*writtenBytes = m_bytesWritten;
}