/*********************************************************************************************
A class for the flex sensor in a voltage divider circuit where the flex is connected between
VCC (usually 3.3 V) and the chosen pin. The divider resistor makes the link between the pin 
and GND(ground). 

*********************************************************************************************/
#ifndef DEF_FLEX
#define DEF_FLEX

#include "Sensor.h"



class Flex : public Sensor{


private:
	//Features
	int 		pin;
	float 		DivResistor; 		// Divider circuit's resistor
	float 		StraightResistance; // Flex straight resistance. Use the one you measure to avoid disparty values
	float		BendResistance; 	// Flex bend resistance

	//Identification of the object
	int 		id;					// Flex ID
	static int 	id_cntr=0;



public:
	Flex(int pin, float DivResistor, float StraightResistance, float BendResistance, int position=0)
		:Sensor(int position, 3.3, 1)
	{
		this->pin 					= pin;
		this->DivResistor 			= DivResistor;
		this->StraightResistance 	= StraightResistance;
		this->BendResistance 		= BendResistance;
		this->id 					= id_cntr;
		this->id_cntr++;
		pinMode(pin,INPUT);
	}

	virtual ~Flex(){
		delete [] fifo;
	}

	
	float readResData(){
		int ADC_pin= analogRead(pin); // Read the ADC value of the pin chosen (between 0 to 4095)
		if(ADC_pin<1000 or ADC_pin>3500) return -1; // ADC value does not match with expectations : Mostly pin issue or misconnections
		float Volt_pin = ADC_pin*VCC/4095.0; // Cross-multiplication for Volt_pin
		return DivResistor*( (VCC/Volt_pin) -1.0) ; // Using divider circuit's formula
	}

	float readAngleData(){ //Convert resistance to angle through mapping
		float resistance;
		float angle;
		resistance= readResData();
		if(resistance<1000 or resistance>3500) return -1;
		return map(resistance, StraightResistance, BendResistance, 0 ,90.0);
	}


	static float readData(int pin, float DivResistor,float StraightResistance, 
		float BendResistance, int VCC=0)
	{ // Static method for resistance
		int ADC_pin= analogRead(pin);
		if(ADC_pin<1000 or ADC_pin>3500) return -1; 
		float Volt_pin = ADC_pin*VCC/4095.0;
		float resistance = DivResistor*( (VCC / Volt_pin ) -1.0);
		return map(resistance, StraightResistance, BendResistance, 0 ,90.0);
	}

	void setPin(int pin){
		this->pin=pin;
	}

	int getPin(){
		return pin;
	}

	void setDivResistor(float resistance){
		this->DivResistor=resistance;
	}

	float getDivResistor(){
		return DivResistor;
	}

	void setStraightResistance(float resistance){
		this->StraightResistance=resistance;
	}

	float getStraightResistance(){
		return StraightResistance;
	}

	void setBendResistance(float resistance){
		this->BendResistance=resistance;
	}

	float getBendResistance(){
		return BendResistance;
	}

	int getType() {
		return TYPE_FLEX;
	}

	static int getNb(){  //Return the number of Flex created
		return id_cntr;
	}

	int getId(){
		return id;
	}

	void saveData() {
		fifo.writeBufr(readAngleData());
	}


	std::string toString(){
		std::string s="";
		s+=readAngleData();
		return s;
	}

	std::string IDtoString(){
		std::string s=getType()+"_"+getId();
	}



};

#endif