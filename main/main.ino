#include <WiFi.h>

#include "Flex.h"
WiFiClient client;

#include "BaseN.h"


Flex *flex = new Flex(4, 10000, 10000, 20000);
BaseN *neck= new BaseN(NULL, (Sensor *)flex);

float resis;


void setup() {
  Serial.begin(115200);
}

void loop() {
  resis=flex->readAngleData();
  Serial.println("Resistance: " +String(resis)+ " ohms");
  //neck.transmitWifi();
}
