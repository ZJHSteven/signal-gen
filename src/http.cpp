// http.cpp
#include "http.h"
#include <ArduinoJson.h>
#include "state.h" // 访问 systemState 和 lastState

static WebServer *webServerRef = nullptr;


// ==== CORS 处理 ====
void setCORSHeaders() {
    webServerRef->sendHeader("Access-Control-Allow-Origin", "*");
    webServerRef->sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    webServerRef->sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// ==== 处理POST请求 ====
void handleControlPost() {
    setCORSHeaders();

    if (!webServerRef->hasArg("plain")) {
        webServerRef->send(400, "application/json", "{\"error\":\"No body received\"}");
        return;
    }

    String body = webServerRef->arg("plain");
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, body);

    if (error) {
        webServerRef->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }

    // 简单字段映射（字段名可后续替换）
    if (doc.containsKey("frequency"))
    {
        if (systemState.waveType == "sine")
        {
            systemState.sineFreq = doc["frequency"];
        }
        else if (systemState.waveType == "pulse")
        {
            systemState.pwmFreq = doc["frequency"];
        }
    }
    if (doc.containsKey("amplitude"))
    {
        if (systemState.waveType == "sine")
        {
            systemState.potentiometer = doc["amplitude"];
        }
        else if (systemState.waveType == "pulse")
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
    if (doc.containsKey("waveType"))
    {
        systemState.waveType = String((const char *)doc["waveType"]);
    }

    webServerRef->send(200, "application/json", "{\"status\":\"ok\"}");
}

// ==== OPTIONS 预检 ====
void handleOptions() {
    setCORSHeaders();
    webServerRef->send(204); // No Content
}

// ==== 初始化 HTTP Server ====
void initHttpControl(WebServer &server) {
    webServerRef = &server;

    server.on("/control", HTTP_OPTIONS, handleOptions);
    server.on("/control", HTTP_POST, handleControlPost);
    server.begin();
}

// ==== 主循环处理 ====
void handleHttpClient() {
    if (webServerRef) webServerRef->handleClient();
}
