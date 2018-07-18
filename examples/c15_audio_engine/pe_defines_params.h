/******************************************************************************/
/** @file       pe_defines_params.h
    @date       2018-03-13
    @version    1.0
    @author     Matthias Seeber
    @brief      c15 parameter definition (according to parameter list)
                ..
    @todo
*******************************************************************************/

#pragma once

#include "pe_defines_config.h"

// define: param id, clock type, poly type, range, scale id, scale arg, postID (-1: ignore, > -1: array pos), spread (0, 1), polarity, tcd factor
// convention: define poly params with spread = 0 !!
// postId for direct copy/distribute post processing
// param id of -1 for placeholders (not part of parameter selection, use clock type 0 to prevent any rendering)

/* Parameter Definition (Test 3) */

const float param_definition[sig_number_of_params][10] = {

    // - - - ENVELOPE A - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        0,      3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 0   ENV_A_ATTACK_TIME
    {        2,      3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 1   ENV_A_DECAY1_TIME
    {        4,      2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 2   ENV_A_BREAKPOINT_LEVEL
    {        6,      3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 3   ENV_A_DECAY2_TIME
    {        8,      2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 4   ENV_A_SUSTAIN_LEVEL
    {        10,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16160  },         // 5   ENV_A_RELEASE_TIME
    {        12,     2,      0,      300,    7,      0,      -1,     0,      1,      7200   },         // 6   ENV_A_GAIN
    {        14,     0,      0,      256,    0,      0,      -1,     0,      0,      15360  },         // 7   ENV_A_LEVEL_VELOCITY
    {        15,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 8   ENV_A_ATTACK_VELOCITY
    {        16,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 9   ENV_A_RELEASE_VELOCITY
    {        17,     0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 10  ENV_A_LEVEL_KEYTRACK
    {        18,     0,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 11  ENV_A_TIME_KEYTRACK
    {        294,    0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 12  ENV_A_ATTACK_CURVE
    {        -1,     0,      0,      1,      0,      0,      -1,     0,      0,      0      },         // 13  (RETRIGGER HARDNESS PLACEHOLDER)
    {        328,    0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 14  ENV_A_SPLIT

    // - - - ENVELOPE B - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        19,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 15  ENV_B_ATTACK_TIME
    {        21,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 16  ENV_B_DECAY1_TIME
    {        23,     2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 17  ENV_B_BREAKPOINT_LEVEL
    {        25,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 18  ENV_B_DECAY2_TIME
    {        27,     2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 19  ENV_B_SUSTAIN_LEVEL
    {        29,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16160  },         // 20  ENV_B_RELEASE_TIME
    {        31,     2,      0,      300,    7,      0,      -1,     0,      1,      7200   },         // 21  ENV_B_GAIN
    {        33,     0,      0,      256,    0,      0,      -1,     0,      0,      15360  },         // 22  ENV_B_LEVEL_VELOCITY
    {        34,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 23  ENV_B_ATTACK_VELOCITY
    {        35,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 24  ENV_B_RELEASE_VELOCITY
    {        36,     0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 25  ENV_B_LEVEL_KEYTRACK
    {        37,     0,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 26  ENV_B_TIME_KEYTRACK
    {        295,    0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 27  ENV_B_ATTACK_CURVE
    {        -1,     0,      0,      1,      0,      0,      -1,     0,      0,      0      },         // 28  (RETRIGGER HARDNESS PLACEHOLDER)
    {        329,    0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 29  ENV_B_SPLIT

    // - - - ENVELOPE C - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        38,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 30  ENV_C_ATTACK_TIME
    {        40,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 31  ENV_C_DECAY1_TIME
    {        42,     2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 32  ENV_C_BREAKPOINT_LEVEL
    {        44,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16000  },         // 33  ENV_C_DECAY2_TIME
    {        297,    2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 34  ENV_C_SUSTAIN_LEVEL
    {        46,     3,      0,      16000,  12,     -20,    -1,     0,      0,      16160  },         // 35  ENV_C_RELEASE_TIME
    {        -1,     0,      0,      1,      0,      0,      -1,     0,      0,      0      },         // 36  (GAIN PLACEHOLDER)
    {        48,     0,      0,      256,    0,      0,      -1,     0,      0,      15360  },         // 37  ENV_C_LEVEL_VELOCITY
    {        49,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 38  ENV_C_ATTACK_VELOCITY
    {        50,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 39  ENV_C_RELEASE_VELOCITY
    {        51,     0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 40  ENV_C_LEVEL_KEYTRACK
    {        52,     0,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 41  ENV_C_TIME_KEYTRACK
    {        296,    0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 42  ENV_C_ATTACK_CURVE
    {        330,    0,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 43  ENV_C_RETRIGGER_HARDNESS
    {        -1,     0,      0,      1,      0,      0,      -1,     0,      0,      0      },         // 44  (SPLIT PLACEHOLDER)

    // - - - OSCILLATOR A - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        53,     3,      0,      100,    8,      -20,    -1,     0,      0,      15000  },         // 45  OSC_A_PITCH
    {        55,     3,      0,      10000,  0,      0,      -1,     0,      0,      10000  },         // 46  OSC_A_PITCH_KEYTRACK
    {        56,     3,      0,      100,    0,      0,      -1,     0,      1,      8000   },         // 47  OSC_A_PITCH_ENV_C
    {        57,     3,      0,      16000,  4,      0.95,   -1,     0,      0,      16000  },         // 48  OSC_A_FLUCTUATION
    {        59,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 49  OSC_A_FLUCTUATION_ENV_C
    {        60,     2,      0,      8000,   4,      0.5,    -1,     0,      1,      8000   },         // 50  OSC_A_PM_SELF
    {        62,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 51  OSC_A_PM_SELF_ENV_A
    {        63,     3,      0,      8000,   0,      0,      9,      1,      1,      8000   },         // 52  OSC_A_PM_SELF_SHAPER
    {        64,     2,      0,      8000,   4,      1,      -1,     0,      1,      8000   },         // 53  OSC_A_PM_B
    {        66,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 54  OSC_A_PM_B_ENV_B
    {        67,     3,      0,      8000,   0,      0,      11,      1,      1,      8000   },        // 55  OSC_A_PM_B_SHAPER
    {        68,     2,      0,      8000,   4,      0.5,    -1,     0,      1,      8000   },         // 56  OSC_A_PM_FB
    {        70,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 57  OSC_A_PM_FB_ENV_C
    {        303,    3,      0,      200,    9,      80,     -1,     0,      0,      12000  },         // 58  OSC_A_CHIRP

    // - - - SHAPER A - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        71,     2,      0,      200,    10,     0.18,   -1,     0,      0,      10000  },         // 59  SHP_A_DRIVE
    {        73,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 60  SHP_A_DRIVE_ENV_A
    {        74,     3,      0,      16000,  0,      0,      15,     1,      0,      16000  },         // 61  SHP_A_FOLD
    {        75,     3,      0,      16000,  0,      0,      16,     1,      0,      16000  },         // 62  SHP_A_ASYMETRY
    {        76,     2,      0,      8000,   0,      0,      17,     1,      1,      8000   },         // 63  SHP_A_MIX
    {        78,     2,      0,      16000,  5,      0,      18,     1,      0,      16000  },         // 64  SHP_A_FEEDBACK_MIX
    {        80,     3,      0,      16000,  0,      0,      -1,     1,      0,      16000  },         // 65  SHP_A_FEEDBACK_ENV_C
    {        81,     2,      0,      16000,  0,      0,      20,     1,      0,      16000  },         // 66  SHP_A_RINGMOD

    // - - - OSCILLATOR B - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        83,     3,      0,      100,    8,      -20,    -1,     0,      0,      15000  },         // 67  OSC_B_PITCH
    {        85,     3,      0,      10000,  0,      0,      -1,     0,      0,      10000  },         // 68  OSC_B_PITCH_KEYTRACK
    {        86,     3,      0,      100,    0,      0,      -1,     0,      1,      8000   },         // 69  OSC_B_PITCH_ENV_C
    {        87,     3,      0,      16000,  4,      0.95,   -1,     0,      0,      16000  },         // 70  OSC_B_FLUCTUATION
    {        89,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 71  OSC_B_FLUCTUATION_ENV_C
    {        90,     2,      0,      8000,   4,      0.5,    -1,     0,      1,      8000   },         // 72  OSC_B_PM_SELF
    {        92,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 73  OSC_B_PM_SELF_ENV_B
    {        93,     3,      0,      8000,   0,      0,      24,     1,      1,      8000   },         // 74  OSC_B_PM_SELF_SHAPER
    {        94,     2,      0,      8000,   4,      1,      -1,     0,      1,      8000   },         // 75  OSC_B_PM_A
    {        96,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 76  OSC_B_PM_A_ENV_A
    {        97,     3,      0,      8000,   0,      0,      26,     1,      1,      8000   },         // 77  OSC_B_PM_A_SHAPER
    {        98,     2,      0,      8000,   4,      0.5,    -1,     0,      1,      8000   },         // 78  OSC_B_PM_FB
    {        100,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 79  OSC_B_PM_FB_ENV_C
    {        304,    3,      0,      200,    9,      80,     -1,     0,      0,      12000  },         // 80  OSC_B_CHIRP

    // - - - SHAPER B - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        101,    2,      0,      200,    10,     0.18,   -1,     0,      0,      10000  },         // 81  SHP_B_DRIVE
    {        103,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 82  SHP_B_DRIVE_ENV_B
    {        104,    3,      0,      16000,  0,      0,      30,     1,      0,      16000  },         // 83  SHP_B_FOLD
    {        105,    3,      0,      16000,  0,      0,      31,     1,      0,      16000  },         // 84  SHP_B_ASYMETRY
    {        106,    2,      0,      8000,   0,      0,      32,     1,      1,      8000   },         // 85  SHP_B_MIX
    {        108,    2,      0,      16000,  5,      0,      33,     1,      0,      16000  },         // 86  SHP_B_FEEDBACK_MIX
    {        110,    3,      0,      16000,  0,      0,      -1,     1,      0,      16000  },         // 87  SHP_B_FEEDBACK_ENV_C
    {        111,    2,      0,      16000,  0,      0,      35,     1,      0,      16000  },         // 88  SHP_B_RINGMOD

    // - - - COMB FILTER - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        113,    2,      0,      16000,  6,      1,      36,     1,      0,      16000  },         // 89  CMB_AB
    {        115,    3,      0,      100,    9,      0,      -1,     0,      0,      12000  },         // 90  CMB_PITCH
    {        117,    3,      0,      10000,  0,      0,      -1,     0,      0,      10500  },         // 91  CMB_PITCH_KT
    {        118,    3,      0,      100,    0,      0,      -1,     0,      1,      8000   },         // 92  CMB_PITCH_ENV_C
    {        119,    3,      0,      80,     0,      0,      -1,     0,      1,      8000   },         // 93  CMB_DECAY
    {        121,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 94  CMB_DECAY_KT
    {        305,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 95  CMB_DECAY_GATE
    {        123,    3,      0,      100,    9,      0,      -1,     0,      0,      14000  },         // 96  CMB_ALLPASS_TUNE
    {        125,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 97  CMB_ALLPASS_KT
    {        126,    3,      0,      100,    0,      0,      -1,     0,      1,      8000   },         // 98  CMB_ALLPASS_ENV_C
    {        127,    3,      0,      16000,  0,      0,      42,     1,      0,      16000  },         // 99  CMB_ALLPASS_RESON
    {        129,    3,      0,      100,    9,      40,     -1,     0,      0,      10000  },         // 100 CMB_HICUT
    {        131,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 101 CMB_HICUT_KT
    {        132,    3,      0,      80,     0,      0,      -1,     0,      1,      8000   },         // 102 CMB_HICUT_ENV_C
    {        133,    3,      0,      8000,   4,      0.9,    44,     1,      1,      8000   },         // 103 CMB_PM
    {        135,    3,      0,      16000,  2,      1,      45,     1,      0,      16000  },         // 104 CMB_PM_AB

    // - - - STATE VARIABLE FILTER  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        136,    2,      0,      16000,  2,      1,      46,     1,      0,      16000  },         // 105 SVF_AB
    {        138,    2,      0,      8000,   0,      0,      47,     1,      1,      8000   },         // 106 SVF_COMB_MIX
    {        140,    3,      0,      100,    9,      20,     -1,     0,      0,      12000  },         // 107 SVF_CUTOFF
    {        142,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 108 SVF_CUTOFF_KT
    {        143,    3,      0,      80,     0,      0,      -1,     0,      1,      8000   },         // 109 SVF_CUTOFF_ENV_C
    {        148,    3,      0,      100,    1,      0.5,    -1,     0,      1,      6000   },         // 110 SVF_SPREAD
    {        153,    3,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 111 SVF_FM
    {        144,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 112 SVF_RESONANCE
    {        146,    3,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 113 SVF_RESONANCE_KT
    {        147,    3,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 114 SVF_RESONANCE_ENV_C
    {        150,    2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 115 SVF_LBH
    {        152,    2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 116 SVF_PARALLEL
    {        155,    3,      0,      16000,  2,      1,      59,     1,      0,      16000  },         // 117 SVF_FM_AB

    // - - - OUTPUT MIXER - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        169,    2,      0,      4000,   0,      0,      -1,     0,      1,      8000   },         // 118 OUT_A_LEVEL
    {        171,    2,      0,      16000,  0,      0.5,    -1,     0,      1,      8000   },         // 119 OUT_A_PAN
    {        172,    2,      0,      4000,   0,      0,      -1,     0,      1,      8000   },         // 120 OUT_B_LEVEL
    {        174,    2,      0,      16000,  0,      0.5,    -1,     0,      1,      8000   },         // 121 OUT_B_PAN
    {        175,    2,      0,      4000,   0,      0,      -1,     0,      1,      8000   },         // 122 OUT_COMB_LEVEL
    {        177,    2,      0,      16000,  0,      0.5,    -1,     0,      1,      8000   },         // 123 OUT_COMB_PAN
    {        178,    2,      0,      4000,   0,      0,      -1,     0,      1,      8000   },         // 124 OUT_SVF_LEVEL
    {        180,    2,      0,      16000,  0,      0.5,    -1,     0,      1,      8000   },         // 125 OUT_SVF_PAN
    {        181,    2,      0,      200,    11,     0.25,   68,     1,      0,      10000  },         // 126 OUT_DRIVE
    {        183,    3,      0,      16000,  0,      0,      69,     1,      0,      16000  },         // 127 OUT_FOLD
    {        184,    3,      0,      16000,  0,      0,      70,     1,      0,      16000  },         // 128 OUT_ASYMETRY
    {        185,    2,      0,      16000,  4,      2.56,   71,     0,      0,      16000  },         // 129 OUT_LEVEL

    // - - - MASTER - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        247,    2,      0,      16000,  4,      4,      81,     0,      0,      16000  },         // 130 MASTER_VOLUME
    {        248,    3,      0,      100,    0,      0,      -1,     0,      1,      4800   },         // 131 MASTER_TUNE

    // - - - POLY KEY EVENT - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        400,    0,      1,      14400,  0,      0,      -1,     0,      1,      7200   },         // 132 KEY_PHASE_A
    {        401,    0,      1,      14400,  0,      0,      -1,     0,      1,      7200   },         // 133 KEY_PHASE_B
    {        406,    0,      1,      1000,   0,      0,      -1,     0,      1,      1000   },         // 134 KEY_NOTE_PITCH
    {        407,    0,      1,      8000,   0,      0,      -1,     0,      1,      8000   },         // 135 KEY_VOICE_PAN
    {        408,    0,      1,      16000,  0,      0,      -1,     0,      0,      16000  },         // 136 KEY_ENV_C_RATE
    {        409,    0,      1,      1,      0,      0,      -1,     0,      0,      1      }          // 137 KEY_VOICE_STEAL

};

/* Utility Parameters */

const float utility_definition[sig_number_of_utilities][3] = {
    //       RANGE   SCALE   (ARG)
    {        4096,   0,      0          },                                      // velocity definition (for now: tcd range 4096)
    {        100,    0,      400        }                                       // pitch reference (A3)
};
