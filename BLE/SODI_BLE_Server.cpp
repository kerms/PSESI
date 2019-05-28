#include <Arduino.h>
#include "SODI_BLE.h"

BLECharacteristic *pCharacteristic[NB_CHAR];
BLEService *pService;
BLEServer *pServer;
boolean connected = false;
