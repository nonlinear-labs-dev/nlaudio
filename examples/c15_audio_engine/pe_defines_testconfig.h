/* configuration of the test project */

#pragma once

#include <stdint.h>
#include "pe_defines_config.h"

/*
 * Test 3 requires a reMote keyboard with the correct template (64: MSE 2) -> see Linuy Engine - Test 3 for details on handling
 */

/* Preset Definition */

#define testRecallSequences 8
#define testMidiModes 2

const int32_t testPresetData[testRecallSequences][lst_recall_length] = {
    /* preset 0 - default */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
                                                                                                                        // (later: FB Mix)
        0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,  0,     6080,                              // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
                                                                                                                        // (later: Gap Filter)
                                                                                                                        // (later: Flanger)
                                                                                                                        // (later: Echo)
                                                                                                                        // (later: Reverb)
        8000,  0                                                                                                        // Master
    },
    /* preset 1 - default tone */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
                                                                                                                        // (later: FB Mix)
        2000,  0,     0,     0,     0,     0,     0,     0,     0,     8000,  0,     6080,                              // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
                                                                                                                        // (later: Gap Filter)
                                                                                                                        // (later: Flanger)
                                                                                                                        // (later: Echo)
                                                                                                                        // (later: Reverb)
        8000,  0                                                                                                        // Master
    },
    /* preset 2 - testing comb filter */
    {
        0,     0,     8000,  8000,  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                   // Env A
        0,     0,     8000,  8000,  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                   // Env B
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc A
        0,     0,     0,     0,     0,     0,     0,     0,                                                             // Shp A
        9200,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc B
        0,     0,     0,     0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     0,     0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
                                                                                                                        // (later: FB Mix)
        0,     0,     0,     0,     2000,  0,     0,     0,     0,     8000,  0,     6080,                              // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
                                                                                                                        // (later: Gap Filter)
                                                                                                                        // (later: Flanger)
                                                                                                                        // (later: Echo)
                                                                                                                        // (later: Reverb)
        8000,  0                                                                                                        // Master
    },
    /* preset 3 - testing state variable filter */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     8000,  16000, 0,     0,     0,     0,     0,     0,     8000,                // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        9200,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc B
        4000,  0,     8000,  0,     8000,  0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
                                                                                                                        // (later: FB Mix)
        0,     0,     0,     0,     0,     0,     2000,  0,     0,     8000,  0,     6080,                              // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
                                                                                                                        // (later: Gap Filter)
                                                                                                                        // (later: Flanger)
                                                                                                                        // (later: Echo)
                                                                                                                        // (later: Reverb)
        8000,  0                                                                                                        // Master
    },
    /* preset 4 - testing envelope a/b split */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     0,     0,     0,     0,     800,   0,     0,                   // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     0,     0,     0,     0,     800,   0,     0,                   // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     8000,  16000, 0,     0,     0,     0,     0,     0,     8000,                // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        9200,  10000, 0,     0,     0,     8000,  16000, 0,     0,     0,     0,     0,     0,     8000,                // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
                                                                                                                        // (later: FB Mix)
        2000,  0,     2000,  0,     0,     0,     0,     0,     0,     8000,  0,     6080,                              // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
                                                                                                                        // (later: Gap Filter)
                                                                                                                        // (later: Flanger)
                                                                                                                        // (later: Echo)
                                                                                                                        // (later: Reverb)
        8000,  0                                                                                                        // Master
    },
    /* preset 5 - testing envelope c retrigger (use one voice polyphony for testing) */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env B
        12000, 9440,  8000,  12640, 4000,  14000, 0,     0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 4000,  0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        8000,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc B
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     6000,  16000, 0,     1200,  0,     8000,  0,     0,     0,     0,     0,                          // SVF
                                                                                                                        // (later: FB Mix)
        2000,  0,     0,     0,     0,     0,     0,     0,     0,     8000,  0,     6080,                              // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
                                                                                                                        // (later: Gap Filter)
                                                                                                                        // (later: Flanger)
                                                                                                                        // (later: Echo)
                                                                                                                        // (later: Reverb)
        8000,  0                                                                                                        // Master
    },
    /* preset 6 - SVF NaN issue */
    {
        0,     9440,  8000,  12640, 0,     8480,  0,     0,     0,     0,     0,     800,   0,     0,                   // Env A
        0,     9440,  8000,  12640, 0,     8480,  0,     7680,  0,     0,     0,     800,   0,     0,                   // Env B
        0,     9440,  8000,  12640, 0,     8480,  7680,  0,     0,     0,     800,   0,     0,                          // Env C
        8000,  10000, 0,     0,     0,     8000,  16000, 0,     0,     0,     0,     0,     0,     8000,                // Osc A
        2000,  0,     8000,  0,     0,     0,     0,     0,                                                             // Shp A
        9200,  10000, 0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     8000,                // Osc B
        4000,  0,     8000,  0,     8000,  0,     0,     0,                                                             // Shp B
        0,     6000,  10000, 0,     0,     5280,  0,     14000, 16000, 0,     10560, 10000, 16000, 0,     0,     0,     // Comb
        0,     0,     12000, 16000, 8000,  -6000, 8000,  16000, 0,     0,     0,     0,     0,                          // SVF
                                                                                                                        // (later: FB Mix)
        0,     0,     0,     0,     0,     0,     2000,  0,     0,     8000,  0,     6080,                              // Out Mix
        4000,  4000,  4000,  -1600, 10000, 2000,  7200,  0,                                                             // Cabinet
                                                                                                                        // (later: Gap Filter)
                                                                                                                        // (later: Flanger)
                                                                                                                        // (later: Echo)
                                                                                                                        // (later: Reverb)
        8000,  0                                                                                                        // Master
    },
    /* preset 7 - null */
    {
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                   // Env A
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                   // Env B
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                          // Env C
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                   // Osc A
        0,     0,     0,     0,     0,     0,     0,     0,                                                             // Shp A
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                   // Osc B
        0,     0,     0,     0,     0,     0,     0,     0,                                                             // Shp B
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     // Comb
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                          // SVF
                                                                                                                        // (later: FB Mix)
        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,                                 // Out Mix
        0,     0,     0,     0,     0,     0,     0,     0,                                                             // Cabinet
                                                                                                                        // (later: Gap Filter)
                                                                                                                        // (later: Flanger)
                                                                                                                        // (later: Echo)
                                                                                                                        // (later: Reverb)
        0,     0                                                                                                        // Master
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
        0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     7,     0,     0,     0,     0,     0,     0,     0,     0,
        0,     8,     9,     10,    11,    12,    13,    14,    15,    0,
        0,     1,     2,     3,     4,     5,     0,     0,     0,     0,
        0,     65,    0,     0,     0,     0,     0,     0,     0,     0,
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

const uint32_t testParamRouting[25][24] = {
    /* IGNORE group */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* ENV A */
    {
    /*  0      1      2      3      4      5      6      7      */
        1,     2,     3,     4,     5,     6,     7,     8,
        9,     13,    0,     0,     15,    10,    11,    12,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* ENV B */
    {
    /*  0      1      2      3      4      5      6      7      */
        16,    17,    18,    19,    20,    21,    22,    23,
        24,    28,    0,     0,     30,    25,    26,    27,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* ENV C */
    {
    /*  0      1      2      3      4      5      6      7      */
        31,    32,    33,    34,    35,    36,    0,     38,
        39,    43,    44,    0,     0,     40,    41,    42,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* OSC A */
    {
    /*  0      1      2      3      4      5      6      7      */
        46,    47,    48,    49,    50,    51,    52,    53,
        0,     0,     59,    57,    58,    54,    55,    56,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* SHP A */
    {
    /*  0      1      2      3      4      5      6      7      */
        60,    62,    63,    64,    65,    67,    0,     0,
        61,    0,     0,     0,     66,    0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* OSC B */
    {
    /*  0      1      2      3      4      5      6      7      */
        68,    69,    70,    71,    72,    73,    74,    75,
        0,     0,     81,    79,    80,    76,    77,    78,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* SHP B */
    {
    /*  0      1      2      3      4      5      6      7      */
        82,    84,    85,    86,    87,    89,    0,     0,
        83,    0,     0,     0,     88,    0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* OUT MIX */
    {
    /*  0      1      2      3      4      5      6      7      */
        128,   130,   132,   134,   139,   136,   137,   138,
        129,   131,   133,   135,   0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* COMB FILTER */
    {
    /*  0      1      2      3      4      5      6      7      */
        90,    91,    92,    93,    94,    95,    96,    104,
        97,    98,    99,    100,   101,   102,   103,   105,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* STATE VARIABLE FILTER */
    {
    /*  0      1      2      3      4      5      6      7      */
        106,   108,   109,   110,   0,     111,   116,   112,
        107,   113,   114,   115,   0,     0,     117,   118,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* CABINET, (later: GAP FILTER) */
    {
    /*  0      1      2      3      4      5      6      7      */
        140,   141,   142,   143,   144,   145,   146,   147,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (later: FLANGER) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (later: ECHO, REVERB) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* MASTER */
    {
    /*  0      1      2      3      4      5      6      7      */
        177,   178,   0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
    /* (none) */
    {
    /*  0      1      2      3      4      5      6      7      */
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
        0,     0,     0,     0,     0,     0,     0,     0,
    },
};
