#include <Arduino.h>
#include <state.h>
#include "pwm.h"
#include "my_ad9833.h"
#include "http.h"

WebServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(500); // 等一会串口准备好

  // 初始化状态
  initState();
  // 初始化 HTTP 服务器
  initHttpControl(server);
  
  // 初始化 PWM
  initPWM();

  // 初始化 AD9833
  initAD9833();

  // 打印提示
  Serial.println("开始PWM输出 + ADC采样");
}

void loop()
{
  // 处理 HTTP 请求
  handleHttpClient();
  // 更新 AD9833
  updateAD9833();
  // 更新 PWM
  updatePWM();
}
