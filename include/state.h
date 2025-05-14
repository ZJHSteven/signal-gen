#pragma once

struct SystemState
{
    int pwmFreq = 1000;
    int pwmDuty = 127;
    int sineFreq = 1000;
    float sineAmplitude = 1.0;
    float pwmAmplitude = 1.0;
    int potentiometer = 68;
    String waveType = "sine"; // 新增字段：波形类型（默认正弦波）
};

extern SystemState systemState;
extern SystemState lastState;

void initState();
