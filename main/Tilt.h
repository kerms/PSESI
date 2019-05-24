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

#include "Sensor.h"



class Tilt : public Sensor{


private:
	int 			pin;
	float 			*buf;
	int 			bufSize;			// Buf size
	int 			bufPos;				// Buf write position
	int 			id;					// TILT ID
	static int 		id_cpt;

public:
	Tilt(int pin, int buf_size, int position=0) : Sensor(position,0,2), pin(pin)
	{
		this->buf= new int[buf_size];
		this->bufSize = buf_size;
		this->bufPos = 0;
		pinMode(pin,INPUT);
	}

	~Tilt() {

	}

	int readData(){
		return digitalRead(this->pin); // Give 1 if we have 3.3V, else 0
	}

	static int readData(int pin){ // Static method for resistance
		return digitalRead(pin);
	}


	void setPin(int pin){
		this->pin=pin;
	}

	int getPin(){
		return pin;
	}

	float* getBuf(){
		return buf;
	}

	int getType() {
		return TYPE_TILT;
	}

	static int getNb(){
		return id_cpt;
	}

	int getID(){
		return id;
	}

	std::string toString(){
		std::string s="";
		s+=readData();
		return s;
	}



};

#endif