
#include <Arduino.h>
#include "SODI_BLE.h"

BLEUUID servUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
BLEUUID charUUID[] = {
	BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"),
	BLEUUID("beb5484e-36e1-4688-b7f5-ea07361b26a8"),
	BLEUUID("beb5485e-36e1-4688-b7f5-ea07361b26a8"),
	BLEUUID("beb5486e-36e1-4688-b7f5-ea07361b26a8")
};