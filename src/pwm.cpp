#include "pwm.h"

// 配置 PWM 输出的相关参数
const int pwmPin = 19; // PWM 输出引脚
const int pwmChannel = 0; // 使用的PWM通道
const int pwmFreq = 1000;    // 频率 1kHz
const int pwmResolution = 8; // 8位分辨率 → 占空比范围0~255
const int pwmDuty = 128;     // 占空比50%

// 初始化 PWM
void initPWM() {
    ledcSetup(pwmChannel, pwmFreq, pwmResolution); // 配置PWM通道、频率和分辨率
    ledcAttachPin(pwmPin, pwmChannel);             // 将PWM通道绑定到指定引脚
    ledcWrite(pwmChannel, pwmDuty);                // 设置PWM占空比，开始输出
}