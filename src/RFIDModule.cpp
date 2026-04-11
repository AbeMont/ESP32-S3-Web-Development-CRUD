#include "RFIDModule.h"

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
  SPI.begin(this->SCK_PIN, this->MISO_PIN, this->MOSI_PIN, this->SS_PIN);
  this->mfrc522.PCD_Init();
  delay(50);

  this->mfrc522.PCD_DumpVersionToSerial();
  Serial.println("Scan PICC...");
}

bool RFIDModule::newCardPresent() {
    return this->mfrc522.PICC_IsNewCardPresent();
}

bool RFIDModule::readCard() {
    return this->mfrc522.PICC_ReadCardSerial();
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
    rfidEvent.onConnect([&rfid](AsyncEventSourceClient *client){
    // reconnect a client if they were asleep/inactive
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
      // Maybe don't need use of this method in the future
      rfid.SPIBegin();
    }
    // send event with message "RFID READY...", id current millis
    // and set reconnect delay to 1 second
    client->send("RFID READY....", NULL, millis(), 10000);
  });
}

void RFIDModule::rfidHandler(RFIDModule& rfid, AsyncEventSource& rfidEvent, bool& loggedState) {
    if(!rfid.newCardPresent()) return;
    if(!rfid.readCard()) return;

    Serial.println(rfid.getUID());
    String uid = rfid.getUID();
    rfidEvent.send(uid.c_str(), "rfidUID");
}

RFIDModule::~RFIDModule() {
}