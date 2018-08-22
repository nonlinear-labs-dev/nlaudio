#include "tcd_log.h"

void logEntry::set(uint32_t _delta, uint32_t _cmdID, uint32_t _arg1, uint32_t _arg2)
{
    m_elapsedSamples = _delta;
    m_commandID = _cmdID;
    m_commandArgs[0] = _arg1;
    m_commandArgs[1] = _arg2;
}

void logEntry::get()
{
    std::cout << "delta: " << m_elapsedSamples << ", ID: " << m_commandID << ", Args: " << m_commandArgs[0] << ", " << m_commandArgs[1] << std::endl;
}

void tcd_log::reset()
{
    m_index = 0;
    m_length = 0;
    m_timestamp = 0;
}

void tcd_log::tick()
{
    m_timestamp++;
}

void tcd_log::add(uint32_t _cmdID, uint32_t _arg1, uint32_t _arg2)
{
    m_entry[m_index].set(m_timestamp, _cmdID, _arg1, _arg2);
    m_timestamp = 0;
    m_index = (m_index + 1) % tcd_log_buffersize;
    m_length = std::min(m_length + 1, tcd_log_buffersize);
    m_startPos = (tcd_log_buffersize + m_index - m_length) % tcd_log_buffersize;
}

void tcd_log::get()
{
    std::cout << "TCD Input Log (length: " << m_length << ", start: " << m_startPos << ")" << std::endl;
    uint32_t idx = m_startPos;
    for(uint32_t i = 0; i < m_length; i++)
    {
        m_entry[idx].get();
        idx = (idx + 1) % tcd_log_buffersize;
    };
}
