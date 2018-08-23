#pragma once

#include <stdint.h>
#include <ostream>
#include "pe_defines_config.h"

struct examine_tcd_input_log
{
    uint32_t m_time;
    uint32_t m_cmd_id;
    uint32_t m_arg_0;
    uint32_t m_arg_1;
};

std::ostream& operator<<(std::ostream& lhs, const examine_tcd_input_log& rhs);

struct examine_param
{
    //
};
std::ostream& operator<<(std::ostream& lhs, const examine_param& rhs);

struct examine_signal
{
    //
};
std::ostream& operator<<(std::ostream& lhs, const examine_signal& rhs);
