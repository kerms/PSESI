#ifndef DEF_SENSOR
#define DEF_SENSOR

#define POS_UNKNOWN 0   // Define differents positions for your sensors
#define POS_NECK    1
#define POS_WRIST   2
#define POS_EAR     3

#define TYPE_UNKNOWN 	0
#define TYPE_FLEX	 	1
#define TYPE_TILT		2
#define TYPE_ACC_GYRO	3

#import <Arduino.h>
#include "Fifo.h"
#include <string>

class Sensor
{
protected:
	int 	idposition = 0;
	float 	VCC = 0;
	int 	type_sensor = 0;
	Fifo	fifo;

public:

	Sensor(unsigned int idposition=POS_UNKNOWN, float VCC=3.3, 
		unsigned int type_sensor=TYPE_UNKNOWN)
		: idposition(idposition), VCC(VCC), type_sensor(type_sensor), fifo()
	{
	}
	
	virtual ~Sensor(){}

	virtual void saveData()=0;

	virtual int getType()=0;

	virtual int getData(void * buff)=0;

	virtual std::string toString()=0;

	Fifo getFifo(){
		return fifo;
	}

	
};


#endif 