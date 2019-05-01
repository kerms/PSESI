#ifndef DEF_SENSOR
#define DEF_SENSOR
#define POS_UNKNOWN 0 
#define POS_NECK    1
#define POS_WRIST   2
#define POS_EAR     3



class sensor{

protected:
	int idposition; 

public:
	virtual bool readData(void* buff)=0;


};


#endif 