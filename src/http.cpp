// http.cpp
#include "http.h"
#include <ArduinoJson.h>
#include "state.h" // 访问 systemState 和 lastState
#include <WiFi.h>

WebServer server(80); // 创建 WebServer 实例

const char *ssid = "Abs";
const char *password = "135792468";

// ==== CORS 处理 ====
void setCORSHeaders() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// ==== 处理POST请求 ====
void handleControlPost() {
    setCORSHeaders();

    if (!server.hasArg("plain")) {
        server.send(400, "application/json", "{\"error\":\"No body received\"}");
        return;
    }

    String body = server.arg("plain");
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, body);

    if (error) {
        server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }

    // 简单字段映射（字段名可后续替换）
    if (doc.containsKey("waveType"))
    {
        String waveType = String((const char *)doc["waveType"]); // 从前端获取 waveType

        if (doc.containsKey("frequency"))
        {
            if (waveType == "sine")
            {
                systemState.sineFreq = doc["frequency"];
            }
            else if (waveType == "pulse")
            {
                systemState.pwmFreq = doc["frequency"];
            }
        }
        if (doc.containsKey("amplitude"))
        {
            if (waveType == "sine")
            {
                // x 是输入的电压值（前端传递的 amplitude）
                float x = doc["amplitude"];
                // 电阻档位置 = - (2/3) * 256 * x + 256
                systemState.potentiometer = static_cast<int>(-(256.0f / 3.0f) * x + 256.0f);
            }
            else if (waveType == "pulse")
            {
                systemState.pwmAmplitude = doc["amplitude"];
            }
        }
        if (doc.containsKey("duty"))
        {
            // 前端传递的是百分比值（1% 到 98%）
            int dutyPercent = doc["duty"];
            // 将百分比值映射到 0 到 255 的范围
            systemState.pwmDuty = map(dutyPercent, 0, 100, 0, 255);
        }

    }

    server.send(200, "application/json", "{\"status\":\"ok\"}");
}

// ==== OPTIONS 预检 ====
void handleOptions() {
    setCORSHeaders();
    server.send(204); // No Content
}

// ==== 初始化 HTTP Server ====
void initHttpControl() {
    // 启动 Wi-Fi 连接
    WiFi.begin(ssid, password);

    // 等待 Wi-Fi 连接成功
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("."); // 输出连接进度
    }

    Serial.println("");
    Serial.println("WiFi connected");

    // 打印获得的 IP 地址
    Serial.println("IP Address: " + WiFi.localIP().toString());


    server.on("/control", HTTP_OPTIONS, handleOptions);
    server.on("/control", HTTP_POST, handleControlPost);
    server.begin();
}

// ==== 主循环处理 ====
void handleHttpClient() {
    server.handleClient();
}
