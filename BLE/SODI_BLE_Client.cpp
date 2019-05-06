
#include <Arduino.h>
#include "SODI_BLE.h"

boolean _connected = false;
boolean _scan_found = false;
BLERemoteCharacteristic * _remoteChar[NB_CHAR];
BLEAddress* _myDevice;
BLEScan* _pBLEScan;
