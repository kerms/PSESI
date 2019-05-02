/*********************************************************************************************
A class for the flex sensor in a voltage divider circuit where the flex is connected between
your pin and the ground and the divider resistor makes the link between VCC (usually 3.3 V)
and your pin. 

*********************************************************************************************/
#ifndef DEF_FLEX
#define DEF_FLEX

#include "sensor.h"



class Flex : public sensor{


private:
	int 	pin;
	float 	DivResistor; 		// Divider circuit's resistor
	float 	StraightResistance; // Flex straight resistance. Use the one you measure to avoid disparty values
	float	BendResistance; 	// Flex bend resistance


public:
	Flex::Flex(int pin, float DivResistor, float StraightResistance, float BendResistance){
		this.pin=pin;
		this.DivResistor=DivResistor;
		this.StraightResistance=StraightResistance;
		this.BendResistance=BendResistance;
	}

	
	bool readResData(void* buff){
		int ADC_pin= analogRead(pin); // Read the ADC value of the pin chosen (between 0 to 4095)
		if(ADC_pin<1000 or ADC_pin>3500) return 0; // ADC value does not match with expectations : Mostly pin issue or misconnections
		float Volt_pin = ADC_pin*VCC/4095.0; // Cross-multiplication for Volt_pin
		*buff=DivResistor*(1/( (VCC / Volt_pin ) -1.0)) ; // Using divider circuit's formula
		return 1
	}

	bool readAngleData(void* buff){ //Convert resistance to angle through mapping
		float* resistance;
		readResData(resistance);
		if(resistance<1000 or resistance>3500) return 0;
		*buff=map(resistor, StraightResistance, BendResistance, 0 ,90.0);
		return 1;
	}

	static bool readData(void* buff, int pin, float DivResistor){ // Static method for resistance
		int ADC_pin= analogRead(pin);
		if(ADC_pin<1000 or ADC_pin>3500) return 0; 
		float Volt_pin = ADC_pin*VCC/4095.0;
		*buff=DivResistor*(1/( (VCC / Volt_pin ) -1.0));
		return 1;
	}

	void setPin(int pin){
		this.pin=pin;
	}

	int getPin(){
		return pin;
	}

	void setDivResistor(float resistance){
		this.resistor=resistor;
	}

	float getDivResistor(){
		return resistor;
	}

	void setStraightResistance(float resistance){
		this.StraightResistance=resistance;
	}

	float getStraightResistance(){
		return StraightResistance;
	}

	void setBendResistance(float resistance){
		this.BendResistance=resistance;
	}

	float getBendResistance(){
		return BendResistance;
	}

	void setup(){ 	// To setup Flex's pin
		pinMode(pin,INPUT);
	}


};

#endif