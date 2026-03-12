#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "Operator.h"

void getOperators(AsyncWebServer &server, std::vector<Operator> &operators);
void getOperatorById(AsyncWebServer &server, std::vector<Operator> &operators);
void postData(AsyncWebServer &server, std::vector<Operator> &operators);
void deleteOperatorbyId(AsyncWebServer &server, std::vector<Operator> &operators);
void updateOperatorById(AsyncWebServer &server, std::vector<Operator> &operators);