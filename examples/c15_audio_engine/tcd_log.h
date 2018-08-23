#pragma once

#include <stdint.h>
#include <cmath>
#include <iostream>

const uint32_t tcd_log_buffersize = 1000;

const char tcd_command_names[128][4] = {
    "V",   "P",   "T",   "?83", "?84", "D",   "?86", "KU",  "U",   "?89", "?8A", "?8B", "?8C", "?8D", "?8E", "?8F",
    "VM",  "PM",  "?92", "?93", "?94", "DS",  "?96", "KD",  "UD",  "?99", "?9A", "?9B", "?9C", "?9D", "?9E", "?9F",
    "?A0", "?A1", "TU",  "?A3", "?A4", "DU",  "?A6", "FL",  "?A8", "?A9", "?AA", "?AB", "?AC", "?AD", "?AE", "PL",
    "?B0", "?B1", "TL",  "?B3", "?B4", "DL",  "?B6", "?B7", "?B8", "?B9", "?BA", "?BB", "?BC", "?BD", "?BE", "?BF",
    "?C0", "?C1", "?C2", "?C3", "?C4", "?C5", "?C6", "?C7", "?C8", "?C9", "?CA", "?CB", "?CC", "?CD", "?CE", "?CF",
    "?D0", "?D1", "?D2", "?D3", "?D4", "?D5", "?D6", "?D7", "?D8", "?D9", "?DA", "?DB", "?DC", "?DD", "?DE", "?DF",
    "?E0", "?E1", "?E2", "?E3", "?E4", "?E5", "?E6", "?E7", "?E8", "?E9", "?EA", "?EB", "?EC", "?ED", "?EE", "?EF",
    "?F0", "?F1", "?F2", "?F3", "?F4", "?F5", "?F6", "?F7", "?F8", "?F9", "?FA", "?FB", "?FC", "?FD", "?FE", "?FF",
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
