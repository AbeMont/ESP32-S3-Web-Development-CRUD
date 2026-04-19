#ifndef RFIDMODULE_H_
#define RFIDMODULE_H_ 

#include <SPI.h>
#include <MFRC522.h>
#include <AsyncEventSource.h>

class RFIDModule {

    public:
        uint8_t SS_PIN; // SDA PIN
        uint8_t SCK_PIN;
        uint8_t MOSI_PIN;
        uint8_t MISO_PIN;
        uint8_t RST_PIN;
        MFRC522 mfrc522;

        RFIDModule(            
            uint8_t ssPin, 
            uint8_t sckPin, 
            uint8_t mosiPin, 
            uint8_t miso_Pin,
            uint8_t rstPin
        );

        void SPIBegin();
        virtual bool readCard();
        virtual bool newCardPresent();
        String getUID();
        void rfidAsyncConnect(RFIDModule& rfid, AsyncEventSource& rfidEvent);
        void rfidHandler(RFIDModule& rfid, AsyncEventSource& rfidEvent, bool& loggedState);
        void rfidReadyToRead(AsyncWebServer &server, bool& rfidReady, bool& loggedState);

        ~RFIDModule();

    private:

};

#endif