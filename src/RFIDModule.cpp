#include "RFIDModule.h"

RFIDModule::RFIDModule(            
    uint8_t ssPin, 
    uint8_t sckPin, 
    uint8_t mosiPin, 
    uint8_t miso_Pin,
    uint8_t rstPin) : 
    SS_PIN(ssPin),
    SCK_PIN(sckPin),
    MOSI_PIN(mosiPin),
    MISO_PIN(miso_Pin),
    RST_PIN(rstPin),
    mfrc522(ssPin, rstPin)   // ✅ THIS is the important fix
{
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

RFIDModule::~RFIDModule() {
}