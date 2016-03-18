#pragma once
#include "tools.h"

enum class BiquadFiltertype
{
    lowpass,
    highpass,
    lowshelf,
    highshelf
};

class BiquadFilters
{
public:
    BiquadFilters(int _sRate,
                  float _cutFreq = 22000.f,
                  float _shelfAmp = 0.f,
                  float _resonance = 0.5f,
                  BiquadFiltertype _filtertype = BiquadFiltertype::lowpass)           // Constructor for static a biquad Filter
        : sRate(static_cast<float>(_sRate))
        , inCh1Delay1(0.f)          //Delays
        , inCh1Delay2(0.f)
        , outCh1Delay1(0.f)
        , outCh1Delay2(0.f)
        , inCh2Delay1(0.f)
        , inCh2Delay2(0.f)
        , outCh2Delay1(0.f)
        , outCh2Delay2(0.f)
        , b0(0.f)                   //Coefficients
        , b1(0.f)
        , b2(0.f)
        , a0(0.f)
        , a1(0.f)
        , a2(0.f)
    {
        setCutFreq(_cutFreq);
        setShelfAmp(_shelfAmp);
        setResonance(_resonance);
        setFiltertype(_filtertype);
    }

    ~BiquadFilters(){}

    void setCutFreq(float _cutFreq)                  /*set cut frequency*/
    {
        if (_cutFreq < (sRate / 24576.f))            //Frequency clipping
        {
            _cutFreq = sRate / 24576.f;
        }

        else if (_cutFreq > (sRate / 2.125f))
        {
            _cutFreq = sRate / 2.125f;
        }

        float omega = _cutFreq * (2.f * M_PI / sRate);     //Frequncy to Omega (Warp)

        omega_cos = Nl::cos(omega);                        //alternative to cos(omega) -> tools.h ;
        omega_sin = Nl::sin(omega);                        //alternative to sin(omega) -> tools.h;

        setAlpha();
        calcCoeff();
    }

    void setShelfAmp(float _shelfAmp)               /*set shelf amplification*/
    {
        shelfAmp = pow(1.059f, _shelfAmp);          //alternative to pow(10, (_shelfAmp / 40.f))
        beta = 2.f * sqrt(shelfAmp);

        calcCoeff();
    }

    void setResonance(float _resonance)             /*set resonance*/
    {
        resonance = _resonance;

        if (resonance > 0.999f)                     //Resonance clipping
        {
            resonance = 0.999f;
        }

        else if (resonance < -0.999f)
        {
            resonance = -0.999f;
        }

        setAlpha();
        calcCoeff();
    }

    void setFiltertype(BiquadFiltertype _filtertype)                /*set filtertype*/
    {
        filtertype = _filtertype;
        resetDelays();
        calcCoeff();
    }


    float applyFilter(float currSample, unsigned int chInd)  /*apply coefficients to incoming sample*/
    {
        float output = 0.f;

        if(chInd == 0)
        {
            output += b0 * currSample;
            output += b1 * inCh1Delay1;
            output += b2 * inCh1Delay2;

            output += a1 * outCh1Delay1;
            output += a2 * outCh1Delay2;

            inCh1Delay2 = inCh1Delay1;
            inCh1Delay1 = currSample;

            outCh1Delay2 = outCh1Delay1;
            outCh1Delay1 = output;
        }

        else if (chInd == 1)
        {
            output += b0 * currSample;
            output += b1 * inCh2Delay1;
            output += b2 * inCh2Delay2;

            output += a1 * outCh2Delay1;
            output += a2 * outCh2Delay2;

            inCh2Delay2 = inCh2Delay1;
            inCh2Delay1 = currSample;

            outCh2Delay2 = outCh2Delay1;
            outCh2Delay1 = output;
        }

        return output;
    }

private:

    float omega_cos;
    float omega_sin;
    float alpha;
    float beta;
    float shelfAmp;
    float resonance;
    float sRate;

    float inCh1Delay1;          //Channel 1
    float inCh1Delay2;
    float outCh1Delay1;
    float outCh1Delay2;

    float inCh2Delay1;          //Channel 2
    float inCh2Delay2;
    float outCh2Delay1;
    float outCh2Delay2;

    float b0, b1, b2, a0, a1, a2;         //Coefficients

    BiquadFiltertype filtertype;

    void calcCoeff()                                /*check which Filter is active and calculate coefficients*/
    {
        float coeff;
        switch(filtertype)
        {
            case BiquadFiltertype::lowpass:

            a0 = 1.f + alpha;
            a1 = omega_cos * -2.f;
            a2 = 1.f - alpha;
            b0 = (1.f - omega_cos) / 2.f;
            b1 = 1.f - omega_cos;
            b2 = b0;
            break;

            case BiquadFiltertype::highpass:

            a0 = 1.f + alpha;
            a1 = omega_cos * -2.f;
            a2 = 1.f - alpha;
            b0 = (1.f + omega_cos) / 2.f;
            b1 = (1.f + omega_cos) * -1.f;
            b2 = b0;
            break;

            case BiquadFiltertype::lowshelf:
            coeff = beta * alpha;

            a0 = (shelfAmp + 1.f) + (omega_cos * (shelfAmp - 1.f)) + coeff;
            a1 = ((shelfAmp - 1.f) + (omega_cos * (shelfAmp + 1.f))) * -2.f;
            a2 = (shelfAmp + 1.f) + (omega_cos * (shelfAmp - 1.f)) - coeff;
            b0 = ((shelfAmp + 1.f) - (omega_cos * (shelfAmp - 1.f)) + coeff) * shelfAmp;
            b1 = ((shelfAmp - 1.f) - (omega_cos * (shelfAmp + 1.f))) * 2.f * shelfAmp;
            b2 = ((shelfAmp + 1.f) - (omega_cos * (shelfAmp - 1.f)) - coeff) * shelfAmp;
            break;

            case BiquadFiltertype::highshelf:
            coeff = beta * alpha;

            a0 = (shelfAmp + 1.f) - (omega_cos * (shelfAmp - 1.f)) + coeff;
            a1 = ((shelfAmp - 1.f) - (omega_cos * (shelfAmp + 1.f))) * 2.f;
            a2 = (shelfAmp + 1.f) - (omega_cos * (shelfAmp - 1.f)) - coeff;
            b0 = ((shelfAmp + 1.f) + (omega_cos * (shelfAmp - 1.f)) + coeff) * shelfAmp;
            b1 = ((shelfAmp - 1.f) + (omega_cos * (shelfAmp + 1.f))) * -2.f * shelfAmp;
            b2 = ((shelfAmp + 1.f) + (omega_cos * (shelfAmp - 1.f)) - coeff) * shelfAmp;
            break;
        }

        a1 /= (-1.f * a0);              //normalize
        a2 /= (-1.f * a0);
        b0 /= a0;
        b1 /= a0;
        b2 /= a0;
    }

    inline void setAlpha()
    {
        alpha = omega_sin * (1.f - resonance);
    }

    void resetDelays()              /*Resets the delays if the filtertype is changed - smoothing!?*/
    {
        inCh1Delay1 = 0.f;          //Channel 1
        inCh1Delay2 = 0.f;
        outCh1Delay1 = 0.f;
        outCh1Delay2 = 0.f;

        inCh2Delay1 = 0.f;          //Channel 2
        inCh2Delay2 = 0.f;
        outCh2Delay1 = 0.f;
        outCh2Delay2 = 0.f;
    }

#if 0
    /*as applied in Reaktor --- befindet sich hier vorübergehend*/
    float reakSin(float x){

        float x_square = x * x;

        x = (((((x_square * -2.39f * pow(10.f, -8.f) + 2.7526f * pow(10.f, -6.f))
                * x_square + (0.198409f * pow(10.f, -3.f)))
               * x_square + 0.008333f)
              * x_square + (-0.166667f))
             * x_square + 1.f) * x;

        return x;
    }


    /*as applied in Reaktor --- befindet sich hier vorübergehend*/
    float reakCos(float x){

        float x_square = x * x;

        x = (((((x_square * -2.605f * pow(10.f, -7.f) + 2.47609 * pow(10.f, -5.f))
                * x_square + (-0.00138884))
               * x_square + 0.0416666)
              * x_square + (-0.499923))
             * x_square) + 1.f;

        return x;
    }
#endif
};
