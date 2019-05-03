/*********************************************************************************************
A class for the tilt sensor. It acts as a switch letting flow the current when the tilt
sensor is straight an cutting it when it's approximataly around 45°. We insert this sensor
between VCC and the pin and a  resistance between the pin and GND. 
When the switch is closed we have the pin cnnected to VCC which is high. We read 1 as 
digital value. Otherwise when the switch is open, the pin is connected to GND and digital
value become 0.
*********************************************************************************************/

#ifndef DEF_FLEX
#define DEF_FLEX

#include "sensor.h"



class Tilt : public sensor{


private:
	int 	pin;

public:
	Tilt::Tilt(int pin) : pin(pin)
	{

	}

	bool readData(void* buff){
		*buff=digitalRead(this.pin); // Give 1 if we have 3.3V, else 0
		if( *buff!=0 || *buff!=1 ) return 0; 
		return 1; 
	}

	static bool readData(void* buff, int pin){ // Static method for resistance
		*buff=digitalRead(pin);
		if( *buff!=0 || *buff!=1 ) return 0; 
		return 1; 
	}

	void setPin(int pin){
		this.pin=pin;
	}

	int getPin(){
		return pin;
	}

	void setup(){ 	// To setup tilt's pin
		pinMode(pin,INPUT);
	}



};

#endif