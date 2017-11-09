/******************************************************************************/
/** @file		reverb.h
    @date		2017-06-27
    @version	0.1
    @author		Anton Schmied[2017-06-27]
    @brief		An implementation of the Reverb Class
                as used in the C15 and implemented in Reaktor

    @todo       All the Smoothing params
                Loop Filter Coefficients
*******************************************************************************/

#pragma once

#include "nltoolbox.h"
#include <array>

//************************************ Buffer Arrays ************************************//
#define BUFFERSIZE 16384
#define BUFFERSIZE_M1 16383
#define BUFFERSIZE_M2 16382

//********************************* Fixed Delay Samples *********************************//
#define DELAYSAMPLES_1 280              // 281 - 1
#define DELAYSAMPLES_2 1122             // 1123 - 1
#define DELAYSAMPLES_3 862              // 863 - 1
#define DELAYSAMPLES_4 466              // 467 - 1
#define DELAYSAMPLES_5 718              // 719 - 1
#define DELAYSAMPLES_6 1030             // 1031 - 1
#define DELAYSAMPLES_7 886              // 887 - 1
#define DELAYSAMPLES_8 1216             // 1217 - 1
#define DELAYSAMPLES_9 378              // 379 - 1
#define DELAYSAMPLES_10 1102            // 1103 - 1
#define DELAYSAMPLES_11 928             // 929 - 1
#define DELAYSAMPLES_12 490             // 491 - 1
#define DELAYSAMPLES_13 682             // 683 - 1
#define DELAYSAMPLES_14 1018            // 1019 - 1
#define DELAYSAMPLES_15 858             // 859 - 1
#define DELAYSAMPLES_16 1366            // 1367 - 1

#define DELAYSAMPLES_L 2916
#define DELAYSAMPLES_R 2676


//********************************* Fixed Gain Amounts **********************************//
#define GAIN_1 0.617748f
#define GAIN_2 0.630809f
#define GAIN_3 0.64093f
#define GAIN_4 0.653011f


class Reverb
{
public:
    Reverb();               // Default Constructor

    ~Reverb(){}               // Destructor

    float mReverbOut_L, mReverbOut_R;
    float mFeedbackOut;

    void applyReverb(float _EchosSample_L, float _EchosSample_R, float _ReverbLevel);

    void setReverbParams(unsigned char _ctrlID, float _ctrlVal);

    inline void applySmoother();


private:
    //******************************** Control Variables ********************************//
    float mDry;
    float mWet;
    float mFeed;
    float mBalance;
    float mDepth;
    float mAbAmnt;
    float mFBAmnt;
    float mHpOmega, mLpOmega;

    float mSize;
    float mColor;
    float mPreDelayTime_L, mPreDelayTime_R;
    float mChorus;

    //************************* Channel Variables and Filters ***************************//
    uint32_t mSampleBufferIndx;                       // sample buffer index

    std::array<float, BUFFERSIZE> mAsymBuffer_L;      // sample buffers for writing and reading the samples
    std::array<float, BUFFERSIZE> mAsymBuffer_R;

    std::array<float, BUFFERSIZE> mDelayBuffer_L1;
    std::array<float, BUFFERSIZE> mDelayBuffer_L2;
    std::array<float, BUFFERSIZE> mDelayBuffer_L3;
    std::array<float, BUFFERSIZE> mDelayBuffer_L4;
    std::array<float, BUFFERSIZE> mDelayBuffer_L5;
    std::array<float, BUFFERSIZE> mDelayBuffer_L6;
    std::array<float, BUFFERSIZE> mDelayBuffer_L7;
    std::array<float, BUFFERSIZE> mDelayBuffer_L8;
    std::array<float, BUFFERSIZE> mDelayBuffer_L9;

    std::array<float, BUFFERSIZE> mDelayBuffer_R1;
    std::array<float, BUFFERSIZE> mDelayBuffer_R2;
    std::array<float, BUFFERSIZE> mDelayBuffer_R3;
    std::array<float, BUFFERSIZE> mDelayBuffer_R4;
    std::array<float, BUFFERSIZE> mDelayBuffer_R5;
    std::array<float, BUFFERSIZE> mDelayBuffer_R6;
    std::array<float, BUFFERSIZE> mDelayBuffer_R7;
    std::array<float, BUFFERSIZE> mDelayBuffer_R8;
    std::array<float, BUFFERSIZE> mDelayBuffer_R9;

    float mDelayStateVar_L1;
    float mDelayStateVar_L2;
    float mDelayStateVar_L3;
    float mDelayStateVar_L4;
    float mDelayStateVar_L5;
    float mDelayStateVar_L6;
    float mDelayStateVar_L7;
    float mDelayStateVar_L8;
    float mDelayStateVar_L9;

    float mDelayStateVar_R1;
    float mDelayStateVar_R2;
    float mDelayStateVar_R3;
    float mDelayStateVar_R4;
    float mDelayStateVar_R5;
    float mDelayStateVar_R6;
    float mDelayStateVar_R7;
    float mDelayStateVar_R8;
    float mDelayStateVar_R9;


    //****************************** Reverb Modulation **********************************//
    float mLFOStateVar_1, mLFOStateVar_2;
    float mLFOWarpedFreq_1, mLFOWarpedFreq_2;


    //********************************** Loop Filter ************************************//
    float mLPStateVar_L, mLPStateVar_R;
    float mHPStateVar_L, mHPStateVar_R;

    float mLPCoeff_1, mLPCoeff_2;
    float mHPCoeff_1, mHPCoeff_2;


    //******************************* Smoothing Variabels *******************************//

    uint32_t mSmootherMask;                    // Smoother Mask (ID 1: dry, ID 2: wet, ID 3: , ID 4: )

    // Mask ID: 1
    float mDry_base;
    float mDry_target;
    float mDry_diff;
    float mDry_ramp;

    // Mask ID: 2
    float mWet_base;
    float mWet_target;
    float mWet_diff;
    float mWet_ramp;

    // Mask ID: 3
    float mFeed_base;
    float mFeed_target;
    float mFeed_diff;
    float mFeed_ramp;

    // Mask ID: 4
    uint32_t mPrSmCounter;
    float mPreDelayTime_ramp;

    float mPreDelayTime_L_base;
    float mPreDelayTime_L_target;
    float mPreDelayTime_L_diff;

    float mPreDelayTime_R_base;
    float mPreDelayTime_R_target;
    float mPreDelayTime_R_diff;

    // MAsk ID: 5
    uint32_t mDepthSmCounter;

    float mDepth_ramp;
    float mDepth_base;
    float mDepth_target;
    float mDepth_diff;

    // Mask ID: 6


    //*********************************** Controls IDs **********************************//

    enum CtrlID: unsigned char
    {
#ifdef REMOTE61                         // ReMote 61
        SIZE                = 0x15,
        COLOR               = 0x16,
        CHORUS              = 0x17,
        PRE_DELAY           = 0x18,
        MIX                 = 0x1C
#endif
#ifndef REMOTE61
        SIZE                = ,
        COLOR               = ,
        CHORUS              = ,
        PRE_DELAY           = ,
        MIX                 =
#endif
    };

    //**************************** Helper Functions ***************************//
    void calcFeedAndBalance();
    void calcLpAndHpCutFreq();
};