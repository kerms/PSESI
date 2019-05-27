/*************************************************************************************************
This class will serve to create the main programm for the neck. We need to appeal to each sensor we 
need in this position. 
*************************************************************************************************/

#ifndef DEF_BASEC
#define DEF_BASEC

#include "Esp32.h"
#include "Tilt.h"
#include "Flex.h"
#include "wifi_client.h"


#define SERVICE 3; 

extern WiFiClient client;

class BaseN : public Esp32 {

private:
	//List of sensors
	Sensor*		sensors[10];
	int			cntr_sensors=0;

	//Sensor's cntr Type
	int cntr_flex=0;
	int cntr_tilt=0;
	int cntr_acc_gyro=0;


public:

	BaseN()
	{
		wifi_connect(SESI_SSID, SESS_PASS, -1);
		wifi_connect_server(SESI_IPv4, SESI_PORT);

	}

	void addSensor(Sensor* sensor){
		sensors[cntr_sensors]=sensor;
		switch (sensor->getType()){
			case 1 : 
				cntr_flex++;
				break;
			case 2 :
				cntr_tilt++;
				break;
			case 3 :
				cntr_acc_gyro++;
				break;
			default :
				break;
		}

		cntr_sensors++;
	}

	//Communication WIFI and BLE
	void transmitWifi(){
		//if (!waitFor(WifiTimer, WifiPeriod)) return;
		//client.print(readData().c_str());
	}
	
	void transmitBLE( ){
		int service= SERVICE;
		//if (!waitFor(BLETimer, BLEPeriod)) return;
	}
	//End Communicaiton


	std::string toString(){ 
		std::string s="";
		for(int i=0; i<cntr_sensors; i++){
			s+=sensors[i]->toString()+"\n";
		}
		return s;
	}

};

#endif