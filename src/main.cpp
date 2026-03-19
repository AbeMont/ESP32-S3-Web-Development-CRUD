#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include <vector>
#include "Operator.h"
// Header Files
#include "getRequests/getRequests.h"
#include "printStatements/printStatements.h"
#include "networkConnection/networkConnection.h"
#include "handlers/handlers.h"

// You can define a std::vector inside setup() or loop(), but if you do, the vector is treated 
// as a local variable, meaning it is created and destroyed every time that function runs.
// Defining a vector outside of setup() and loop() (globally) is generally preferred because 
// it provides persistence (data stays between loops), consistent memory management, 
// and scope accessibility across your entire sketch
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
  operators.push_back(Operator(4, "Motoko kusanagi", "M9", "Takicoma Unit"));

  printOperators(operators);

  // Connecting to the Network
  connectToNetwork();
  printNetworkInit(serverPort);
  neopixelWrite(RGB_BUILTIN, 0, 30, 0);

  // GET Requests
  getOperatorsHandler(server, operators);
  getOperatorByIdHandler(server, operators);
  setupGetRequestRoutes(server);

  // POST Request
  postDataHandler(server, operators);

  // DELETE Requests
  deleteOperatorbyIdHandler(server, operators);

  // PUT Requests
  updateOperatorByIdHandler(server, operators);

  // Begin Sever
  server.begin();
}

void loop() { }

