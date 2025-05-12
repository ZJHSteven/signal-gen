#include <Arduino.h>
#include <state.h>
#include <pwm.h>

void setup()
{
  Serial.begin(115200);
  delay(500); // 等一会串口准备好

  // 初始化 PWM
  initPWM();

  // 打印提示
  Serial.println("开始PWM输出 + ADC采样");
}

void loop()
{

}
