#ifndef __BLE_SODI_CLIENT_H__
#define __BLE_SODI_CLIENT_H__

#include <Arduino.h>
#include "SODI_BLE.h"

//extern SODI_BLE_Client BLE_client;
extern boolean _connected;
extern boolean _scan_found;
extern BLERemoteCharacteristic * _remoteChar[NB_CHAR];
extern BLEAddress* _myDevice;
extern BLEScan* _pBLEScan;

class MyClientCallback : public BLEClientCallbacks {
    void onConnect(BLEClient* pclient) {
    }

    void onDisconnect(BLEClient* pclient) {
        _connected = false;
        Serial.println("onDisconnect");
    }
};

/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
 /**
   * Called for each advertising BLE server.
   */
    void onResult(BLEAdvertisedDevice advertisedDevice) {

    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

        // We have found a device, let us now see if it contains the service we are looking for.
        if (advertisedDevice.haveServiceUUID() &&
            //advertisedDevice.getName() == bleServerName &&
            advertisedDevice.getServiceUUID().equals(servUUID)) {

            _pBLEScan->stop();
            if(_myDevice)
                delete _myDevice;
            _myDevice = new BLEAddress(advertisedDevice.getAddress());
            _scan_found = true;
            Serial.println("Device found. Connecting!");
        }
    }
};

void init_BLE_client() 
{
    BLEDevice::init("");
    _pBLEScan = BLEDevice::getScan();
    _pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    _pBLEScan->setActiveScan(true);
}

bool BLE_connect() {
	if (_scan_found == false) {
		_pBLEScan->start(2);
		return false;
	}

    if (_connected == true){
        return true;
    }
    Serial.print("Forming a connection to ");
    Serial.println(_myDevice->toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();

    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    // if you pass BLEAdvertisedDevice instead of address, 
    //it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");
    pClient->connect(*_myDevice);  

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(servUUID); 
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(servUUID.toString().c_str());
      return false;
    }
    Serial.println(" - Found our service");


    /* get all char from server */
    for (int i = 0; i < NB_CHAR; ++i)
    {
    	_remoteChar[i] = pRemoteService->getCharacteristic(charUUID[i]);
    }

    /* test if all char are valid */
    for (int i = 0; i < NB_CHAR; ++i)
    {
    	if (_remoteChar[i] == nullptr){
    		Serial.print("Erreur pour trouver les characteristics");
      		return false;
    	}
    }

    Serial.println(" all characteristics found");
    _connected = true;
    return true;
}


#endif