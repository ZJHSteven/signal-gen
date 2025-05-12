#include <Arduino.h>
#include <state.h>

// 配置 PWM 输出
const int pwmPin = 18; // PWM 输出引脚
const int pwmChannel = 0;
const int pwmFreq = systemState.pwmFreq;    // 频率 1kHz
const int pwmResolution = 8; // 8位分辨率 → 占空比范围0~255
const int pwmDuty = systemState.pwmDuty;     // 占空比50%


void setup()
{
  Serial.begin(115200);
  delay(500); // 等一会串口准备好

  // 初始化 PWM
  ledcSetup(pwmChannel, pwmFreq, pwmResolution);
  ledcAttachPin(pwmPin, pwmChannel);
  ledcWrite(pwmChannel, pwmDuty); // 输出占空比

  // 打印提示
  Serial.println("开始PWM输出 + ADC采样");
}

void loop()
{

}
