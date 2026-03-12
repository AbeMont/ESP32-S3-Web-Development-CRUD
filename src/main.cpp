#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include "Operator.h"
#include <vector>
#include <cstdlib> // Required header for atoi()
// Header Files
#include "getRequests/getRequests.h"
#include "printStatements/printStatements.h"
#include "networkConnection/networkConnection.h"
#include "handlers/handlers.h"

std::vector<Operator> operators;

// Create AsyncWebServer object on port 80
int serverPort = 3000;
AsyncWebServer server(serverPort);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(1000);

  operators.push_back(Operator(1, "Lain Iwakura", "MP5N", "Navi"));
  operators.push_back(Operator(2, "Ocelot", "SAA", "Metal Gear Ray"));
  operators.push_back(Operator(3, "XOF Operator", "MAC-11", "Uh-60"));

  printOperators(operators);

  /////////////////////////////
  // Connecting to the Network
  ////////////////////////////
  connectToNetwork();
  printNetworkInit(serverPort);
  neopixelWrite(RGB_BUILTIN, 0, 30, 0);

  ///////////////
  // GET Requests
  ///////////////
  getOperators(server, operators);
  getOperatorById(server, operators);
  setup_get_request_routes(server);

  ///////////////
  // POST Request
  ///////////////
  postData(server, operators);

  //////////////////
  // DELETE Requests
  //////////////////
  deleteOperatorbyId(server, operators);

  ///////////////
  // PUT Requests
  ///////////////
  updateOperatorById(server, operators);

  // Begin Sever
  server.begin();
}

void loop() { }

