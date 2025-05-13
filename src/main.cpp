#include <Arduino.h>
#include <state.h>
#include "pwm.h"
#include "my_ad9833.h"

void setup()
{
  Serial.begin(115200);
  delay(500); // 等一会串口准备好

  // 初始化 PWM
  initPWM();

  // 初始化 AD9833
  initAD9833();

  // 打印提示
  Serial.println("开始PWM输出 + ADC采样");
}

void loop()
{
  // 更新 PWM
  updateAD9833();
}
