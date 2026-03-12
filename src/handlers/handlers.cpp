#include "handlers.h"

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

void getOperators(AsyncWebServer &server, std::vector<Operator> &operators) {
  server.on("/getOperators", HTTP_GET, [&operators](AsyncWebServerRequest *request){
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

void getOperatorById(AsyncWebServer &server, std::vector<Operator> &operators) {
    server.on("/getOperatorById", HTTP_GET, [&operators](AsyncWebServerRequest *request){

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
};

void postData(AsyncWebServer &server, std::vector<Operator> &operators) {
  server.on("/post-json-data", HTTP_POST, [](AsyncWebServerRequest *request) {
    Serial.println("POST Test...");
    }, NULL, [&operators](AsyncWebServerRequest *request, 
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
};

void deleteOperatorbyId(AsyncWebServer &server, std::vector<Operator> &operators) {
  server.on("/deleteOperatorbyId", HTTP_DELETE, [&operators](AsyncWebServerRequest *request){

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
};

void updateOperatorById(AsyncWebServer &server, std::vector<Operator> &operators) {
    server.on("/updateOperatorById", HTTP_PUT, [](AsyncWebServerRequest *request){
        Serial.println("Update Method");
        }, NULL, [&operators](AsyncWebServerRequest *request, 
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
};