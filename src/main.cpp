#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include <vector>
#include <AsyncTCP.h>
#include "Operator.h"
// Header Files
#include "getRequests.h"
#include "printStatements.h"
#include "networkConnection.h"
#include "handlers.h"
#include "RFIDModule.h"

// You can define a std::vector inside setup() or loop(), but if you do, the vector is treated 
// as a local variable, meaning it is created and destroyed every time that function runs.
// Defining a vector outside of setup() and loop() (globally) is generally preferred because 
// it provides persistence (data stays between loops), consistent memory management, 
// and scope accessibility across your entire sketch
std::vector<Operator> operators;

// Create AsyncWebServer object on port 80
int serverPort = 3000;
AsyncWebServer server(serverPort);

// Init RFID module
RFIDModule rfid(4, 5, 6, 7, 15);
// Create eventsource
AsyncEventSource rfidEvent("/rfidEvent");
// login state
bool loggedIn = false;
// Timer variables
unsigned long lastTime = 0;  
unsigned long timerDelay = 750;

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

  // RFID Connect
  rfid.rfidAsyncConnect(rfid, rfidEvent);

  // RFID Event
  server.addHandler(&rfidEvent);

  // Begin Server
  server.begin();

  // Begin RFID Card Reader
  rfid.SPIBegin();
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    rfid.rfidHandler(rfid, rfidEvent, loggedIn);
  }
}

