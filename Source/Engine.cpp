/*
  ==============================================================================

    Engine.cpp
    Created: 7 Feb 2021 12:08:42pm
    Author:  Dominik Kuzniar / dkuzniar4

  ==============================================================================
*/

#include "Engine.h"
#include "math.h"
#include "kernels.h"
#include <cstring>

IIR_filter::IIR_filter()
{
    //todo
}

float IIR_filter::processing(float input, float* IN_coeffs, float* OUT_coeffs)
{
    float output = 0.0f;

    IN_buffer[4] = IN_buffer[3];
    IN_buffer[3] = IN_buffer[2];
    IN_buffer[2] = IN_buffer[1];
    IN_buffer[1] = IN_buffer[0];
    IN_buffer[0] = input;

    output = IN_buffer[0] * IN_coeffs[0];
    output += IN_buffer[1] * IN_coeffs[1];
    output += IN_buffer[2] * IN_coeffs[2];
    output += IN_buffer[3] * IN_coeffs[3];
    output += IN_buffer[4] * IN_coeffs[4];

    output += -OUT_buffer[0] * OUT_coeffs[1];
    output += -OUT_buffer[1] * OUT_coeffs[2];
    output += -OUT_buffer[2] * OUT_coeffs[3];
    output += -OUT_buffer[3] * OUT_coeffs[4];


    OUT_buffer[4] = OUT_buffer[3];
    OUT_buffer[3] = OUT_buffer[2];
    OUT_buffer[2] = OUT_buffer[1];
    OUT_buffer[1] = OUT_buffer[0];
    OUT_buffer[0] = output;

    return output * volume;
}

void IIR_filter::setVolume(float value)
{
    volume = value;
}

float IIR_filter::getVolume(void)
{
    return volume;
}

RingBuffer::RingBuffer()
{
    this->bufferIdx = 0;
    this->bufferSize = RB_SIZE;
    memset(this->buffer, 0, sizeof(this->buffer));
}

RingBuffer::~RingBuffer()
{

}

void RingBuffer::putDataToBuffer(float data)
{
    buffer[bufferIdx] = data;
    bufferIdx++;
    if (bufferIdx >= bufferSize)
    {
        bufferIdx = 0;
    }
}

float RingBuffer::getDataFromBuffer(int n_samples)
{
    int delay = bufferIdx - n_samples - 1;

    if (delay >= 0)
    {
        return buffer[delay];
    }
    else
    {
        return buffer[bufferSize + delay];
    }
}

FIR::FIR()
{

}

float FIR::processing(float input, float* IR, unsigned int IR_len)
{
    rbuff.putDataToBuffer(input);

    float sum = 0.0;
    for (auto i = 0; i < IR_len; i++)
    {
        sum += IR[i] * rbuff.getDataFromBuffer(i);
    }

    return sum;
}

Saturator::Saturator()
{
    // todo
}

float Saturator::processing(float input)
{
    if ((input > 0.0f) && plus)
    {
        if (input < threshold)
        {
            return input;
        }
        else
        {
            return (((input - threshold) * gainAbove) + threshold);
        }
    }
    else if ((input <= 0.0f) && minus)
    {
        if (input > -threshold)
        {
            return input;
        }
        else
        {
            return (-threshold - ((-threshold - input) * gainAbove));
        }
    }
    else
    {
        return input;
    }
}

void Saturator::setThreshold(float value)
{
    threshold = value;
}

void Saturator::setGainAbove(float value)
{
    gainAbove = value;
}

float Saturator::getThreshold(void)
{
    return threshold;
}

float Saturator::getGainAbove(void)
{
    return gainAbove;
}

void Saturator::setPlus(int value)
{
    plus = value;
}

void Saturator::setMinus(int value)
{
    minus = value;
}

int Saturator::getPlus(void)
{
    return plus;
}

int Saturator::getMinus(void)
{
    return minus;
}

Amp::Amp()
{
    setInputVolume(1.0);
    setMasterVolume(1.0);
    bass_filter.setVolume(10.0);
    mid_filter.setVolume(10.0);
    treble_filter.setVolume(10.0);

    sat.setThreshold(0.5);
    sat.setGainAbove(0.4);
    sat.setPlus(1);
    sat.setMinus(1);

    setAmpState(1);
    setCabState(1);
}

float Amp::processing(float input)
{
    float signal = input;
    float signal_bass;
    float signal_mid;
    float signal_treble;

    signal *= inputVolume;

    if (amp_state == 1)
    {
        signal_bass = bass_filter.processing(signal, IN_bass, OUT_bass);
        signal_mid = mid_filter.processing(signal, IN_mid, OUT_mid);
        signal_treble = treble_filter.processing(signal, IN_treble, OUT_treble);
        signal = signal_bass + signal_mid + signal_treble;

        signal = sat.processing(signal);
    }

    if (cab_state == 1)
    {
        signal = cabinet.processing(signal, cab_IR, 427);
    }

    signal *= masterVolume;

    return signal;
}

void Amp::setBassVolume(float value)
{
    bass_filter.setVolume(value);
}

void Amp::setMidVolume(float value)
{
    mid_filter.setVolume(value);
}

void Amp::setTrebleVolume(float value)
{
    treble_filter.setVolume(value);
}

void Amp::setInputVolume(float value)
{
    inputVolume = value;
}

void Amp::setMasterVolume(float value)
{
    masterVolume = value;
}

float Amp::getBassVolume(void)
{
    return bass_filter.getVolume();
}

float Amp::getMidVolume(void)
{
    return mid_filter.getVolume();
}

float Amp::getTrebleVolume(void)
{
    return treble_filter.getVolume();
}

float Amp::getInputVolume(void)
{
    return inputVolume;
}

float Amp::getMasterVolume(void)
{
    return masterVolume;
}

void Amp::setAmpState(int value)
{
    amp_state = value;
}

void Amp::setCabState(int value)
{
    cab_state = value;
}

int Amp::getAmpState(void)
{
    return amp_state;
}

int Amp::getCabState(void)
{
    return cab_state;
}

void Amp::setPlus(int value)
{
    sat.setPlus(value);
}

void Amp::setMinus(int value)
{
    sat.setMinus(value);
}

int Amp::getPlus(void)
{
    return sat.getPlus();
}

int Amp::getMinus(void)
{
    return sat.getMinus();
}

void Amp::setThreshold(float value)
{
    sat.setThreshold(value);
}

void Amp::setGainAbove(float value)
{
    sat.setGainAbove(value);
}

float Amp::getThreshold(void)
{
    return sat.getThreshold();
}

float Amp::getGainAbove(void)
{
    return sat.getGainAbove();
}
