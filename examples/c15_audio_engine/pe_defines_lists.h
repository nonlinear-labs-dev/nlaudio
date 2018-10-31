/******************************************************************************/
/** @file       pe_defines_lists.h
    @date       2018-03-13
    @version    1.0
    @author     Matthias Seeber
    @brief      predefined id list declaration (recall, key event)
                ..
    @todo
*******************************************************************************/

#pragma once

#include <stdint.h>
#include "pe_defines_config.h"
#include "pe_defines_labels.h"

// NOTE: manually keeping track of internal param ids gets more and more inconvenient...
// NOTE: define param labels directly and get rid of envIndex and placeholders, then replace recall ids with param labels

// consecutive paramIds for MONO recall update (defining tcd order of destinations) - listId = 1
// NOTE:    - recall param id order by PLAYGROUND, list mechanism fragile/risky in this case -> discard

/* later: define "official" parameter order (playground, ...) in order to transmit preset lists -> also affects testconfig preset data! */
const uint32_t paramIds_recall[lst_recall_length] = {
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  16,      // Env A (all params - #15: rh placeholder!)
    17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  33,      // Env B (all params - #32: rh placeholder!)
    34,  35,  36,  37,  38,  39,  41,  42,  45,  46,  47,  48,  49,                     // Env C (all params - #40, 43, 44, 50: gain, d1v, d2v, split placeholder!)
    51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,           // Osc A (all params)
    66,  67,  68,  69,  70,  71,  72,  73,                                              // Shp A (all params)
    74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,           // Osc B (all params)
    89,  90,  91,  92,  93,  94,  95,  96,                                              // Shp B (all params)
    97,  98,  99,  100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,     // Comb (all params)
    113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125,                    // SFV (all params)
    126, 127, 128, 129, 130, 131, 132, 133, 134,                                        // FB Mixer (all params)
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147,                    // Out Mix (all params)
    148, 149, 150, 151, 152, 153, 154, 155,                                             // Cabinet (all params)
    156, 157, 158, 159, 160, 161,                                                       // Gap Filter (all params)
    162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173,                         // Flanger (all params)
    174, 175, 176, 177, 178, 179, 180,                                                  // Echo (all params)
    181, 182, 183, 184, 185, 186,                                                       // Reverb (all params)
    187, 188,                                                                           // Master (Vol, Tune)
    190, 191, 192, 193                                                                  // Unison (all params)
};

// consecutive paramIds for POLY key event update (defining tcd order of destinations) - listId = 2
// NOTE:    - keyEvent param id order by LPC, list mechanism usable -> keep

#if test_milestone == 150

const uint32_t paramIds_keyEvent[lst_keyEvent_length] = {
    P_KEY_PH, P_KEY_NP, P_KEY_VP, P_KEY_VS
};

#elif test_milestone == 155

const uint32_t paramIds_keyEvent[lst_keyEvent_length] = {
    P_KEY_BP, P_KEY_IDX, P_KEY_STL
};

#endif
