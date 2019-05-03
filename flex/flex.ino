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
const int FLEX_PIN = 4; // Pin connected to voltage divider output


//POUR AMELIORER :
// Measure the voltage at your pin and the actual resistance of your
// choice you want to use, and enter them below:
const float VCC = 3.3; // Measured voltage of Ardunio 5V line
const float R_DIV = 10000.0; // Measured resistance you choose

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 10000.; // resistance when straight 4' : 10 kOhms _ 2'2 : 25 kOhms
const float BEND_RESISTANCE = 20000.0; // resistance at 90 deg     4' : 20 kOhms _ 2'2 : 50 kOhms

void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  Serial.println(String(flexADC));
  float flexV = flexADC * VCC / 4095.0; // Produit en croix pour obtenir la valeur en Volt au pin choisi sachant que pour 3.3V on a une val au pin de 4095
  float flexR = R_DIV * ( 1/((VCC / flexV) - 1.0)); // Exploitation du diviseur de tension pour obetenir la valeur de resistance du flex sensor " flexV = Vcc*flexR / (flexR + R_DIV) " 
  Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0); // Remappe la valeur de la resistance allant d'une valeur à une autre ( Straigth to Bend ) sur celle d'une valeur d'angle ( 0 à 90 °)
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();

  delay(500);
}
