#include <pwm.h>

// 配置 PWM 输出的相关参数
const int pwmPin = 18; // PWM 输出引脚
const int pwmChannel = 0;
const int pwmFreq = 1000;    // 频率 1kHz
const int pwmResolution = 8; // 8位分辨率 → 占空比范围0~255
const int pwmDuty = 128;     // 占空比50%

void initPWM() {
    // 初始化 PWM
    ledcSetup(pwmChannel, pwmFreq, pwmResolution);
    ledcAttachPin(pwmPin, pwmChannel);
    ledcWrite(pwmChannel, pwmDuty); // 输出占空比
}