#pragma once

#include <stdint.h>
#include <cmath>
#include <iostream>

const uint32_t tcd_log_buffersize = 10;

struct logEntry
{
    uint32_t m_elapsedSamples = 0;
    uint32_t m_commandID = 0;
    uint32_t m_commandArgs[2] = {0, 0};

    void set(uint32_t _delta, uint32_t _cmdID, uint32_t _arg1, uint32_t _arg2);
    void get();
};

struct tcd_log
{
    uint32_t m_timestamp = 0;
    uint32_t m_index = 0;
    uint32_t m_length = 0;
    uint32_t m_startPos = 0;
    logEntry m_entry[tcd_log_buffersize];

    void reset();
    void tick();
    void add(uint32_t _cmdID, uint32_t _arg1, uint32_t _arg2);
    void get();
};
