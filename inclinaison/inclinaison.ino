/******************************************************************************


******************************************************************************/
const int TILT_PIN = 4; 
//Le capteur d'inclinaison se comporte sois en circuit fermé ( à la verticale)
//ou en circuit ouvert( pour une inclinaison de 45°). On interprete ça selon 0 ou 1

int TiltADC =0;
int Tilt=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(TILT_PIN, INPUT);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  TiltADC = digitalRead(TILT_PIN); // Donerra 0 ou 1 selon si on détecte 3,3 V ou non
  Serial.println("Digital"+String(TiltADC));
  Tilt  = analogRead(TILT_PIN);
  
  Serial.println(String(Tilt));
  
  delay(500);
}
