/******************************************************************************/
/** @file       dsp_defines_signallabels.h
    @date       2018-08-21
    @version    1.0
    @author     Matthias Seeber & Anton Schmied
    @brief      Defines for the individual Signal Names (indices) in the great
                shared m_paramsignaldata[][] array
*******************************************************************************/

#pragma once

/* Envelope Signals                 -- polyphonic */

#define ENV_A_MAG       0           // Envelope A (magnitude component)
#define ENV_A_TMB       1           // Envelope A (timbre component)
#define ENV_B_MAG       2           // Envelope B (magnitude component)
#define ENV_B_TMB       3           // Envelope B (timbre component)
#define ENV_C_SIG       4           // Envelope C
#define ENV_G_SIG       5           // Gate Envelope

/* Oscillator A Signals             -- polyphonic */

#define OSC_A_FRQ       6           // Oscillator A Frequency (Pitch, Pitch KT, Pitch Env C Amount, Env C, Master Tune, Reference, Key Pitch)
#define OSC_A_FLUEC     7           // Oscillator A Fluctuation (Amount, Env C Amount, Env C)
#define OSC_A_PMSEA     8           // Oscillator A PM Self (Amount, Env A Amount, Env A)
#define OSC_A_PMSSH     9           // Oscillator A PM Self Shaper (Amount)
#define OSC_A_PMBEB     10          // Oscillator A PM B (Amount, Env B Amount, Env B)
#define OSC_A_PMBSH     11          // Oscillator A PM B Shaper (Amount)
#define OSC_A_PMFEC     12          // Oscillator A PM FB (Amount, Env C Amount, Env C)
#define OSC_A_CHI       13          // Oscillator A Chirp Frequency (Cutoff)

/* Shaper A Signals                 -- polyphonic */

#define SHP_A_DRVEA     14          // Shaper A Drive (Drive, Env A Amount, Env A)
#define SHP_A_FLD       15          // Shaper A Fold (Amount)
#define SHP_A_ASM       16          // Shaper A Asymetry (Amount)
#define SHP_A_MIX       17          // Shaper A Mix (Amount)
#define SHP_A_FBM       18          // Shaper A Feedback Mix (Amount)
#define SHP_A_FBEC      19          // Shaper A Feedback Env C (Amount, Env C, Gate)
#define SHP_A_RM        20          // Shaper A Ringmod (Amount)

/* Oscillator B Signals             -- polyphonic */

#define OSC_B_FRQ       21          // Oscillator B Frequency (Pitch, Pitch KT, Pitch Env C Amount, Env C, Master Tune, Reference, Key Pitch)
#define OSC_B_FLUEC     22          // Oscillator B Fluctuation (Amount, Env C Amount, Env C)
#define OSC_B_PMSEB     23          // Oscillator B PM Self (Amount, Env B Amount, Env B)
#define OSC_B_PMSSH     24          // Oscillator B PM Self Shaper (Amount)
#define OSC_B_PMAEA     25          // Oscillator B PM A (Amount, Env A Amount, Env A)
#define OSC_B_PMASH     26          // Oscillator B PM A Shaper (Amount)
#define OSC_B_PMFEC     27          // Oscillator B PM FB (Amount, Env C Amount, Env C)
#define OSC_B_CHI       28          // Oscillator B Chirp Frequency (Cutoff)

/* Shaper B Signals                 -- polyphonic */

#define SHP_B_DRVEB     29          // Shaper B Drive (Drive, Env B Amount, Env B)
#define SHP_B_FLD       30          // Shaper B Fold (Amount)
#define SHP_B_ASM       31          // Shaper B Asymetry (Amount)
#define SHP_B_MIX       32          // Shaper B Mix (Amount)
#define SHP_B_FBM       33          // Shaper B Feedback Mix (Amount)
#define SHP_B_FBEC      34          // Shaper B Feedback Env C (Amount, Env C, Gate)
#define SHP_B_RM        35          // Shaper B Ringmod (Amount)

/* Comb Filter Signals              -- polyphonic */

#define CMB_AB          36          // Comb AB Input Mix (Amount)
#define CMB_FRQ         37          // Comb Frequency (Pitch, Pitch KT, Master Tune, Reference, Key Pitch)
#define CMB_BYP         38          // Comb Bypass (Pitch)
#define CMB_FEC         39          // Comb Pitch Env C (Frequency Factor)
#define CMB_DEC         40          // Comb Decay (Decay, Decay KT, Decay Gate Amount, Gate, Master Tune, Key Pitch)
#define CMB_APF         41          // Comb Allpass Frequency (Tune, AP KT, AP Env C Amount, Env C, Master Tune, Key Pitch)
#define CMB_APR         42          // Comb Allpass Resonance (Amount)
#define CMB_LPF         43          // Comb Hi Cut Frequency (Hi Cut, Hi Cut KT, Hi Cut Env C, Env C, Master Tune, Key Pitch)
#define CMB_PM          44          // Comb PM (Amount)
#define CMB_PMAB        45          // Comb PM AB Mix (Amount)

/* State Variable Filter Signals    -- polyphonic */

#define SVF_AB          46          // SVF AB Input Mix (Amount)
#define SVF_CMIX        47          // SVF Comb Input Mix (Amount)
#define SVF_F1_CUT      48          // SVF Upper Filter Frequency (Cutoff, Cutoff KT, Cutoff Env C Amount, Env C, Spread, Master Tune, Reference, Key Pitch)
#define SVF_F2_CUT      49          // SVF Lower Filter Frequency (Cutoff, Cutoff KT, Cutoff Env C Amount, Env C, Spread, Master Tune, Reference, Key Pitch)
#define SVF_F1_FM       50          // SVF Upper Filter FM Amount (Cutoff, Cutoff KT, Cutoff Env C Amount, Env C, Spread, FM, Master Tune, Reference, Key Pitch)
#define SVF_F2_FM       51          // SVF Lower Filter FM Amount (Cutoff, Cutoff KT, Cutoff Env C Amount, Env C, Spread, FM, Master Tune, Reference, Key Pitch)
#define SVF_RES         52          // SVF Resonance (Resonance, Res KT, Res Env C Amount, Env C, Master Tune, Key Pitch)
#define SVF_LBH_1       53          // SVF Upper LBH Mix (Amount)
#define SVF_LBH_2       54          // SVF Lower LBH Mix (Amount)
#define SVF_PAR_1       55          // SVF Parallel Amount 1 (Amount)
#define SVF_PAR_2       56          // SVF Parallel Amount 2 (Amount)
#define SVF_PAR_3       57          // SVF Parallel Amount 3 (Amount)
#define SVF_PAR_4       58          // SVF Parallel Amount 4 (Amount)
#define SVF_FMAB        59          // SVF FM AB Mix (Amount)

/* Feedback Mixer Signals           -- polyphonic */

#define FBM_CMB         60          // FB Mix Comb Mix (Amount)
#define FBM_SVF         61          // FB Mix SVF Mix (Amount)
#define FBM_FX          62          // FB Mix Effects Mix (Amount)
#define FBM_REV         63          // FB Mix Reverb Mix (Amount)
#define FBM_DRV         64          // FB Mix Drive (Amount)
#define FBM_FLD         65          // FB Mix Fold (Amount)
#define FBM_ASM         66          // FB Mix Asymetry (Amount)
#define FBM_LVL         67          // FB Mix Level (Level, Level KT, Master Tune, Key Pitch)
#define FBM_HPF         68          // FB Mix Highpass Frequency (Master Tune, Key Pitch)

/* Output Mixer Signals             -- polyphonic */

#define OUT_A_L         69          // Out Mix Branch A Left Level (Level, Pan, Key Pan)
#define OUT_A_R         70          // Out Mix Branch A Right Level (Level, Pan, Key Pan)
#define OUT_B_L         71          // Out Mix Branch B Left Level (Level, Pan, Key Pan)
#define OUT_B_R         72          // Out Mix Branch B Right Level (Level, Pan, Key Pan)
#define OUT_CMB_L       73          // Out Mix Comb Left Level (Level, Pan, Key Pan)
#define OUT_CMB_R       74          // Out Mix Comb Right Level (Level, Pan, Key Pan)
#define OUT_SVF_L       75          // Out Mix SVF Left Level (Level, Pan, Key Pan)
#define OUT_SVF_R       76          // Out Mix SVF Right Level (Level, Pan, Key Pan)
#define OUT_DRV         77          // Out Mix Drive (Amount)
#define OUT_FLD         78          // Out Mix Fold (Amount)
#define OUT_ASM         79          // Out Mix Asymetry (Amount)
#define OUT_LVL         80          // Out Mix Level (Level)

/* Cabinet Signals                  -- monophonic */

#define CAB_DRV         81          // Cabinet Drive (Amount)
#define CAB_FLD         82          // Cabinet Fold (Amount)
#define CAB_ASM         83          // Cabinet Asymetry (Amount)
#define CAB_PRESAT      84          // Cabinet Saturation Level (Tilt - pre Shaper factor)
#define CAB_SAT         85          // Cabinet Saturation Level (Tilt - post Shaper factor)
#define CAB_TILT        86          // Cabinet Tilt (Tilt)
#define CAB_LPF         87          // Cabinet Hi Cut (Cutoff)
#define CAB_HPF         88          // Cabinet Lo Cut (Cutoff)
#define CAB_DRY         89          // Cabinet Dry Amount (Mix)
#define CAB_WET         90          // Cabinet Wet Amount (Mix)

/* Gap Filter Signals               -- monophonic */

#define GAP_LFL         91          // Gap Filter Left Lowpass Frequency (Center, Stereo, Gap)
#define GAP_HFL         92          // Gap Filter Left Highpass Frequency (Center, Stereo, Gap)
#define GAP_LFR         93          // Gap Filter Right Lowpass Frequency (Center, Stereo, Gap)
#define GAP_HFR         94          // Gap Filter Right Highpass Frequency (Center, Stereo, Gap)
#define GAP_RES         95          // Gap Filter Resonance (Amount)
#define GAP_HPLP        96          // Gap Filter Highpass to Lowpass Amount (Balance, Mix)
#define GAP_INLP        97          // Gap Filter Input to Lowpass Amount (Balance, Mix)
#define GAP_HPOUT       98          // Gap Filter Highpass to Output Amount (Balance, Mix)
#define GAP_LPOUT       99          // Gap Filter Lowpass to Output Amount (Balance, Mix)
#define GAP_INOUT       100         // Gap Filter Input to Output Amount (Balance, Mix)

/* Flanger Signals                  -- monophonic */

#define FLA_TMOD        101         // Flanger Time Modulation (Amount)
#define FLA_LFO_L       102         // Flanger Left Modulation Signal (Phase, Rate, Envelope, Flanger LFO/Envelope)
#define FLA_LFO_R       103         // Flanger Right Modulation Signal (Phase, Rate, Envelope, Flanger LFO/Envelope)
#define FLA_TL          104         // Flanger Left Time (Time, Stereo)
#define FLA_TR          105         // Flanger Right Time (Time, Stereo)
#define FLA_FB_LOC      106         // Flanger Local Feedback Amount (Feedback, Cross FB)
#define FLA_FB_CR       107         // Flanger Cross Feedback Amount (Feedback, Cross FB)
#define FLA_LPF         108         // Flanger Lowpass Frequency (Hi Cut)
#define FLA_DRY         109         // Flanger Dry Amount (Mix)
#define FLA_WET         110         // Flanger Wet Amount (Mix)
#define FLA_APF_L       111         // Flanger Left Allpass Frequency (AP Mod, AP Tune, Flanger LFO/Envelope)
#define FLA_APF_R       112         // Flanger Right Allpass Frequency (AP Mod, AP Tune, Flanger LFO/Envelope)

/* Echo Signals                     -- monophonic */

#define DLY_TL          113         // Echo Left Time (Time, Stereo)
#define DLY_TR          114         // Echo Right Time (Time, Stereo)
#define DLY_FB_LOC      115         // Echo Local Feedback (Feedback, Cross FB)
#define DLY_FB_CR       116         // Echo Cross Feedback (Feedback, Cross FB)
#define DLY_LPF         117         // Echo Lowpass Frequency (Hi Cut)
#define DLY_DRY         118         // Echo Dry Amount (Mix)
#define DLY_WET         119         // Echo Wet Amount (Mix)

/* Reverb Signals                   -- monophonic */

#define REV_SIZE        120         // Reverb Size (Size)
#define REV_FEED        121         // Reverb Feedback Amount (Size)
#define REV_BAL         122         // Reverb Balance (Size)
#define REV_PRE         123         // Reverb Pre Delay (Pre Delay)
#define REV_HPF         124         // Reverb Highpass Frequency (Color)
#define REV_LPF         125         // Reverb Lowpass Frequency (Color)
#define REV_CHO         126         // Reverb Chorus (Chorus)
#define REV_DRY         127         // Reverb Dry Amount (Mix)
#define REV_WET         128         // Reverb Wet Amount (Mix)

/* Master Signals                   -- monophonic */

#define MST_VOL         129         // Master Volume (Volume)
