#include <ESPAsyncWebServer.h>
#include <cstdlib> // Required header for atoi()
#include <ArduinoJson.h>
#include "Operator.h"

Operator* getOperatorbyId(std::vector<Operator> &operators, int targetId);
void deleteOperatorById(std::vector<Operator> &operators, int targetId);
Operator* updateOperatorById(std::vector<Operator> &operators, 
    int targetId, 
    String updatedName,
    String updatedWeapon,
    String updatedMetalgear);

void getOperatorsHandler(AsyncWebServer &server, std::vector<Operator> &operators);
void getOperatorByIdHandler(AsyncWebServer &server, std::vector<Operator> &operators);
void postDataHandler(AsyncWebServer &server, std::vector<Operator> &operators);
void deleteOperatorbyIdHandler(AsyncWebServer &server, std::vector<Operator> &operators);
void updateOperatorByIdHandler(AsyncWebServer &server, std::vector<Operator> &operators);