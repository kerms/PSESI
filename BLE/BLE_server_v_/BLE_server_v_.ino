/**
 * A BLE client example that is rich in capabilities.
 * There is a lot new capabilities implemented.
 * author unknown
 * updated by chegewara
 */

#include <Arduino.h>
#include "SODI_BLE_Server.h"

#define bleServerName "ESP32_server"
long randNumber;
char val[50];
int SD_PIN = 32; // TODO
int SD_OK = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  init_BLE_server(); 
  advertise ();//creation des charac et associer les droits
  /*
  if(!SD.begin()) {
    Serial.println("initialization failed!");
  }
  SD_OK = 1;
  */
} // End of setup.


// This is the Arduino main loop function.
void loop() {
  if (connected)
  {
    /*Serial.printf ("Mise à jour valeur des capteurs dans les characteristics\n");
    for (int i = 0; i < NB_CHAR; ++i)
    {
      randNumber = random(300);
      snprintf (val, 75, "%d",randNumber);
      Serial.println(val);
      pCharacteristic[i]->setValue(val);
      pCharacteristic[i]->notify();
     
    }*/
//c'est plutot le client du coup qui lui envoie ces données. censer recevoir les données 

     
   
    delay(2000);
  }
}
