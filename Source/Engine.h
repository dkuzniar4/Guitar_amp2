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
#define RB_SIZE 1000

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

class RingBuffer
{
public:
    RingBuffer();
    ~RingBuffer();
    void putDataToBuffer(float data);
    float getDataFromBuffer(int n_samples);

private:
    float buffer[RB_SIZE];
    int bufferIdx;
    int bufferSize;
};

class FIR
{
public:
    FIR();
    float processing(float input, float* IR, unsigned int IR_len);

private:
    RingBuffer rbuff;
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

class Amp
{
public:
    Amp();
    float processing(float input);

    void setBassVolume(float value);
    void setMidVolume(float value);
    void setTrebleVolume(float value);
    void setInputVolume(float value);
    void setMasterVolume(float value);

    float getBassVolume(void);
    float getMidVolume(void);
    float getTrebleVolume(void);
    float getInputVolume(void);
    float getMasterVolume(void);

    void setAmpState(int value);
    void setCabState(int value);
    int getAmpState(void);
    int getCabState(void);

    void setPlus(int value);
    void setMinus(int value);

    int getPlus(void);
    int getMinus(void);

    void setThreshold(float value);
    void setGainAbove(float value);

    float getThreshold(void);
    float getGainAbove(void);

private:
    int amp_state = 1;
    int cab_state = 1;

    float inputVolume = 1.0;
    float masterVolume = 1.0;

    IIR_filter bass_filter;
    IIR_filter mid_filter;
    IIR_filter treble_filter;

    Saturator sat;

    FIR cabinet;
};

