#pragma once

#include <stdint.h>
#include <cmath>
#include <iostream>

const uint32_t tcd_log_buffersize = 1000;

const char tcd_command_names[128][4] = {
    "V",   "P",   "T",   "?03", "?04", "D",   "?06", "KU",  "U",   "?09", "?0A", "?0B", "?0C", "?0D", "?0E", "?0F",
    "VM",  "PM",  "?12", "?13", "?14", "DS",  "?16", "KD",  "UD",  "?19", "?1A", "?1B", "?1C", "?1D", "?1E", "?1F",
    "?20", "?21", "TU",  "?23", "?24", "DU",  "?26", "FL",  "?28", "?29", "?2A", "?2B", "?2C", "?2D", "?2E", "PL",
    "?30", "?31", "TL",  "?33", "?34", "DL",  "?36", "?37", "?38", "?39", "?3A", "?3B", "?3C", "?3D", "?3E", "?3F",
    "?40", "?41", "?42", "?43", "?44", "?45", "?46", "?47", "?48", "?49", "?4A", "?4B", "?4C", "?4D", "?4E", "?4F",
    "?50", "?51", "?52", "?53", "?54", "?55", "?56", "?57", "?58", "?59", "?5A", "?5B", "?5C", "?5D", "?5E", "?5F",
    "?60", "?61", "?62", "?63", "?64", "?65", "?66", "?67", "?68", "?69", "?6A", "?6B", "?6C", "?6D", "?6E", "?6F",
    "?70", "?71", "?72", "?73", "?74", "?75", "?76", "?77", "?78", "?79", "?7A", "?7B", "?7C", "?7D", "?7E", "?7F",
};

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
