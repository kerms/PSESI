/*************************************************************************************************
This class will serve to create the main programm for the neck. We need to appeal to each sensor we 
need in this position. 
*************************************************************************************************/

#ifndef DEF_BASEC
#define DEF_BASEC

#include "esp32.h"
#include "tilt.h"
#include "flex.h"
#include "wifi_client.h"

#define MAX_WAIT_FOR_TIMER 2 // 1 timer to read data every period_1, a timer to save those on sd card, an other for WIFI
#define BUFF_WEIGHT 100
#define DataTimer	0
#define SDTimer		1
#define WifiTimer	2
#define BLETimer	3
#define DataPeriod 	100 	// in microseconds
#define SDPeriod	1000 	// Depends on the time we need to write on SD card
//#define WifiPeriod	100000 	// Huge amount because we wont use it all the time
#define WifiPeriod	1000 	// Huge amount because we wont use it all the time
#define BLEPeriod	10000	// Same

extern WiFiClient client;

class BaseN : public esp32 {

private:
	Sensor* tilt;
	Sensor* flex;


public:

	BaseN :: BaseN(Sensor* tilt=NULL, Sensor* flex=NULL) : this.tilt(tilt), this.flex(flex)
	{
		wifi_connect(SESI_SSID, SESS_PASS, -1);
		wifi_connect_server(SESI_IPv4, SESI_PORT);

	}

	std::string readData(){
		if (!waitFor(DataTimer, DataPeriod)) return;
		//tilt.toString();
		return flex.toString();
	}

	void transmitSD(){
		if (!waitFor(SDTimer, SDPeriod)) return;
	}

	void transmitWifi(){
		if (!waitFor(WifiTimer, WifiPeriod)) return;
		client.print(readData().c_str());
	}
	
	void transmitBLE(){
		if (!waitFor(BLETimer, BLEPeriod)) return;
	}
	

};

#endif