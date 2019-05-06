#ifndef __SODI_BLE_H__
#define __SODI_BLE_H__

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define NB_CHAR 4

extern BLEUUID servUUID;
extern BLEUUID charUUID[];

#endif