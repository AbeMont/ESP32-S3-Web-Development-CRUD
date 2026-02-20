#include <WiFi.h>
// #include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "index_html.h"
#include "Operator.h"
#include <vector>
#include <cstdlib> // Required header for atoi()
#include <SPIFFS.h>
#include "getRequests/getRequests.h"

std::vector<Operator> operators;

// Create AsyncWebServer object on port 80
#define serverPort 3000
AsyncWebServer server(serverPort);

void printNetworkInit() {
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println (WiFi.localIP());
  Serial.print("Port: ");
  Serial.println(serverPort);
  Serial.print("URL: ");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(serverPort);
}

// Main Website
void loadWebsite() {
    Serial.println("Loading index.html...");
    neopixelWrite(RGB_BUILTIN, 0, 30, 0);
     // Loads index.html
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/html", index_html);
    });
}

void loadFiles() {
  // load css
  server.on("/css/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/css/bootstrap.min.css", "text/css");
  });
  // load js
  server.on("/js/bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/js/bootstrap.min.js");
  });
}

void printOperators() {
  // Push to our C++ Operators Array
  for (int i = 0; i < operators.size(); i++) {
    Serial.println();
    Serial.print("id: ");
    Serial.println(operators[i].id);
    Serial.print("Name: ");
    Serial.println(operators[i].name);
    Serial.print("Weapon: ");
    Serial.println(operators[i].weapon);
    Serial.print("MetalGear: ");
    Serial.println(operators[i].metalGear);
    Serial.println("-------------------");
  }
}

void getOperators() {
  server.on("/getOperators", HTTP_GET, [](AsyncWebServerRequest *request){
    StaticJsonDocument<512> operatorsDoc;
    JsonArray dataArray = operatorsDoc.to<JsonArray>();

    for (const auto& item : operators) {
      // Create a nested object for each item
      JsonObject obj = dataArray.createNestedObject();

      // Add key-value pairs to the JSON object
      obj["id"] = item.id;
      obj["name"] = item.name;
      obj["weapon"] = item.weapon;
      obj["metalGear"] = item.metalGear;
    }

    String jsonResponse;
    serializeJson(operatorsDoc, jsonResponse);
    request->send(200, "application/json",jsonResponse);
  });
}

void getOperatorById() {
  server.on("/getOperatorById", HTTP_GET, [](AsyncWebServerRequest *request){

    if (request->hasParam("id")) {
      StaticJsonDocument<128> operatorDoc;
      String jsonResponse;

      String operatorIdParam = request->getParam("id")->value();
      // converts string to int
      int id = atoi(operatorIdParam.c_str());
      // find operator by id
      Operator* foundOperator = getOperatorbyId(operators, id);

      if (foundOperator) {
        operatorDoc["id"] = foundOperator->id;
        operatorDoc["name"] = foundOperator->name;
        operatorDoc["weapon"] = foundOperator->weapon;
        operatorDoc["metalGear"] = foundOperator->metalGear;

        serializeJson(operatorDoc, jsonResponse);
        Serial.println(jsonResponse);
      } else {
        operatorDoc["error"] = "Operator does not exist";
        serializeJson(operatorDoc, jsonResponse);
        Serial.println(jsonResponse);
      }
      request->send(200, "application/json", jsonResponse);
    }
  });
}

void postData() {
  server.on("/post-json-data", HTTP_POST, [](AsyncWebServerRequest *request) {
    Serial.println("POST Test...");
  }, NULL, [](AsyncWebServerRequest *request, 
    uint8_t *data, 
    size_t len, 
    size_t index, 
    size_t total) {
    StaticJsonDocument<256> postDoc;
    // The body handler callback
    Serial.println("Receiving JSON body...");

    // Deserialize the JSON data
    DeserializationError error = deserializeJson(postDoc, data, len);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      request->send(400, "text/plain", "Invalid JSON format");
    } else {

      // Extract data from the JSON object
      const int   key0 = postDoc["id"];
      const char* key1 = postDoc["name"];
      const char* key2 = postDoc["weapon"];
      const char* key3 = postDoc["metalGear"];

      // Clear postDoc to create response to be sent back
      postDoc.clear();

      postDoc["code"] = 200;
      postDoc["submitted"] = true;
      postDoc["data"]["id"] = key0;
      postDoc["data"]["name"] = key1;
      postDoc["data"]["weapon"] = key2;
      postDoc["data"]["metalGear"] = key3;

      // push to C++ Array
      operators.push_back(Operator(key0, key1, key2, key3));

      String jsonResponse;
      serializeJson(postDoc, jsonResponse);

      Serial.println(jsonResponse);
      request->send(200, "application/json", jsonResponse);
    }
  });
}

void deleteOperatorbyId() {
  server.on("/deleteOperatorbyId", HTTP_DELETE, [](AsyncWebServerRequest *request){

    if (request->hasParam("id")) {

      String operatorIdParam = request->getParam("id")->value();
      // converts string to int
      int id = atoi(operatorIdParam.c_str());

      // Remove Operator By Id
      removeOperatorById(operators,id);

      // Return New Array to response (May need to create a separate function)
      StaticJsonDocument<512> operatorsDoc;
      JsonArray dataArray = operatorsDoc.to<JsonArray>();

      // The operators param is from the actual Array defined above
      for (const auto& item : operators) {
        // Create a nested object for each item
        JsonObject obj = dataArray.createNestedObject();

        // Add key-value pairs to the JSON object
        obj["id"] = item.id;
        obj["name"] = item.name;
        obj["weapon"] = item.weapon;
        obj["metalGear"] = item.metalGear;
      }

      String jsonResponse;
      serializeJson(operatorsDoc, jsonResponse);

      request->send(200, "application/json", jsonResponse);
    }
  });
}

void updateOperatorById() {
  server.on("/updateOperatorById", HTTP_PUT, [](AsyncWebServerRequest *request){
    Serial.println("Update Method");
  }, NULL, [](AsyncWebServerRequest *request, 
    uint8_t *data, 
    size_t len, 
    size_t index, 
    size_t total) {
    StaticJsonDocument<256> postDoc;
    // The body handler callback
    Serial.println("Receiving JSON body...");

    // Deserialize the JSON data
    DeserializationError error = deserializeJson(postDoc, data, len);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      request->send(400, "text/plain", "Invalid JSON format");
    } else {

      // Extract data from the JSON object
      const int   key0 = postDoc["id"];
      const char* key1 = postDoc["name"];
      const char* key2 = postDoc["weapon"];
      const char* key3 = postDoc["metalGear"];

      // Update to C++ Array
      Operator* updatedOperator = updateOperatorById(operators, key0, key1, key2, key3);

      // Clear postDoc to create response to be sent back
      postDoc.clear();

      if(updatedOperator) {
        postDoc["code"] = 200;
        postDoc["updated"] = true;
        postDoc["data"]["id"] = updatedOperator->id;
        postDoc["data"]["name"] = updatedOperator->name;
        postDoc["data"]["weapon"] = updatedOperator->weapon;
        postDoc["data"]["metalGear"] = updatedOperator->metalGear;
      } else {
        postDoc["message"] = "Operator not found";
      }

      String jsonResponse;
      serializeJson(postDoc, jsonResponse);

      Serial.println(jsonResponse);
      request->send(200, "application/json", jsonResponse);
    }
  });
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(1000);

  if(!SPIFFS.begin(true)) {
    Serial.println("An error has occurred mounting file system");
    return;
  }

  operators.push_back(Operator(1, "Lain Iwakura", "MP5N", "Navi"));
  operators.push_back(Operator(2, "Ocelot", "SAA", "Metal Gear Ray"));
  operators.push_back(Operator(3, "XOF Operator", "MAC-11", "Uh-60"));

  printOperators();

  /////////////////////////////
  // Connecting to the Network
  ////////////////////////////
  // Get our network name and credentials
  const String ssid = "xxxx";
  const String password = "xxxx";

    // Connect to the Wifi Network
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin (ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay (500);
    Serial.print("...");
  }

  // After successful connection,
  // Print out ip, port to get url for the browser
  printNetworkInit();

  //////////////////
  // Load index.html
  //////////////////
  loadWebsite();
  loadFiles();

  ///////////////
  // GET Requests
  ///////////////
  getOperators();
  getOperatorById();
  setup_get_request_routes(server);

  ///////////////
  // POST Request
  ///////////////
  postData();

  //////////////////
  // DELETE Requests
  //////////////////
  deleteOperatorbyId();

  ///////////////
  // PUT Requests
  ///////////////
  updateOperatorById();

  // Begin Sever
  server.begin();
}

void loop() { }


// Example Fix (Capture by Value)
// void setupHandler() {
//   String myVariable = "Hello"; 

//   // Capture 'myVariable' by value using [myVariable]
//   server.on("/somepath", [myVariable]() {
//     // myVariable is a local copy inside the lambda
//     Serial.println(myVariable);
//     // You can also capture all used variables by value with [=]
//   });
// }
