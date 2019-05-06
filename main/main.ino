#include "BaseN.h"

Flex *flex=new flex(4, 10000, 10000, 20000);
BaseN neck= new BaseN(NULL, flex);

float resis;

void setup() {
  Serial.begin(115200);
  flex.setup();
}

void loop() {
  resis=flex.readAngleData();
  Serial.println("Resistance: " +String(resis)+ " ohms");
  neck.transmitWifi();
}
