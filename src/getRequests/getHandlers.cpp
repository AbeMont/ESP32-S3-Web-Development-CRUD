#include "getRequests.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

void getSnakeData(AsyncWebServerRequest *request) {
    StaticJsonDocument<128> doc;

    doc["name"] = "Solid Snake";
    doc["weapon"] = "Mk.21 SOCOM Pistol";
    doc["metalGear"] = "Metal_Gear_Rex";

    String jsonResponse;
    serializeJson(doc, jsonResponse);

    Serial.println(jsonResponse);

    request->send(200, "application/json",jsonResponse);
};

void getJS(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/js/bootstrap.min.js");
}

void getCss(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/css/bootstrap.min.css", "text/css");
}

void setup_get_request_routes(AsyncWebServer& server) {
    server.on("/getSnakeData", HTTP_GET, getSnakeData);
    server.on("/js/bootstrap.min.js", HTTP_GET, getJS);
    server.on("/css/bootstrap.min.css", HTTP_GET, getCss);
}