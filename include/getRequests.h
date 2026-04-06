#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include "index_html.h"

void setupGetRequestRoutes(AsyncWebServer &server);
