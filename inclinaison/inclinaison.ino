/******************************************************************************
Flex_Sensor_Example.ino
Example sketch for SparkFun's flex sensors
  (https://www.sparkfun.com/products/10264)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining a flex sensor with a 47k resistor.
- The resistor should connect from A0 to GND.
- The flex sensor should connect from A0 to 3.3V
As the resistance of the flex sensor increases (meaning it's being bent), the
voltage at A0 should decrease.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int TILT_PIN = 4; 
//Le capteur d'inclinaison se comporte sois en circuit fermé ( à la verticale)
//ou en circuit ouvert( pour une inclinaison de 45°). On interprete ça selon 0 ou 1


void setup() 
{
  Serial.begin(9600);
  pinMode(TILT_PIN, INPUT);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  int TiltADC = digitalRead(TILT_PIN); // Donerra 0 ou 1 selon si on détecte 3,3 V ou non
  Serial.println(String(TiltADC));
  delay(500);
}
