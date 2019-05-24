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

 // 1 timer to read data every period_1, a timer to save those on sd card, an other for WIFI
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

#include <SPI.h>			// For SD card module
#include <SD.h>				// For SD card

extern WiFiClient client;

class BaseN : public Esp32 {

private:
	Sensor* tilt;
	Sensor* flex;


public:

	BaseN(Sensor* tilt=NULL, Sensor* flex=NULL)
	{
		wifi_connect(SESI_SSID, SESS_PASS, -1);
		wifi_connect_server(SESI_IPv4, SESI_PORT);
		this->tilt = tilt;
		this->flex = flex;

	}

	std::string readData(){
		if (!waitFor(DataTimer, DataPeriod)) return "";
		//tilt.toString();
		return flex->toString();
	}

	void setup_SD(int pin){
		SD.begin(pin); //Pin
		Serial.print("Initializing SD card...");
		if(!SD.begin(pin)) {
    		Serial.println("initialization failed!");
    		return;
  		}
  		Serial.println("initialization done.");
	}

	void transmitToSD(String file,float *buf){
		//if (!waitFor(SDTimer, SDPeriod)) return;
		dataFile = SD.open(file, FILE_WRITE); // FILE_WRITE : to write and read in this file
		if(dataFile){
			Serial.println("File opened ok");
			for
			dataFile.println(buf)
		}

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