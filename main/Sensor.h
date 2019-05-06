#ifndef DEF_SENSOR
#define DEF_SENSOR
#define POS_UNKNOWN 0   // Define differents positions for your sensors
#define POS_NECK    1
#define POS_WRIST   2
#define POS_EAR     3




class Sensor{

protected:
	int idposition;
	float VCC;
	int type;


public:
	virtual void saveData()=0;
	virtual int getType()=0;
	virtual std::string toString()=0;

};


#endif 