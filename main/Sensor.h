#ifndef DEF_SENSOR
#define DEF_SENSOR
#define POS_UNKNOWN 0   // Define differents positions for your sensors
#define POS_NECK    1
#define POS_WRIST   2
#define POS_EAR     3
#define VCC			3.3 // VCC value given by ESP32. You need to measure it and make the real value here




class Sensor{

protected:
	int idposition;
	float VCC;

public:
	virtual bool readData(void* buff)=0;

};


#endif 