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

RFIDModule::~RFIDModule() {
}