#include "handlers.h"
#include <RFIDModule.h>

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

Operator* getOperatorbyId(std::vector<Operator> &operators, int targetId) {
    auto it = std::find_if(operators.begin(), operators.end(), [targetId](const Operator& obj) {
        return obj.id == targetId;
    });
    // Check if a matching object was found
    // Return the pointer (Operator*) -> &(*it) to the found object
    // Why not just return -- it -- instead of &(*it)? Thats because
    // it is an iterator type, not the Operator* pointer the function
    // expects to return
    // Return nullptr if not found
    return it != operators.end() ? &(*it) : nullptr;
}

void deleteOperatorById(std::vector<Operator> &operators, int targetId) {
    // std::remove_if shifts elements to be kept to the front and returns an iterator 
    // to the new logical end of the remaining elements.
    auto it = std::remove_if(operators.begin(), operators.end(), [targetId](const Operator& obj) { 
        return obj.id == targetId; 
    });

    // vector::erase then removes the elements from the new logical end to the actual end.
    operators.erase(it, operators.end());
}

Operator* updateOperatorById(std::vector<Operator> &operators, 
    int targetId, 
    String updatedName,
    String updatedWeapon,
    String updatedMetalgear) {
    // Use reference (&)in &obj to modify the actual object in the vector
    auto operatorObj = std::find_if(operators.begin(), operators.end(), [targetId](const Operator& obj){
        return obj.id == targetId;
    });

    if (operatorObj != operators.end()) {
        operatorObj->name = updatedName;
        operatorObj->weapon = updatedWeapon;
        operatorObj->metalGear = updatedMetalgear;
        // Return the pointer (Operator*) to the updated object
        return &(*operatorObj);
    } else {
        return nullptr;
    }
}

void getOperatorsHandler(AsyncWebServer &server, std::vector<Operator> &operators) {
  server.on("/getOperators", HTTP_GET, [&operators](AsyncWebServerRequest *request){
    // As the operators vector grows, this value needs to get bigger
    StaticJsonDocument<640> operatorsDoc;
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
    Serial.println(jsonResponse);
    request->send(200, "application/json",jsonResponse);
  });
}

void getOperatorByIdHandler(AsyncWebServer &server, std::vector<Operator> &operators) {
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

void postDataHandler(AsyncWebServer &server, std::vector<Operator> &operators) {
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

void deleteOperatorbyIdHandler(AsyncWebServer &server, std::vector<Operator> &operators) {
  server.on("/deleteOperatorbyId", HTTP_DELETE, [&operators](AsyncWebServerRequest *request){

    if (request->hasParam("id")) {

      String operatorIdParam = request->getParam("id")->value();
      // converts string to int
      int id = atoi(operatorIdParam.c_str());

      // Remove Operator By Id
      deleteOperatorById(operators,id);

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

void updateOperatorByIdHandler(AsyncWebServer &server, std::vector<Operator> &operators) {
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

void rfidHandler(RFIDModule& rfid, AsyncEventSource& rfidEvent) {
  if(!rfid.newCardPresent()) return;
  if(!rfid.readCard()) return;

  Serial.println(rfid.getUID());
  String uid = rfid.getUID();
  rfidEvent.send(uid.c_str(), "rfidUID");
  delay(150);
}