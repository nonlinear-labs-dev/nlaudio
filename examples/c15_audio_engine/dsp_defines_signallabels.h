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
#define OSC_A_PHS       13          // Oscillator A Phase (Offset)
#define OSC_A_CHI       14          // Oscillator A Chirp Frequency (Cutoff)

/* Shaper A Signals                 -- polyphonic */

#define SHP_A_DRVEA     15          // Shaper A Drive (Drive, Env A Amount, Env A)
#define SHP_A_FLD       16          // Shaper A Fold (Amount)
#define SHP_A_ASM       17          // Shaper A Asymetry (Amount)
#define SHP_A_MIX       18          // Shaper A Mix (Amount)
#define SHP_A_FBM       19          // Shaper A Feedback Mix (Amount)
#define SHP_A_FBEC      20          // Shaper A Feedback Env C (Amount, Env C, Gate)
#define SHP_A_RM        21          // Shaper A Ringmod (Amount)

/* Oscillator B Signals             -- polyphonic */

#define OSC_B_FRQ       22          // Oscillator B Frequency (Pitch, Pitch KT, Pitch Env C Amount, Env C, Master Tune, Reference, Key Pitch)
#define OSC_B_FLUEC     23          // Oscillator B Fluctuation (Amount, Env C Amount, Env C)
#define OSC_B_PMSEB     24          // Oscillator B PM Self (Amount, Env B Amount, Env B)
#define OSC_B_PMSSH     25          // Oscillator B PM Self Shaper (Amount)
#define OSC_B_PMAEA     26          // Oscillator B PM A (Amount, Env A Amount, Env A)
#define OSC_B_PMASH     27          // Oscillator B PM A Shaper (Amount)
#define OSC_B_PMFEC     28          // Oscillator B PM FB (Amount, Env C Amount, Env C)
#define OSC_B_PHS       29          // Oscillator B Phase (Offset)
#define OSC_B_CHI       30          // Oscillator B Chirp Frequency (Cutoff)

/* Shaper B Signals                 -- polyphonic */

#define SHP_B_DRVEB     31          // Shaper B Drive (Drive, Env B Amount, Env B)
#define SHP_B_FLD       32          // Shaper B Fold (Amount)
#define SHP_B_ASM       33          // Shaper B Asymetry (Amount)
#define SHP_B_MIX       34          // Shaper B Mix (Amount)
#define SHP_B_FBM       35          // Shaper B Feedback Mix (Amount)
#define SHP_B_FBEC      36          // Shaper B Feedback Env C (Amount, Env C, Gate)
#define SHP_B_RM        37          // Shaper B Ringmod (Amount)

/* Comb Filter Signals              -- polyphonic */

#define CMB_AB          38          // Comb AB Input Mix (Amount)
#define CMB_FRQ         39          // Comb Frequency (Pitch, Pitch KT, Master Tune, Reference, Key Pitch)
#define CMB_BYP         40          // Comb Bypass (Pitch)
#define CMB_FEC         41          // Comb Pitch Env C (Frequency Factor)
#define CMB_DEC         42          // Comb Decay (Decay, Decay KT, Decay Gate Amount, Gate, Master Tune, Key Pitch)
#define CMB_APF         43          // Comb Allpass Frequency (Tune, AP KT, AP Env C Amount, Env C, Master Tune, Key Pitch)
#define CMB_APR         44          // Comb Allpass Resonance (Amount)
#define CMB_LPF         45          // Comb Hi Cut Frequency (Hi Cut, Hi Cut KT, Hi Cut Env C, Env C, Master Tune, Key Pitch)
#define CMB_PM          46          // Comb PM (Amount)
#define CMB_PMAB        47          // Comb PM AB Mix (Amount)

/* State Variable Filter Signals    -- polyphonic */

#define SVF_AB          48          // SVF AB Input Mix (Amount)
#define SVF_CMIX        49          // SVF Comb Input Mix (Amount)
#define SVF_F1_CUT      50          // SVF Upper Filter Frequency (Cutoff, Cutoff KT, Cutoff Env C Amount, Env C, Spread, Master Tune, Reference, Key Pitch)
#define SVF_F2_CUT      51          // SVF Lower Filter Frequency (Cutoff, Cutoff KT, Cutoff Env C Amount, Env C, Spread, Master Tune, Reference, Key Pitch)
#define SVF_F1_FM       52          // SVF Upper Filter FM Amount (Cutoff, Cutoff KT, Cutoff Env C Amount, Env C, Spread, FM, Master Tune, Reference, Key Pitch)
#define SVF_F2_FM       53          // SVF Lower Filter FM Amount (Cutoff, Cutoff KT, Cutoff Env C Amount, Env C, Spread, FM, Master Tune, Reference, Key Pitch)
#define SVF_RES         54          // SVF Resonance (Resonance, Res KT, Res Env C Amount, Env C, Master Tune, Key Pitch)
#define SVF_LBH_1       55          // SVF Upper LBH Mix (Amount)
#define SVF_LBH_2       56          // SVF Lower LBH Mix (Amount)
#define SVF_PAR_1       57          // SVF Parallel Amount 1 (Amount)
#define SVF_PAR_2       58          // SVF Parallel Amount 2 (Amount)
#define SVF_PAR_3       59          // SVF Parallel Amount 3 (Amount)
#define SVF_PAR_4       60          // SVF Parallel Amount 4 (Amount)
#define SVF_FMAB        61          // SVF FM AB Mix (Amount)

/* Feedback Mixer Signals           -- polyphonic */

#define FBM_CMB         62          // FB Mix Comb Mix (Amount)
#define FBM_SVF         63          // FB Mix SVF Mix (Amount)
#define FBM_FX          64          // FB Mix Effects Mix (Amount)
#define FBM_REV         65          // FB Mix Reverb Mix (Amount)
#define FBM_DRV         66          // FB Mix Drive (Amount)
#define FBM_FLD         67          // FB Mix Fold (Amount)
#define FBM_ASM         68          // FB Mix Asymetry (Amount)
#define FBM_LVL         69          // FB Mix Level (Level, Level KT, Master Tune, Key Pitch)
#define FBM_HPF         70          // FB Mix Highpass Frequency (Master Tune, Key Pitch)

/* Output Mixer Signals             -- polyphonic */

#define OUT_A_L         71          // Out Mix Branch A Left Level (Level, Pan, Key Pan)
#define OUT_A_R         72          // Out Mix Branch A Right Level (Level, Pan, Key Pan)
#define OUT_B_L         73          // Out Mix Branch B Left Level (Level, Pan, Key Pan)
#define OUT_B_R         74          // Out Mix Branch B Right Level (Level, Pan, Key Pan)
#define OUT_CMB_L       75          // Out Mix Comb Left Level (Level, Pan, Key Pan)
#define OUT_CMB_R       76          // Out Mix Comb Right Level (Level, Pan, Key Pan)
#define OUT_SVF_L       77          // Out Mix SVF Left Level (Level, Pan, Key Pan)
#define OUT_SVF_R       78          // Out Mix SVF Right Level (Level, Pan, Key Pan)
#define OUT_DRV         79          // Out Mix Drive (Amount)
#define OUT_FLD         80          // Out Mix Fold (Amount)
#define OUT_ASM         81          // Out Mix Asymetry (Amount)
#define OUT_LVL         82          // Out Mix Level (Level)

/* Cabinet Signals                  -- monophonic */

#define CAB_DRV         83          // Cabinet Drive (Amount)
#define CAB_FLD         84          // Cabinet Fold (Amount)
#define CAB_ASM         85          // Cabinet Asymetry (Amount)
#define CAB_PRESAT      86          // Cabinet Saturation Level (Tilt - pre Shaper factor)
#define CAB_SAT         87          // Cabinet Saturation Level (Tilt - post Shaper factor)
#define CAB_TILT        88          // Cabinet Tilt (Tilt)
#define CAB_LPF         89          // Cabinet Hi Cut (Cutoff)
#define CAB_HPF         90          // Cabinet Lo Cut (Cutoff)
#define CAB_DRY         91          // Cabinet Dry Amount (Mix)
#define CAB_WET         92          // Cabinet Wet Amount (Mix)

/* Gap Filter Signals               -- monophonic */

#define GAP_LFL         93          // Gap Filter Left Lowpass Frequency (Center, Stereo, Gap)
#define GAP_HFL         94          // Gap Filter Left Highpass Frequency (Center, Stereo, Gap)
#define GAP_LFR         95          // Gap Filter Right Lowpass Frequency (Center, Stereo, Gap)
#define GAP_HFR         96          // Gap Filter Right Highpass Frequency (Center, Stereo, Gap)
#define GAP_RES         97          // Gap Filter Resonance (Amount)
#define GAP_HPLP        98          // Gap Filter Highpass to Lowpass Amount (Balance, Mix)
#define GAP_INLP        99          // Gap Filter Input to Lowpass Amount (Balance, Mix)
#define GAP_HPOUT       100         // Gap Filter Highpass to Output Amount (Balance, Mix)
#define GAP_LPOUT       101         // Gap Filter Lowpass to Output Amount (Balance, Mix)
#define GAP_INOUT       102         // Gap Filter Input to Output Amount (Balance, Mix)

/* Flanger Signals                  -- monophonic */

#define FLA_TMOD        103         // Flanger Time Modulation (Amount)
#define FLA_LFO_L       104         // Flanger Left Modulation Signal (Phase, Rate, Envelope, Flanger LFO/Envelope)
#define FLA_LFO_R       105         // Flanger Right Modulation Signal (Phase, Rate, Envelope, Flanger LFO/Envelope)
#define FLA_TL          106         // Flanger Left Time (Time, Stereo)
#define FLA_TR          107         // Flanger Right Time (Time, Stereo)
#define FLA_FB_LOC      108         // Flanger Local Feedback Amount (Feedback, Cross FB)
#define FLA_FB_CR       109         // Flanger Cross Feedback Amount (Feedback, Cross FB)
#define FLA_LPF         110         // Flanger Lowpass Frequency (Hi Cut)
#define FLA_DRY         111         // Flanger Dry Amount (Mix)
#define FLA_WET         112         // Flanger Wet Amount (Mix)
#define FLA_APF_L       113         // Flanger Left Allpass Frequency (AP Mod, AP Tune, Flanger LFO/Envelope)
#define FLA_APF_R       114         // Flanger Right Allpass Frequency (AP Mod, AP Tune, Flanger LFO/Envelope)

/* Echo Signals                     -- monophonic */

#define DLY_TL          115         // Echo Left Time (Time, Stereo)
#define DLY_TR          116         // Echo Right Time (Time, Stereo)
#define DLY_FB_LOC      117         // Echo Local Feedback (Feedback, Cross FB)
#define DLY_FB_CR       118         // Echo Cross Feedback (Feedback, Cross FB)
#define DLY_LPF         119         // Echo Lowpass Frequency (Hi Cut)
#define DLY_DRY         120         // Echo Dry Amount (Mix)
#define DLY_WET         121         // Echo Wet Amount (Mix)

/* Reverb Signals                   -- monophonic */

#define REV_SIZE        122         // Reverb Size (Size)
#define REV_FEED        123         // Reverb Feedback Amount (Size)
#define REV_BAL         124         // Reverb Balance (Size)
#define REV_PRE         125         // Reverb Pre Delay (Pre Delay)
#define REV_HPF         126         // Reverb Highpass Frequency (Color)
#define REV_LPF         127         // Reverb Lowpass Frequency (Color)
#define REV_CHO         128         // Reverb Chorus (Chorus)
#define REV_DRY         129         // Reverb Dry Amount (Mix)
#define REV_WET         130         // Reverb Wet Amount (Mix)

/* Master Signals                   -- monophonic */

#define MST_VOL         131         // Master Volume (Volume)
