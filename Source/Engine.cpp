/*
  ==============================================================================

    Engine.cpp
    Created: 7 Feb 2021 12:08:42pm
    Author:  Dominik Kuzniar / dkuzniar4

  ==============================================================================
*/

#include "Engine.h"
#include "math.h"

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

FIR::FIR()
{
    buffIndex = 0;
}

float FIR::processing(float input, float* IR, unsigned int IR_len)
{
    buffer[buffIndex] = input;
    buffer[buffIndex + IR_len] = input;

    float sum = 0.0;
    for (auto i = 0; i < IR_len; i++)
    {
        sum += IR[i] * buffer[buffIndex + IR_len - i];
    }

    buffIndex++;
    if (buffIndex >= IR_len)
    {
        buffIndex = 0;
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
