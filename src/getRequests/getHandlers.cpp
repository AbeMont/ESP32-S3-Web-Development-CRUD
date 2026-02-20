#include "getRequests.h"
#include <Arduino.h>
#include <ArduinoJson.h>

void getSnakeData(AsyncWebServerRequest *request)
{
    StaticJsonDocument<128> doc;

    doc["name"] = "Solid Snake";
    doc["weapon"] = "Mk.21 SOCOM Pistol";
    doc["metalGear"] = "Metal Gear Rex";

    String jsonResponse;
    serializeJson(doc, jsonResponse);

    Serial.println(jsonResponse);

    request->send(200, "application/json",jsonResponse);
};

void setup_get_request_routes(AsyncWebServer& server){
    server.on("/getSnakeData", HTTP_GET, getSnakeData);
}