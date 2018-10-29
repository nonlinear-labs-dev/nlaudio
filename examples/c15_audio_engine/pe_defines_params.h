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
    {        0,      3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 0   ENV_A_ATTACK_TIME
    {        2,      3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 1   ENV_A_DECAY1_TIME
    {        4,      2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 2   ENV_A_BREAKPOINT_LEVEL
    {        6,      3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 3   ENV_A_DECAY2_TIME
    {        8,      2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 4   ENV_A_SUSTAIN_LEVEL
    {        10,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16160  },         // 5   ENV_A_RELEASE_TIME
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
    {        19,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 15  ENV_B_ATTACK_TIME
    {        21,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 16  ENV_B_DECAY1_TIME
    {        23,     2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 17  ENV_B_BREAKPOINT_LEVEL
    {        25,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 18  ENV_B_DECAY2_TIME
    {        27,     2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 19  ENV_B_SUSTAIN_LEVEL
    {        29,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16160  },         // 20  ENV_B_RELEASE_TIME
    {        31,     2,      0,      300,    7,      0,      -1,     0,      1,      7200   },         // 21  ENV_B_GAIN
    {        33,     0,      0,      256,    0,      0,      -1,     0,      0,      15360  },         // 22  ENV_B_LEVEL_VELOCITY
    {        34,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 23  ENV_B_ATTACK_VELOCITY
    {        35,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 24  ENV_B_RELEASE_VELOCITY
    {        36,     0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 25  ENV_B_LEVEL_KEYTRACK
    {        37,     0,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 26  ENV_B_TIME_KEYTRACK
    {        295,    0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 27  ENV_B_ATTACK_CURVE
    {        -1,     0,      0,      1,      0,      0,      -1,     0,      0,      0      },         // 28  (RETRIGGER HARDNESS PLACEHOLDER)
    {        330,    0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 29  ENV_B_SPLIT

    // - - - ENVELOPE C - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        38,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 30  ENV_C_ATTACK_TIME
    {        40,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 31  ENV_C_DECAY1_TIME
    {        42,     2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 32  ENV_C_BREAKPOINT_LEVEL
    {        44,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16000  },         // 33  ENV_C_DECAY2_TIME
    {        297,    2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 34  ENV_C_SUSTAIN_LEVEL
    {        46,     3,      0,      16000,  13,     -20,    -1,     0,      0,      16160  },         // 35  ENV_C_RELEASE_TIME
    {        -1,     0,      0,      1,      0,      0,      -1,     0,      0,      0      },         // 36  (GAIN PLACEHOLDER)
    {        48,     0,      0,      256,    0,      0,      -1,     0,      0,      15360  },         // 37  ENV_C_LEVEL_VELOCITY
    {        49,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 38  ENV_C_ATTACK_VELOCITY
    {        50,     0,      0,      200,    0,      0,      -1,     0,      0,      12000  },         // 39  ENV_C_RELEASE_VELOCITY
    {        51,     0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 40  ENV_C_LEVEL_KEYTRACK
    {        52,     0,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 41  ENV_C_TIME_KEYTRACK
    {        296,    0,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 42  ENV_C_ATTACK_CURVE
    {        332,    0,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 43  ENV_C_RETRIGGER_HARDNESS
    {        -1,     0,      0,      1,      0,      0,      -1,     0,      0,      0      },         // 44  (SPLIT PLACEHOLDER)

    // - - - OSCILLATOR A - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        53,     3,      0,      100,    8,      -20,    -1,     0,      0,      15000  },         // 45  OSC_A_PITCH
    {        55,     3,      0,      10000,  0,      0,      -1,     0,      0,      10000  },         // 46  OSC_A_PITCH_KEYTRACK
    {        56,     3,      0,      100,    0,      0,      -1,     0,      1,      8000   },         // 47  OSC_A_PITCH_ENV_C
    {        57,     3,      0,      16000,  4,      0.95f,  -1,     0,      0,      16000  },         // 48  OSC_A_FLUCTUATION
    {        59,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 49  OSC_A_FLUCTUATION_ENV_C
    {        60,     2,      0,      8000,   4,      0.5f,   -1,     0,      1,      8000   },         // 50  OSC_A_PM_SELF
    {        62,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 51  OSC_A_PM_SELF_ENV_A
    {        63,     3,      0,      8000,   0,      0,      10,     1,      1,      8000   },         // 52  OSC_A_PM_SELF_SHAPER
    {        64,     2,      0,      8000,   4,      1,      -1,     0,      1,      8000   },         // 53  OSC_A_PM_B
    {        66,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 54  OSC_A_PM_B_ENV_B
    {        67,     3,      0,      8000,   0,      0,      12,     1,      1,      8000   },         // 55  OSC_A_PM_B_SHAPER
    {        68,     2,      0,      8000,   4,      0.5f,   -1,     0,      1,      8000   },         // 56  OSC_A_PM_FB
    {        70,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 57  OSC_A_PM_FB_ENV_C
    {        301,    1,      0,      14400,  0,      0,      14,     1,      1,      7200   },         // 58  OSC_A_PHASE
    {        303,    3,      0,      200,    9,      80,     -1,     0,      0,      12000  },         // 59  OSC_A_CHIRP

    // - - - SHAPER A - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        71,     2,      0,      200,    10,     0.18f,  -1,     0,      0,      10000  },         // 60  SHP_A_DRIVE
    {        73,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 61  SHP_A_DRIVE_ENV_A (later maybe fast type)
#if test_fast_fold_asym == 0
    {        74,     3,      0,      16000,  0,      0,      17,     1,      0,      16000  },         // 62  SHP_A_FOLD (later maybe fast type)
    {        75,     3,      0,      16000,  0,      0,      18,     1,      0,      16000  },         // 63  SHP_A_ASYMETRY (later maybe fast type)
#elif test_fast_fold_asym == 1
    {        74,     2,      0,      16000,  0,      0,      17,     1,      0,      16000  },         // 62  SHP_A_FOLD (later maybe fast type)
    {        75,     2,      0,      16000,  0,      0,      18,     1,      0,      16000  },         // 63  SHP_A_ASYMETRY (later maybe fast type)
#endif
    {        76,     2,      0,      8000,   0,      0,      19,     1,      1,      8000   },         // 64  SHP_A_MIX
    {        78,     2,      0,      16000,  5,      0,      20,     1,      0,      16000  },         // 65  SHP_A_FEEDBACK_MIX
    {        80,     3,      0,      16000,  0,      0,      -1,     1,      0,      16000  },         // 66  SHP_A_FEEDBACK_ENV_C
    {        81,     2,      0,      16000,  0,      0,      22,     1,      0,      16000  },         // 67  SHP_A_RINGMOD

    // - - - OSCILLATOR B - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        83,     3,      0,      100,    8,      -20,    -1,     0,      0,      15000  },         // 68  OSC_B_PITCH
    {        85,     3,      0,      10000,  0,      0,      -1,     0,      0,      10000  },         // 69  OSC_B_PITCH_KEYTRACK
    {        86,     3,      0,      100,    0,      0,      -1,     0,      1,      8000   },         // 70  OSC_B_PITCH_ENV_C
    {        87,     3,      0,      16000,  4,      0.95f,  -1,     0,      0,      16000  },         // 71  OSC_B_FLUCTUATION
    {        89,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 72  OSC_B_FLUCTUATION_ENV_C
    {        90,     2,      0,      8000,   4,      0.5f,   -1,     0,      1,      8000   },         // 73  OSC_B_PM_SELF
    {        92,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 74  OSC_B_PM_SELF_ENV_B
    {        93,     3,      0,      8000,   0,      0,      26,     1,      1,      8000   },         // 75  OSC_B_PM_SELF_SHAPER
    {        94,     2,      0,      8000,   4,      1,      -1,     0,      1,      8000   },         // 76  OSC_B_PM_A
    {        96,     3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 77  OSC_B_PM_A_ENV_A
    {        97,     3,      0,      8000,   0,      0,      28,     1,      1,      8000   },         // 78  OSC_B_PM_A_SHAPER
    {        98,     2,      0,      8000,   4,      0.5f,   -1,     0,      1,      8000   },         // 79  OSC_B_PM_FB
    {        100,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 80  OSC_B_PM_FB_ENV_C
    {        302,    1,      0,      14400,  0,      0,      30,     1,      1,      7200   },         // 81  OSC_B_PHASE
    {        304,    3,      0,      200,    9,      80,     -1,     0,      0,      12000  },         // 82  OSC_B_CHIRP

    // - - - SHAPER B - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        101,    2,      0,      200,    10,     0.18f,  -1,     0,      0,      10000  },         // 83  SHP_B_DRIVE
    {        103,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 84  SHP_B_DRIVE_ENV_B (later maybe fast type)
#if test_fast_fold_asym == 0
    {        104,    3,      0,      16000,  0,      0,      33,     1,      0,      16000  },         // 85  SHP_B_FOLD (later maybe fast type)
    {        105,    3,      0,      16000,  0,      0,      34,     1,      0,      16000  },         // 86  SHP_B_ASYMETRY (later maybe fast type)
#elif test_fast_fold_asym == 1
    {        104,    2,      0,      16000,  0,      0,      33,     1,      0,      16000  },         // 85  SHP_B_FOLD (later maybe fast type)
    {        105,    2,      0,      16000,  0,      0,      34,     1,      0,      16000  },         // 86  SHP_B_ASYMETRY (later maybe fast type)
#endif
    {        106,    2,      0,      8000,   0,      0,      35,     1,      1,      8000   },         // 87  SHP_B_MIX
    {        108,    2,      0,      16000,  5,      0,      36,     1,      0,      16000  },         // 88  SHP_B_FEEDBACK_MIX
    {        110,    3,      0,      16000,  0,      0,      -1,     1,      0,      16000  },         // 89  SHP_B_FEEDBACK_ENV_C
    {        111,    2,      0,      16000,  0,      0,      38,     1,      0,      16000  },         // 90  SHP_B_RINGMOD

    // - - - COMB FILTER - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        113,    2,      0,      16000,  6,      1,      39,     1,      0,      16000  },         // 91  CMB_AB
    {        115,    3,      0,      100,    9,      0,      -1,     0,      0,      12000  },         // 92  CMB_PITCH
    {        117,    3,      0,      10000,  0,      0,      -1,     0,      0,      10500  },         // 93  CMB_PITCH_KT
    {        118,    3,      0,      100,    0,      0,      -1,     0,      1,      8000   },         // 94  CMB_PITCH_ENV_C
    {        119,    3,      0,      80,     0,      0,      -1,     0,      1,      8000   },         // 95  CMB_DECAY
    {        121,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 96  CMB_DECAY_KT
    {        305,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 97  CMB_DECAY_GATE
    {        123,    3,      0,      100,    9,      0,      -1,     0,      0,      14000  },         // 98  CMB_ALLPASS_TUNE
    {        125,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 99  CMB_ALLPASS_KT
    {        126,    3,      0,      100,    0,      0,      -1,     0,      1,      8000   },         // 100 CMB_ALLPASS_ENV_C
    {        127,    3,      0,      16000,  0,      0,      45,     1,      0,      16000  },         // 101 CMB_ALLPASS_RESON
    {        129,    3,      0,      100,    9,      40,     -1,     0,      0,      10000  },         // 102 CMB_HICUT
    {        131,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 103 CMB_HICUT_KT
    {        132,    3,      0,      80,     0,      0,      -1,     0,      1,      8000   },         // 104 CMB_HICUT_ENV_C
    {        133,    3,      0,      8000,   4,      0.9f,   47,     1,      1,      8000   },         // 105 CMB_PM
    {        135,    3,      0,      16000,  2,      1,      48,     1,      0,      16000  },         // 106 CMB_PM_AB

    // - - - STATE VARIABLE FILTER  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        136,    2,      0,      16000,  2,      1,      49,     1,      0,      16000  },         // 107 SVF_AB
    {        138,    2,      0,      8000,   0,      0,      50,     1,      1,      8000   },         // 108 SVF_COMB_MIX
    {        140,    3,      0,      100,    9,      20,     -1,     0,      0,      12000  },         // 109 SVF_CUTOFF
    {        142,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 110 SVF_CUTOFF_KT
    {        143,    3,      0,      80,     0,      0,      -1,     0,      1,      8000   },         // 111 SVF_CUTOFF_ENV_C
    {        148,    3,      0,      100,    1,      0.5f,   -1,     0,      1,      6000   },         // 112 SVF_SPREAD
    {        153,    3,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 113 SVF_FM
    {        144,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 114 SVF_RESONANCE
    {        146,    3,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 115 SVF_RESONANCE_KT
    {        147,    3,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 116 SVF_RESONANCE_ENV_C
    {        150,    2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 117 SVF_LBH
    {        152,    2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 118 SVF_PARALLEL
    {        155,    3,      0,      16000,  2,      1,      62,     1,      0,      16000  },         // 119 SVF_FM_AB

    // - - - FEEDBACK MIXER - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        156,    2,      0,      8000,   0,      0,      63,     1,      1,      8000   },         // 120 FBM_COMB_MIX
    {        158,    2,      0,      8000,   0,      0,      64,     1,      1,      8000   },         // 121 FBM_SVF_MIX
    {        160,    2,      0,      8000,   3,      0,      65,     1,      1,      8000   },         // 122 FBM_EFFECTS_MIX
    {        162,    2,      0,      16000,  0,      0,      66,     0,      0,      16000  },         // 123 FBM_REVERB_MIX
    {        164,    2,      0,      200,    11,     2.5f,   67,     1,      0,      10000  },         // 124 FBM_DRIVE
#if test_fast_fold_asym == 0
    {        166,    3,      0,      16000,  0,      0,      68,     1,      0,      16000  },         // 125 FBM_FOLD
    {        167,    3,      0,      16000,  0,      0,      69,     1,      0,      16000  },         // 126 FBM_ASYM
#elif test_fast_fold_asym == 1
    {        166,    2,      0,      16000,  0,      0,      68,     1,      0,      16000  },         // 125 FBM_FOLD
    {        167,    2,      0,      16000,  0,      0,      69,     1,      0,      16000  },         // 126 FBM_ASYM
#endif
    {        168,    3,      0,      8000,   0,      0,      -1,     1,      1,      8000   },         // 127 FBM_LEVEL_KT
    {        299,    2,      0,      16000,  4,      4,      -1,     1,      0,      16000  },         // 128 FBM_LEVEL

    // - - - OUTPUT MIXER - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        169,    2,      0,      4000,   0,      0,      -1,     0,      1,      8000   },         // 129 OUT_A_LEVEL
    {        171,    2,      0,      16000,  0,      0.5f,   -1,     0,      1,      8000   },         // 130 OUT_A_PAN
    {        172,    2,      0,      4000,   0,      0,      -1,     0,      1,      8000   },         // 131 OUT_B_LEVEL
    {        174,    2,      0,      16000,  0,      0.5f,   -1,     0,      1,      8000   },         // 132 OUT_B_PAN
    {        175,    2,      0,      4000,   0,      0,      -1,     0,      1,      8000   },         // 133 OUT_COMB_LEVEL
    {        177,    2,      0,      16000,  0,      0.5f,   -1,     0,      1,      8000   },         // 134 OUT_COMB_PAN
    {        178,    2,      0,      4000,   0,      0,      -1,     0,      1,      8000   },         // 135 OUT_SVF_LEVEL
    {        180,    2,      0,      16000,  0,      0.5f,   -1,     0,      1,      8000   },         // 136 OUT_SVF_PAN
    {        181,    2,      0,      200,    11,     0.25f,  80,     1,      0,      10000  },         // 137 OUT_DRIVE
#if test_fast_fold_asym == 0
    {        183,    3,      0,      16000,  0,      0,      81,     1,      0,      16000  },         // 138 OUT_FOLD (later maybe fast type)
    {        184,    3,      0,      16000,  0,      0,      82,     1,      0,      16000  },         // 139 OUT_ASYMETRY (later maybe fast type)
#elif test_fast_fold_asym == 1
    {        183,    2,      0,      16000,  0,      0,      81,     1,      0,      16000  },         // 138 OUT_FOLD (later maybe fast type)
    {        184,    2,      0,      16000,  0,      0,      82,     1,      0,      16000  },         // 139 OUT_ASYMETRY (later maybe fast type)
#endif
    {        185,    2,      0,      16000,  4,      2.56f,  83,     0,      0,      16000  },         // 140 OUT_LEVEL
    {        187,    2,      0,      960000, 0,      0,      -1,     0,      0,      16000  },         // 141 OUT_KEY_PAN

    // - - - CABINET  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        188,    2,      0,      200,    12,     0,      84,     0,      0,      10000  },         // 142 CABINET_DRIVE
#if test_fast_fold_asym == 0
    {        190,    3,      0,      16000,  0,      0,      85,     0,      0,      16000  },         // 143 CABINET_FOLD (later maybe fast type)
    {        191,    3,      0,      16000,  0,      0,      86,     0,      0,      16000  },         // 144 CABINET_ASYMETRY (later maybe fast type)
#elif test_fast_fold_asym == 1
    {        190,    2,      0,      16000,  0,      0,      85,     0,      0,      16000  },         // 143 CABINET_FOLD (later maybe fast type)
    {        191,    2,      0,      16000,  0,      0,      86,     0,      0,      16000  },         // 144 CABINET_ASYMETRY (later maybe fast type)
#endif
    {        192,    2,      0,      80,     0,      0,      -1,     0,      1,      8000   },         // 145 CABINET_TILT (implement fast and slow handling)
    {        194,    3,      0,      200,    9,      60,     -1,     0,      0,      16000  },         // 146 CABINET_HI_CUT
    {        196,    3,      0,      200,    9,      20,     -1,     0,      0,      16000  },         // 147 CABINET_LOW_CUT
    {        197,    2,      0,      200,    12,     -50,    -1,     0,      0,      10000  },         // 148 CABINET_CAB_LEVEL
    {        199,    2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 149 CABINET_MIX

    // - - - GAP FILTER - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        201,    3,      0,      100,    0,      24,     -1,     0,      0,      9600   },         // 150 GAP_FILTER_CENTER
    {        203,    3,      0,      200,    1,      0.5f,   -1,     0,      1,      7200   },         // 151 GAP_FILTER_STEREO
    {        204,    3,      0,      100,    1,      0.5f,   -1,     0,      0,      9600   },         // 152 GAP_FILTER_GAP
    {        206,    3,      0,      16000,  1,      0.9f,   98,     0,      0,      16000  },         // 153 GAP_FILTER_RESONANCE
    {        207,    2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 154 GAP_FILTER_BALANCE
    {        209,    2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 155 GAP_FILTER_MIX

    // - - - FLANGER  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        211,    2,      0,      8000,   4,      1,      104,    0,      1,      8000   },         // 156 FLANGER_TIME_MOD
#if test_flanger_phs == 0
    {        213,    3,      0,      80,     0,      0,      -1,     0,      0,      14400  },         // 157 FLANGER_PHASE
#elif test_flanger_phs == 1
    {        213,    2,      0,      80,     0,      0,      -1,     0,      0,      14400  },         // 157 FLANGER_PHASE
#elif test_flanger_phs == 2
    {        213,    1,      0,      80,     0,      0,      -1,     0,      0,      14400  },         // 157 FLANGER_PHASE
#endif
    {        214,    1,      0,      16000,  4,      10,     -1,     0,      0,      16000  },         // 158 FLANGER_RATE (audio)
    {        216,    3,      0,      12500,  4,      50,     -1,     0,      0,      12500  },         // 159 FLANGER_TIME
    {        218,    3,      0,      160,    0,      0,      -1,     0,      1,      8000   },         // 160 FLANGER_STEREO
    {        219,    2,      0,      16000,  0,      0.5f,   -1,     0,      1,      8000   },         // 161 FLANGER_FEEDBACK
    {        221,    2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 162 FLANGER_CROSS_FEEDBACK
    {        222,    3,      0,      200,    9,      60,     -1,     0,      0,      16000  },         // 163 FLANGER_HI_CUT
    {        223,    2,      0,      8000,   0,      0,      -1,     0,      1,      8000   },         // 164 FLANGER_MIX
#if test_flanger_env == 0
    {        307,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 165 FLANGER_ENVELOPE
#elif test_flanger_env == 1
    {        307,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 165 FLANGER_ENVELOPE
#elif test_flanger_env == 2
    {        307,    1,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 165 FLANGER_ENVELOPE
#endif
    {        308,    3,      0,      8000,   1,      70,     -1,     0,      1,      8000   },         // 166 FLANGER_ALLPASS_MOD
    {        310,    3,      0,      100,    0,      0,      -1,     0,      0,      14000  },         // 167 FLANGER_ALLPASS_TUNE

    // - - - ECHO - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        225,    3,      0,      16000,  4,      2,      -1,     0,      0,      16000  },         // 168 ECHO_DELAY_TIME
    {        227,    3,      0,      200,    0,      0,      -1,     0,      1,      6600   },         // 169 ECHO_STEREO
    {        229,    2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 170 ECHO_FEEDBACK
    {        231,    2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 171 ECHO_CROSS_FEEDBACK
    {        232,    3,      0,      200,    9,      60,     -1,     0,      0,      16000  },         // 172 ECHO_HI_CUT
    {        233,    2,      0,      16000,  4,      1,      -1,     0,      0,      16000  },         // 173 ECHO_MIX
    {        334,    2,      0,      16000,  0,      0,      123,    0,      0,      16000  },         // 174 ECHO_SEND

    // - - - REVERB - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
#if test_reverbParams == 0
    /* should the parameters run with fast clock? (except chorus) - see pe_defines_config.h */
    {        235,    2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 175 REVERB_SIZE
    {        237,    2,      0,      16000,  5,      0,      -1,     0,      0,      16000  },         // 176 REVERB_PRE_DELAY
    {        238,    2,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 177 REVERB_COLOR
    {        240,    3,      0,      16000,  4,      1,      130,    0,      0,      16000  },         // 178 REVERB_CHORUS
#elif test_reverbParams == 1
    /* should the parameters run with slow clock? - see pe_defines_config.h */
    {        235,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 175 REVERB_SIZE
    {        237,    3,      0,      16000,  5,      0,      -1,     0,      0,      16000  },         // 176 REVERB_PRE_DELAY
    {        238,    3,      0,      16000,  0,      0,      -1,     0,      0,      16000  },         // 177 REVERB_COLOR
    {        240,    3,      0,      16000,  4,      1,      130,    0,      0,      16000  },         // 178 REVERB_CHORUS
#endif
    {        241,    2,      0,      16000,  4,      1,      -1,     0,      0,      16000  },         // 179 REVERB_MIX
    {        336,    2,      0,      16000,  0,      0,      133,    0,      0,      16000  },         // 180 REVERB_SEND

    // - - - MASTER - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
    {        247,    2,      0,      16000,  4,      4,      134,    0,      0,      16000  },         // 181 MASTER_VOLUME
    {        248,    3,      0,      100,    0,      0,      -1,     0,      1,      4800   },         // 182 MASTER_TUNE
    {        338,    0,      0,      1,      0,      0,      -1,     0,      1,      1      },         // 183 NOTE_SHIFT

    // - - - UNISON - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
#if test_inputModeFlag == 0
    {        249,    0,      0,      1,      0,      -1,     -1,     0,      0,      11     },         // 184 UNISON_VOICES
#elif test_inputModeFlag == 1
    {        249,    0,      0,      1,      0,      0,      -1,     0,      0,      11     },         // 184 UNISON_VOICES
#endif
    {        250,    3,      0,      1000,   0,      0,      -1,     0,      0,      12000  },         // 185 UNISON_DETUNE
    {        252,    1,      0,      14400,  0,      0,      -1,     0,      0,      14400  },         // 186 UNISON_PHASE
    {        253,    2,      0,      16000,  1,      0.5f,   -1,     0,      0,      16000  },         // 187 UNISON_PAN

    // - - - POLY KEY EVENT - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //       ID      CLOCK   POLY    RANGE   SCALE   (ARG)   POST    SPREAD  POL     FACTOR
#if test_milestone == 150
    {        400,    0,      1,      14400,  0,      0,      -1,     0,      1,      7200   },         // 188 KEY_UNISON_PHASE
    {        406,    0,      1,      1000,   0,      0,      -1,     0,      1,      1000   },         // 189 KEY_NOTE_PITCH
    {        407,    0,      1,      8000,   0,      0,      -1,     0,      1,      8000   },         // 190 KEY_VOICE_PAN
    {        409,    0,      1,      1,      0,      0,      -1,     0,      0,      1      }          // 191 KEY_VOICE_STEAL
#elif test_milestone == 155
    {        416,    0,      1,      1,      0,      0,      -1,     0,      1,      1      },         // 188 KEY_POSITION
    {        417,    0,      1,      1,      0,      0,      -1,     0,      0,      1      },         // 189 KEY_UNISON_IDX
    {        418,    0,      1,      1,      0,      0,      -1,     0,      0,      1      },         // 190 KEY_VOICE_STEAL
#endif

};

/* Utility Parameters */

const float utility_definition[sig_number_of_utilities][3] = {
    //       RANGE   SCALE   (ARG)
    {        4096,   0,      0          },                                      // velocity definition (for now: tcd range 4096)
    {        100,    0,      400        },                                      // pitch reference (A3)
    {        1,      0,      0          },                                      // Test Tone Frequency (400 ... 1000 Hz)
    {        1,      0,      0          },                                      // Test Tone Ampltude (-60 ... 0 dB)
    {        1,      0,      0          }                                       // Test Tone State (0, 1)
};
