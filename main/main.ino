#include <WiFi.h>


#include "Flex.h"
WiFiClient client;

#include "BaseN.h"


Flex *flex = new Flex(4, 10000, 10000, 20000);
BaseN *neck= new BaseN();

float resis;


void setup() {
  Serial.begin(115200);
  neck->addSensor(flex);
  init_BLE_client();
}

void loop() {
  //resis=flex->readAngleData();
  //Serial.println("Resistance: " +String(resis)+ " ohms");
  //delay(125);
  neck->transmitBLE();
}

