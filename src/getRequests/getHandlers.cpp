#include "getRequests.h"
#include "views/login.h"

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

void loadIndexHtml(AsyncWebServerRequest *request) {
    Serial.println("Loading index.html...");
    request->send(200, "text/html", index_html);
}


void getBootstrapJS(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/js/bootstrap.min.js", "application/javascript");
}

void getApiExamples(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/js/apiExamples.js", "application/javascript");
};

void getCustomEventsJS(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/js/customEvents.js", "application/javascript");
}

void getLoginJS(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/js/login.js", "application/javascript");
}

void getCss(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/css/bootstrap.min.css", "text/css");
}

void getLoginPage(AsyncWebServerRequest *request) {
    Serial.println("Loading login Page...");
    request->send(200, "text/plain", login_html);
}

void setupGetRequestRoutes(AsyncWebServer& server) {
    // Loads our main index.html
    server.on("/", HTTP_GET, loadIndexHtml);
    server.on("/getSnakeData", HTTP_GET, getSnakeData);
    server.on("/login", HTTP_GET, getLoginPage);

    // Load our js & css files
    if(!SPIFFS.begin(true)) {
        Serial.println("An error has occurred mounting file system");
        return;
    }
    server.on("/js/bootstrap.min.js", HTTP_GET, getBootstrapJS);
    server.on("/js/apiExamples.js", HTTP_GET, getApiExamples);
    server.on("/js/customEvents.js", HTTP_GET, getCustomEventsJS);
    server.on("/js/login.js", HTTP_GET, getLoginJS);
    server.on("/css/bootstrap.min.css", HTTP_GET, getCss);
}