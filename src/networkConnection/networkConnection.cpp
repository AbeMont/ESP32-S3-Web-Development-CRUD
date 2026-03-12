#include "networkConnection.h"

void connectToNetwork() {
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
}

void printNetworkInit(int serverPort) {
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