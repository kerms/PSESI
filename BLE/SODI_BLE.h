#ifndef __SODI_BLE_H__
#define __SODI_BLE_H__

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define NB_CHAR 4

extern BLEUUID servUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
extern BLEUUID charUUID[] = {
	BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"),
	BLEUUID("beb5484e-36e1-4688-b7f5-ea07361b26a8"),
	BLEUUID("beb5485e-36e1-4688-b7f5-ea07361b26a8"),
	BLEUUID("beb5486e-36e1-4688-b7f5-ea07361b26a8")
}


#endif