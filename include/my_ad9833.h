#pragma once
#include <Arduino.h>

void initAD9833();             // 初始化模块
void updateAD9833();           // 每次循环更新
void setFrequency(float freq); // 设置频率
