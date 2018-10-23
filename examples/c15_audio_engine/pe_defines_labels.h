/******************************************************************************/
/** @file       pe_defines_labels.h
    @date       2018-04-20
    @version    1.0
    @author     Matthias Seeber
    @brief      c15 parameter labels (for better code readability)
                NOTE:
                The provided IDs represent the rendering items of the parameter
                engine, NOT the elements of the shared m_paramsignaldata[][] array!
                ..
    @todo
*******************************************************************************/

#pragma once

/* Envelope Parameter Labels - access parameter with (envIndex + ID) */

#define E_ATT       0
#define E_DEC1      1
#define E_BP        2
#define E_DEC2      3
#define E_SUS       4
#define E_REL       5
#define E_LV        7
#define E_AV        8
#define E_RV        9
#define E_LKT       10
#define E_TKT       11
#define E_AC        12
#define E_RH        13
#define E_SPL       14

/* 'normal' Parameter Labels - access parameter with m_head[ID] - maybe, the rendering index would be much more efficient? */

#define P_EA_GAIN   6
#define P_EB_GAIN   21

#define P_OA_P      45
#define P_OA_PKT    46
#define P_OA_PEC    47
#define P_OA_F      48
#define P_OA_FEC    49
#define P_OA_PMS    50
#define P_OA_PMSEA  51
#define P_OA_PMSSH  52
#define P_OA_PMB    53
#define P_OA_PMBEB  54
#define P_OA_PMBSH  55
#define P_OA_PMF    56
#define P_OA_PMFEC  57
#define P_OA_PHS    58
#define P_OA_CHI    59

#define P_SA_D      60
#define P_SA_DEA    61
#define P_SA_F      62
#define P_SA_A      63
#define P_SA_M      64
#define P_SA_FBM    65
#define P_SA_FBEC   66
#define P_SA_RM     67

#define P_OB_P      68
#define P_OB_PKT    69
#define P_OB_PEC    70
#define P_OB_F      71
#define P_OB_FEC    72
#define P_OB_PMS    73
#define P_OB_PMSEB  74
#define P_OB_PMSSH  75
#define P_OB_PMA    76
#define P_OB_PMAEA  77
#define P_OB_PMASH  78
#define P_OB_PMF    79
#define P_OB_PMFEC  80
#define P_OB_PHS    81
#define P_OB_CHI    82

#define P_SB_D      83
#define P_SB_DEB    84
#define P_SB_F      85
#define P_SB_A      86
#define P_SB_M      87
#define P_SB_FBM    88
#define P_SB_FBEC   89
#define P_SB_RM     90

#define P_CMB_AB    91
#define P_CMB_P     92
#define P_CMB_PKT   93
#define P_CMB_PEC   94
#define P_CMB_D     95
#define P_CMB_DKT   96
#define P_CMB_DG    97
#define P_CMB_APT   98
#define P_CMB_APKT  99
#define P_CMB_APEC  100
#define P_CMB_APR   101
#define P_CMB_LP    102
#define P_CMB_LPKT  103
#define P_CMB_LPEC  104
#define P_CMB_PM    105
#define P_CMB_PMAB  106

#define P_SVF_AB    107
#define P_SVF_CMB   108
#define P_SVF_CUT   109
#define P_SVF_CKT   110
#define P_SVF_CEC   111
#define P_SVF_SPR   112
#define P_SVF_FM    113
#define P_SVF_RES   114
#define P_SVF_RKT   115
#define P_SVF_REC   116
#define P_SVF_LBH   117
#define P_SVF_PAR   118
#define P_SVF_FMAB  119

#define P_FBM_CMB   120
#define P_FBM_SVF   121
#define P_FBM_FX    122
#define P_FBM_REV   123
#define P_FBM_DRV   124
#define P_FBM_FLD   125
#define P_FBM_ASM   126
#define P_FBM_LKT   127
#define P_FBM_LVL   128

#define P_OM_AL     129
#define P_OM_AP     130
#define P_OM_BL     131
#define P_OM_BP     132
#define P_OM_CL     133
#define P_OM_CP     134
#define P_OM_SL     135
#define P_OM_SP     136
#define P_OM_DRV    137
#define P_OM_FLD    138
#define P_OM_ASM    139
#define P_OM_LVL    140
// P_OM_KP

#define P_CAB_DRV   141
#define P_CAB_FLD   142
#define P_CAB_ASM   143
#define P_CAB_TILT  144
#define P_CAB_LPF   145
#define P_CAB_HPF   146
#define P_CAB_LVL   147
#define P_CAB_MIX   148

#define P_GAP_CNT   149
#define P_GAP_STE   150
#define P_GAP_GAP   151
#define P_GAP_RES   152
#define P_GAP_BAL   153
#define P_GAP_MIX   154

#define P_FLA_TMOD  155
#define P_FLA_PHS   156
#define P_FLA_RTE   157
#define P_FLA_TIME  158
#define P_FLA_STE   159
#define P_FLA_FB    160
#define P_FLA_CFB   161
#define P_FLA_LPF   162
#define P_FLA_MIX   163
#define P_FLA_ENV   164
#define P_FLA_APM   165
#define P_FLA_APT   166

#define P_DLY_TIME  167
#define P_DLY_STE   168
#define P_DLY_FB    169
#define P_DLY_CFB   170
#define P_DLY_LPF   171
#define P_DLY_MIX   172
// P_DLY_SND

#define P_REV_SIZE  173
#define P_REV_PRE   174
#define P_REV_COL   175
#define P_REV_CHO   176
#define P_REV_MIX   177
// P_REV_SND

#define P_MA_V      178
#define P_MA_T      179

// UNISON...

#define P_KEY_PH    180
#define P_KEY_NP    181
#define P_KEY_VP    182
#define P_KEY_EC    183
#define P_KEY_VS    184
