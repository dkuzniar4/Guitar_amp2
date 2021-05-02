/*
  ==============================================================================

    Engine.h
    Created: 7 Feb 2021 12:08:55pm
    Author:  Dominik Kuzniar / dkuzniar4

  ==============================================================================
*/

#pragma once

#define ABS(input) (float)(input > 0.0f ? input : -input)
#define PI (3.141592f)
#define FIR_MAX_LEN 1000

class IIR_filter
{
public:
    IIR_filter();
    float processing(float input, float* IN_coeffs, float* OUT_coeffs);
    void setVolume(float value);
    float getVolume(void);

    float volume = 1.0;

private:
    float IN_buffer[5] = { 0 };
    float OUT_buffer[5] = { 0 };
};

class FIR
{
public:
    FIR::FIR();
    float processing(float input, float* IR, unsigned int IR_len);

private:
    float buffer[FIR_MAX_LEN * 2] = { 0 };
    unsigned int buffIndex = 0;
};

class Saturator
{
public:
    Saturator();
    float processing(float input);
    void setThreshold(float value);
    void setGainAbove(float value);

    float getThreshold(void);
    float getGainAbove(void);

    void setPlus(int value);
    void setMinus(int value);

    int getPlus(void);
    int getMinus(void);
private:
    float threshold;
    float gainAbove;
    int plus;
    int minus;
};
