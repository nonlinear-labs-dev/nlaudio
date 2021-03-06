/* configuration of the test project */

#pragma once

#include <stdint.h>
#include "pe_defines_config.h"
#include "pe_defines_labels.h"

/*
 * Test 3 requires a reMote keyboard with the correct template (64: MSE 2) -> see Linuy Engine - Test 3 for details on handling
 */

/* Preset Definition */

#define testRecallSequences 8
#define testMidiModes 2

const int32_t testPresetData[testRecallSequences][lst_recall_length] = {
    /* preset 0 - default */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
        0,     0,     0,     8000,  0,     8000,  0,     0,     6080,                                                   // FB Mix
        0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,  0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
    /* preset 1 - default tone */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
        0,     0,     0,     8000,  0,     8000,  0,     0,     6080,                                                   // FB Mix
        2000,  0,     0,     0,     0,     0,     0,     0,     0,     8000,  0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
    /* preset 2 - testing comb filter */
    {
        0,     0,     8000,  8000,  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     // Env A
        0,     0,     8000,  8000,  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     // Env B
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        0,     0,     0,     0,     0,     0,     0,     0,                                                             // Shp A
        9200,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        0,     0,     0,     0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     0,     0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
        0,     0,     0,     8000,  0,     8000,  0,     0,     6080,                                                   // FB Mix
        0,     0,     0,     0,     2000,  0,     0,     0,     0,     8000,  0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
    /* preset 3 - testing state variable filter */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     8000,  16000, 0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        9200,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        4000,  0,     8000,  0,     8000,  0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
        0,     0,     0,     8000,  0,     8000,  0,     0,     6080,                                                   // FB Mix
        0,     0,     0,     0,     0,     0,     2000,  0,     0,     8000,  0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
    /* preset 4 - testing envelope a/b split */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     0,     0,     0,     0,     0,     0,     800,   0,     0,     // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     0,     0,     0,     0,     0,     0,     800,   0,     0,     // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     8000,  16000, 0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        9200,  10000, 0,     0,     0,     8000,  16000, 0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
        0,     0,     0,     8000,  0,     8000,  0,     0,     6080,                                                   // FB Mix
        2000,  0,     2000,  0,     0,     0,     0,     0,     0,     8000,  0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
    /* preset 5 - testing envelope c retrigger (use one voice polyphony for testing) */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env B
        12000, 9440,  8000,  12640, 4000,  14000, 0,     0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 4000,  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
        0,     0,     0,     8000,  0,     8000,  0,     0,     6080,                                                   // FB Mix
        2000,  0,     0,     0,     0,     0,     0,     0,     0,     8000,  0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
    /* preset 6 - SVF NaN issue */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     0,     0,     0,     0,     0,     0,     800,   0,     0,     // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     8000,  16000, 0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        9200,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        4000,  0,     8000,  0,     8000,  0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     12000, 16000, 8000,  -6000, 8000,  16000, 0,     0,     0,     0,     0,                          // SVF
        0,     0,     0,     8000,  0,     8000,  0,     0,     6080,                                                   // FB Mix
        0,     0,     0,     0,     0,     0,     2000,  0,     0,     8000,  0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
#if 0
    /* preset 7 - SVF NAN (handmade copy of "Linux Engine NAN" Bank) */
    {
        0,     9440,  8000,  12640, 0,     8560,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        2000,  0,     8000,  0,     8000,  0,     0,     0,                                                             // Shp A
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6400,  16000, 0,     4900,  -8000, 12800, 0,     0,     4640,  -2560, 16000,                      // SVF
        0,     0,     0,     8000,  0,     8000,  0,     0,     6080,                                                   // FB Mix
        0,     0,     0,     0,     0,     0,     4320,  0,     0,     8000,  0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
#endif
    /* preset 7 - feedback mixer asym issue */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     0,     0,     800,   0,     0,     // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc A
        0,     0,     0,     0,     0,     0,     0,     0,                                                             // Shp A
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,         // Osc B
        0,     0,     0,     0,     0,     16000, 0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
        4000,  0,     0,     8000,  0,     0,     0,     0,     6080,                                                   // FB Mix
        0,     0,     4000,  0,     0,     0,     0,     0,     0,     0,     0,     6080,  0,                          // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
        4800,  0,     1200,  8000,  0,     0,                                                                           // Gap Filter
        0,     7200,  5072,  3963,  0,     0,     4000,  12000, 0,     0,     0,     14000,                             // Flanger
        6928,  0,     8000,  8000,  12000, 0,     16000,                                                                // Echo
        5280,  5280,  8000,  4000,  0,     16000,                                                                       // Reverb
        8000,  0,                                                                                                       // Master
        1,     0,     0,     0                                                                                          // Unison
    },
};

const uint32_t testMidiMapping[testMidiModes][128] = {
    /* - - - - - - - Mode 1 - Group Select - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    {
    /*  0      1      2      3      4      5      6      7      8      9     */
        0,     33,    34,    35,    36,    37,    38,    39,    40,    0,
        0,     41,    42,    43,    44,    45,    46,    47,    48,    0,
        0,     49,    50,    51,    52,    53,    54,    55,    56,    0,
        0,     1,     2,     3,     4,     5,     0,     0,     0,     0,
        0,     65,    66,    67,    68,    69,    70,    71,    72,    0,
        0,     73,    74,    75,    76,    77,    78,    79,    80,    0,
        0,     81,    82,    83,    84,    85,    86,    87,    88,    0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* - - - - - - - Mode 2 - Global Stuff - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    {
    /*  0      1      2      3      4      5      6      7      8      9     */
        0,     6,     18,    19,    20,    0,     0,     0,     0,     0,
        0,     7,     16,    17,    0,     0,     0,     0,     0,     0,
        0,     8,     9,     10,    11,    12,    13,    14,    15,    0,
        0,     1,     2,     3,     4,     5,     0,     0,     0,     0,
        0,     65,    67,    68,    0,     0,     0,     0,     0,     0,
        0,     66,    0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
};

const int32_t testParamRouting[25][24] = {
    /* IGNORE group */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* ENV A */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_EA_ATT,     P_EA_DEC1,    P_EA_BP,      P_EA_DEC2,    P_EA_SUS,     P_EA_REL,     P_EA_GAIN,    P_EA_LV,
        P_EA_AV,      P_EA_AC,      P_EA_D1V,     P_EA_D2V,     P_EA_SPL,     P_EA_RV,      P_EA_LKT,     P_EA_TKT,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* ENV B */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_EB_ATT,     P_EB_DEC1,    P_EB_BP,      P_EB_DEC2,    P_EB_SUS,     P_EB_REL,     P_EB_GAIN,    P_EB_LV,
        P_EB_AV,      P_EB_AC,      P_EB_D1V,     P_EB_D2V,     P_EB_SPL,     P_EB_RV,      P_EB_LKT,     P_EB_TKT,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* ENV C */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_EC_ATT,     P_EC_DEC1,    P_EC_BP,      P_EC_DEC2,    P_EC_SUS,     P_EC_REL,     -1,           P_EC_LV,
        P_EC_AV,      P_EC_AC,      -1,           -1,           P_EC_RH,      P_EC_RV,      P_EC_LKT,     P_EC_TKT,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* OSC A */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_OA_P,       P_OA_PKT,     P_OA_PEC,     P_OA_F,       P_OA_FEC,     P_OA_PMS,     P_OA_PMSEA,   P_OA_PMSSH,
        -1,           P_OA_PHS,     P_OA_CHI,     P_OA_PMF,     P_OA_PMFEC,   P_OA_PMB,     P_OA_PMBEB,   P_OA_PMBSH,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* SHP A */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_SA_DRV,     P_SA_FLD,     P_SA_ASM,     P_SA_MIX,     P_SA_FBM,     P_SA_RM,      -1,           -1,
        P_SA_DEA,     -1,           -1,           -1,           P_SA_FBEC,    -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* OSC B */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_OB_P,       P_OB_PKT,     P_OB_PEC,     P_OB_F,       P_OB_FEC,     P_OB_PMS,     P_OB_PMSEB,   P_OB_PMSSH,
        -1,           P_OB_PHS,     P_OB_CHI,     P_OB_PMF,     P_OB_PMFEC,   P_OB_PMA,     P_OB_PMAEA,   P_OB_PMASH,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* SHP B */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_SB_DRV,     P_SB_FLD,     P_SB_ASM,     P_SB_MIX,     P_SB_FBM,     P_SB_RM,      -1,           -1,
        P_SB_DEB,     -1,           -1,           -1,           P_SB_FBEC,    -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* OUT MIX */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_OM_AL,      P_OM_BL,      P_OM_CL,      P_OM_SL,      P_OM_LVL,     P_OM_DRV,     P_OM_FLD,     P_OM_ASM,
        P_OM_AP,      P_OM_BP,      P_OM_CP,      P_OM_SP,      P_OM_KP,      -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* COMB FILTER */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_CMB_AB,     P_CMB_P,      P_CMB_PKT,    P_CMB_PEC,    P_CMB_D,      P_CMB_DKT,    P_CMB_DG,     P_CMB_PM,
        P_CMB_APT,    P_CMB_APKT,   P_CMB_APEC,   P_CMB_APR,    P_CMB_LP,     P_CMB_LPKT,   P_CMB_LPEC,   P_CMB_PMAB,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* STATE VARIABLE FILTER */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_SVF_AB,     P_SVF_CUT,    P_SVF_CKT,    P_SVF_CEC,    -1,           P_SVF_SPR,    P_SVF_LBH,    P_SVF_FM,
        P_SVF_CMB,    P_SVF_RES,    P_SVF_RKT,    P_SVF_REC,    -1,           -1,           P_SVF_PAR,    P_SVF_FMAB,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* CABINET,     GAP FILTER */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_CAB_DRV,    P_CAB_FLD,    P_CAB_ASM,    P_CAB_TILT,   P_CAB_LPF,    P_CAB_HPF,    P_CAB_LVL,    P_CAB_MIX,
        P_GAP_CNT,    P_GAP_STE,    P_GAP_GAP,    P_GAP_RES,    P_GAP_BAL,    P_GAP_MIX,    -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* FLANGER */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_FLA_TMOD,   P_FLA_PHS,    P_FLA_RTE,    P_FLA_TIME,   P_FLA_STE,    P_FLA_FB,     P_FLA_CFB,    P_FLA_MIX,
        P_FLA_ENV,    P_FLA_APM,    P_FLA_APT,    P_FLA_LPF,    -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* ECHO,     REVERB */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_DLY_SND,    P_DLY_TIME,   P_DLY_STE,    P_DLY_FB,     P_DLY_CFB,    P_DLY_LPF,    P_DLY_MIX,          -1,
        P_REV_SND,    P_REV_SIZE,   P_REV_PRE,    P_REV_COL,    P_REV_CHO,    P_REV_MIX,    -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* FEEDBACK MIX */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_FBM_CMB,    P_FBM_SVF,    P_FBM_FX,     P_FBM_REV,    P_FBM_DRV,    P_FBM_FLD,    P_FBM_ASM,    P_FBM_LVL,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           P_FBM_LKT,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* MASTER,     UNISON */
    {
    /*  0             1             2             3             4             5             6             7            */
        P_MA_V,       P_MA_T,       P_MA_SH,      -1,           -1,           -1,           -1,           -1,
        P_UN_V,       P_UN_DET,     P_UN_PHS,     P_UN_PAN,     -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
    /* (none) */
    {
    /*  0             1             2             3             4             5             6             7            */
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
        -1,           -1,           -1,           -1,           -1,           -1,           -1,           -1,
    },
};
