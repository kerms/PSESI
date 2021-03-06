/**
 * A BLE client example that is rich in capabilities.
 * There is a lot new capabilities implemented.
 * author unknown
 * updated by chegewara
 */

#include "SODI_BLE_Client.h"

#define bleServerName "ESP32_server"


void setup() {
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  init_BLE_client();
}

// This is the Arduino main loop function.
void loop() {
  if (BLE_connect()){
    Serial.print("connect ok");
  }

  for (int i = 0; i < NB_CHAR; ++i)
  {
    BLE_write(i, "hey");
  }
  //censer envoyer les données
  
  delay(1000);
}
