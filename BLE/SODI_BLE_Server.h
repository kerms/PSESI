/*Normalement situé à la base P, stocke les valeurs du client*/
#ifndef __BLE_SODI_SERVER_H__
#define __BLE_SODI_SERVER_H__
#include <Arduino.h>
#include "SODI_BLE.h"

extern boolean connected;
extern BLECharacteristic *pCharacteristic[NB_CHAR];
extern BLEService *pService;
extern BLEServer *pServer;
//static uint16_t mtu;
//static uint16_t mtu1;

//static esp_err_t set;
//#define bleServerName "ESP32_server"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pserver) {
    connected = true;
    Serial.println("onConnect");
  }

  void onDisconnect(BLEServer* pserver) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

class MyBLEChar : public BLECharacteristicCallbacks 
{
    virtual void onRead(BLECharacteristic* pCharacteristic)
    {

    }

    virtual void onWrite(BLECharacteristic* pCharacteristic)
    {
        Serial.print("data of: ");
        Serial.print(pCharacteristic->getUUID().toString().c_str()); //which char. are we reading
        Serial.print(", value : ");
        Serial.println(pCharacteristic->getValue().c_str());

    }
};

void init_BLE_server() 
{
  /*Serial.println("MTU lenght :");
  mtu = BLEDevice::getMTU ();
  Serial.println(mtu);
  set=BLEDevice::setMTU (500);
  mtu1 = BLEDevice::getMTU ();
  Serial.println(mtu1);*/

  

  BLEDevice::init("ESP_server"); //donner un nom à notre server
  pServer = BLEDevice::createServer();
  Serial.println("Server created!");
  pServer->setCallbacks(new MyServerCallbacks());
  pService = pServer->createService(servUUID, 10);  // cree un service 
  Serial.println("Service created!");

	//Serial.println("Debug");
	for (int i = 0; i < NB_CHAR; ++i)
    {
    	pCharacteristic[i]= pService->createCharacteristic(charUUID[i],
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
    }

    Serial.println("Characteristics flags defined!");
}


void advertise () //Creer et specifier les flags et les characteristics
{
	//set_charac ();
	pService->start();
	Serial.println("Service started!");
  	BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  	//BLEAdvertising *pAdvertising = BLEDevice::getAdvertising(); // creation de l'advertiser
  	/* INITIALISATION DE L'ADVERTISER*/
  	pAdvertising->addServiceUUID(servUUID); 
  	pAdvertising->setScanResponse(true);
  	pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  	pAdvertising->setMinPreferred(0x12);
  	BLEDevice::startAdvertising(); // Activation pour dire que "Hey je suis là"
  	Serial.println("Characteristic defined! Now you can read data in ESP client!");

    pCharacteristic[0]->setCallbacks(new MyBLEChar());
}


#endif