// http.h
#pragma once

#include <WebServer.h>

// 初始化HTTP服务（在 setup() 中调用）
void initHttpControl(WebServer &server);

// 每帧处理HTTP请求（在 loop() 中调用）
void handleHttpClient();
