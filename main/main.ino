#include <WiFi.h>


#include "Flex.h"
WiFiClient client;

#include "Esp32.h"
#include "BaseN.h"

Flex *flex;
BaseN *neck;

float resis;
unsigned long timer;

void setup() {
  Serial.begin(115200);
  //pinMode(4, INPUT);
  flex = new Flex(32, 10000, 10000, 20000);
  neck= new BaseN();
  neck->addSensor(flex);
  init_BLE_client();
  //Serial.println(analogRead(4));
}


void loop() {
  //resis=flex->readAngleData();
  //Serial.println("Resistance: " +String(resis)+ " ohms");
  //delay(125);
  neck->transmitBLE();
}

