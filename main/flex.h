#ifndef DEF_FLEX
#define DEF_FLEX

#include "sensor.h"


class flex : public sensor{


private:
	int pin;
	float resistor;


public:

	bool readData(void* buff){

	}

	static bool readData(void* buff, int pin){


	}

	void setPin(int pin){
		this.pin=pin;
	}

	int getPin(){
		return pin;
	}

	void setResistor(float resistor){
		this.resistor=resistor;
	}

	float getResistor(){
		return resistor;
	}




};

#endif