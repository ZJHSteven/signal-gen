#pragma once

struct SystemState
{
    float pwmFreq = 1000;
    int pwmDuty = 127;
    float sineFreq = 1000;
    float amplitude = 1.0;
};

extern SystemState systemState;
extern SystemState lastState;

void initState();
