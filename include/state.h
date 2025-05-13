#pragma once

struct SystemState
{
    int pwmFreq = 1000;
    int pwmDuty = 127;
    int sineFreq = 1000;
    float sineAmplitude = 1.0;
    float amplitude = 1.0;
    int potentiometer = 68;
};

extern SystemState systemState;
extern SystemState lastState;

void initState();
