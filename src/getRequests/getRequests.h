#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include "index_html.h"

void setup_get_request_routes(AsyncWebServer &server);
