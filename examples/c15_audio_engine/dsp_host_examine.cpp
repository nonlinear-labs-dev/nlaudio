#include "dsp_host_examine.h"

void tcd_log_entry::set(const uint32_t _time, const uint32_t _cmdId, const uint32_t _arg0, const uint32_t _arg1)
{
    m_time = _time;
    m_cmdId = _cmdId;
    m_arg = (_arg0 << 7) + _arg1;
}

void examine_tcd_input_log::reset()
{
    m_index = 0;
    m_length = 0;
    m_timestamp = 0;
}

void examine_tcd_input_log::tick()
{
    m_timestamp++;
}

void examine_tcd_input_log::add(const uint32_t _cmdId, const uint32_t _arg0, const uint32_t _arg1)
{
    m_entry[m_index].set(m_timestamp, _cmdId, _arg0, _arg1);
    m_timestamp = 0;
    m_index = (m_index + 1) % tcd_log_buffersize;
    m_length = std::min(m_length + 1, tcd_log_buffersize);
    m_startPos = (tcd_log_buffersize + m_index - m_length) % tcd_log_buffersize;
}

std::ostream& operator<<(std::ostream& lhs, const examine_tcd_input_log& rhs)
{
    lhs << "TCD MIDI Input Log: (Length: " << rhs.m_length << ")" << std::endl;
    lhs << "(elapsed Samples, Command, Databyte0, Databyte1)" << std::endl;
    uint32_t idx = rhs.m_startPos;
    for(uint32_t i = 0; i < rhs.m_length; i++)
    {
        lhs << rhs.m_entry[idx].m_time << "\t: ";
        lhs << tcd_command_names[rhs.m_entry[idx].m_cmdId] << " ";
        lhs << rhs.m_entry[idx].m_arg << std::endl;
        idx = (idx + 1) % tcd_log_buffersize;
    }
    lhs << "End of TCD MIDI Input Log" << std::endl;
    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const examine_param& rhs)
{
    //
    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, const examine_signal& rhs)
{
    //
    return lhs;
}
