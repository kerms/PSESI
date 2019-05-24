#ifndef DEF_BASEP
#define DEF_BASEP

#include "Esp32.h"
#include "wifi_client.h"
#include <SPI.h>			// For SD card module
#include <SD.h>				// For SD card


class baseC : public esp32
{
private:


public :

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
			for(int i=0; i<250; i++){
				dataFile.println(buf[i]);
			}
			dataFile.close();
		}
	}

	

	void transmitWifi(){
		if (!waitFor(WifiTimer, WifiPeriod)) return;
		client.print(readData().c_str());
	}


};

#endif