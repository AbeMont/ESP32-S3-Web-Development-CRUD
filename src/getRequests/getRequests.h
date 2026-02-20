#ifndef HANDLER_SETUP_H
#define HANDLER_SETUP_H

#include <ESPAsyncWebServer.h>
#include <vector>

void getSnakeData(AsyncWebServerRequest *request);
void setup_get_request_routes(AsyncWebServer& server);

#endif