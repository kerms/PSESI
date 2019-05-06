/*************************************************************************************************
This class will serve to create the main programm for the neck. We need to appeal to each sensor we 
need in this position. 
*************************************************************************************************/

#ifndef DEF_BASEC
#define DEF_BASEC

#include "esp32.h"
#include "tilt.h"
#include "flex.h"

#define MAX_WAIT_FOR_TIMER 2 // 1 timer to read data every period_1, a timer to save those on sd card, an other for WIFI
#define BUFF_WEIGHT 100
#define DataTimer	0
#define SDTimer		1
#define WifiTimer	2
#define BLETimer	3
#define DataPeriod 	100 	// in microseconds
#define SDPeriod	1000 	// Depends on the time we need to write on SD card
#define WifiPeriod	100000 	// Huge amount because we wont use it all the time
#define BLEPeriod	10000	// Same

struct sensorsData{ //Struc to store Data
	float flexDatum;
	int	tiltDatum;
} sensorsData;

class BaseC : public esp32 {

private:
	Tilt* tilt;
	Flex* flex;
	sensorsData sData;
	sensorsData* buff; //Temporary buffer to store data until it goes on SD card
	int cpt;


public:

	BaseN :: BaseN(Tilt* tilt, Flex* flex) : this.tilt(tilt), this.flex(flex)
	{
		this.buff=new sensorsData[BUFF_WEIGHT];
		this.cpt=0;
	}

	void readData(){
		if (!waitFor(DataTimer, DataPeriod)) return;
		tilt.readData(&(sData->tiltDatum));
		flex.readAngleData(&(sData->flexDatum));
		buff[cpt]=sData;
		cpt++;

	}

	void transmitSD(){
		if (!waitFor(SDTimer, SDPeriod)) return;
	}

	void transmitWifi(){
		if (!waitFor(WifiTimer, WifiPeriod)) return;
	}
	
	void transmitBLE(){
		if (!waitFor(BLETimer, BLEPeriod)) return;
	}
	

};

#endif