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
#include "SODI_BLE.h"
#include "SODI_BLE_Client.h"

#define NB_SENSOR 10

extern WiFiClient client;

class BaseN : public Esp32 {

private:
	//List of sensors
	Sensor*		sensors[NB_SENSOR];
	int			cntr_sensors=0;

	//Sensor's cntr Type
	int cntr_flex=0;
	int cntr_tilt=0;
	int cntr_acc_gyro=0;
	unsigned long SENSOR_TIMER[NB_SENSOR];
	unsigned long SENSOR_PERIOD[NB_SENSOR];
	unsigned long BLE_TIMER;


public:

	BaseN()
	{
		//wifi_connect(SESI_SSID, SESS_PASS, -1);
		//wifi_connect_server(SESI_IPv4, SESI_PORT);
		//init_BLE_client();
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
		SENSOR_PERIOD[cntr_sensors] = 100000; // every second
		cntr_sensors++;
	}

	//Communication WIFI and BLE
	void transmitWifi(){
		//if (!waitFor(WifiTimer, WifiPeriod)) return;
		//client.print(readData().c_str());
	}
	
	void transmitBLE( ){
		if (!waitFor(&BLE_TIMER, 1000000)) return; //every sec
		if ( !BLE_connect())
			return;
		float buff;
		//sensors[0]->getData(&buff);
		_remoteChar[0]->writeValue(sensors[0]->toString());
		Serial.print("value ");
		//Serial.print(sensors[0]->toString());
		Serial.println(" transmited ");
	}
	//End Communicaiton

	void saveData()
	{
		for(int i=0; i<cntr_sensors; i++){
			if (!waitFor(&SENSOR_TIMER[i], SENSOR_PERIOD[i])) continue;
			sensors[i]->saveData();
		}
	}

	std::string toString(){ 
		std::string s="";
		for(int i=0; i<cntr_sensors; i++){
			s+=sensors[i]->toString()+"\n";
		}
		return s;
	}

};

#endif