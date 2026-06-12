#include "RFIDModule.h"
#include "views/mainMenu.h"

RFIDModule::RFIDModule(            
    uint8_t ssPin, 
    uint8_t sckPin, 
    uint8_t mosiPin, 
    uint8_t miso_Pin,
    uint8_t rstPin) :
    mfrc522(ssPin, rstPin) 
{
    this->SS_PIN = ssPin;
    this->SCK_PIN = sckPin;
    this->MOSI_PIN = mosiPin;
    this->MISO_PIN = miso_Pin;
    this->RST_PIN = rstPin;
}

void RFIDModule::SPIBegin() {
    // sck, miso, mosi, ss
    // The <SPI.h> module is coming from <MFRC522.h>
    SPI.begin(this->SCK_PIN, this->MISO_PIN, this->MOSI_PIN, this->SS_PIN);
    this->mfrc522.PCD_Init();
    delay(50);

    this->mfrc522.PCD_DumpVersionToSerial();
    Serial.println("Scan PICC...");
}

bool RFIDModule::readCard() {
    return this->mfrc522.PICC_ReadCardSerial();
}

bool RFIDModule::newCardPresent() {
    return this->mfrc522.PICC_IsNewCardPresent();
}

String RFIDModule::getUID() {
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) uid += "0";
        uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();
    return uid;
}

void RFIDModule::rfidAsyncConnect(RFIDModule& rfid, AsyncEventSource& rfidEvent) {
    rfidEvent.onConnect([&rfid](AsyncEventSourceClient* client){
    // reconnect a client if they were asleep/inactive
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
      // Maybe don't need use of this method in the future
      rfid.SPIBegin();
    }
    // send event with message "RFID READY...", id current millis
    // and set reconnect delay to 1 second
    client->send("RFID Async Custom Events Ready....", NULL, millis(), 10000);
  });
}

void RFIDModule::rfidReadyToRead(AsyncWebServer& server, bool& rfidReady, bool& loggedState) {
    server.on("/rfid-ready-to-read", HTTP_POST, [](AsyncWebServerRequest *request) {
    }, NULL, [&rfidReady, &loggedState](AsyncWebServerRequest *request, 
        uint8_t *data, 
        size_t len, 
        size_t index, 
        size_t total) {

            String body = "";
            for (size_t i = 0; i < len; i++) {
                body += (char)data[i];
            }

            Serial.println("Received body: " + body);

            if (body == "true") {
                rfidReady = true;
                neopixelWrite(RGB_BUILTIN, 60, 30, 0);
                request->send(200, "text/plain", "Awaiting Card Input...");
            } else if (body == "false") {
                rfidReady = false;
                loggedState = false;
                neopixelWrite(RGB_BUILTIN, 30, 0, 0);
                request->send(200, "text/plain", "Card reader Inactive");
            } else {
                request->send(400, "text/plain", "Invalid body");
            }
        });
}

void RFIDModule::rfidHandler(RFIDModule& rfid, AsyncEventSource& rfidEvent, bool& loggedState) {
    if(!rfid.newCardPresent()) return;
    if(!rfid.readCard()) return;

    Serial.println(rfid.getUID());
    String uid = rfid.getUID();

    if ((uid == "593A5207" || uid == "0443464AD21D90") && loggedState == false) {
        loggedState = true;

        // send response with data client-side, 
        // remember we created 'loadLoggedIn' & 'loadLoggedIn' in customEvents.js
        rfidEvent.send(uid.c_str(), "rfidUID");
        rfidEvent.send(mainMenu, "loadLoggedIn");

        // Update LED color to Green
        neopixelWrite(RGB_BUILTIN, 0, 30, 0);
    }
    
}

RFIDModule::~RFIDModule() {
}