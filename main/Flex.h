/*********************************************************************************************
A class for the flex sensor in a voltage divider circuit where the flex is connected between
your pin and the ground and the divider resistor makes the link between VCC (usually 3.3 V)
and your pin. 

*********************************************************************************************/
#ifndef DEF_FLEX
#define DEF_FLEX

#include "sensor.h"



class Flex : public Sensor{


private:
	int 	pin;
	float 	DivResistor; 		// Divider circuit's resistor
	float 	StraightResistance; // Flex straight resistance. Use the one you measure to avoid disparty values
	float	BendResistance; 	// Flex bend resistance
	float 	buf[]; //TODOOOOOOOO
	int 	size;				// Buf size
	int 	bufPos;				// Buf position


public:
	Flex::Flex(int pin, float DivResistor, float StraightResistance, float BendResistance, int size=500){
		this.pin=pin;
		this.DivResistor=DivResistor;
		this.StraightResistance=StraightResistance;
		this.BendResistance=BendResistance;
		this.buf= new buf[size];
	}

	
	float readResData(){
		int ADC_pin= analogRead(pin); // Read the ADC value of the pin chosen (between 0 to 4095)
		if(ADC_pin<1000 or ADC_pin>3500) return -1; // ADC value does not match with expectations : Mostly pin issue or misconnections
		float Volt_pin = ADC_pin*VCC/4095.0; // Cross-multiplication for Volt_pin
		return DivResistor*(1/( (VCC / Volt_pin ) -1.0)) ; // Using divider circuit's formula
	}

	float readAngleData(){ //Convert resistance to angle through mapping
		float resistance;
		float angle;
		resistance= readResData();
		if(resistance<1000 or resistance>3500) return -1;
		return map(resistor, StraightResistance, BendResistance, 0 ,90.0);
	}

	// TODOOOOOOO
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

	int getType(){
		return type;
	}

	void setup(){ 	// To setup Flex's pin
		pinMode(pin,INPUT);
	}

	void saveData();

	std::string toString(){
		std::string s="";
		s+=readAngleData();
		return s;
	}



};

#endif