/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID          "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID_F "ecd7a2f4-b9c2-410f-9733-c40e75b95c59"
#define CHARACTERISTIC_UUID_I "664f55f7-b436-4aca-b1d0-2505b456a5f5"
#define CHARACTERISTIC_UUID_A "a674cb19-8da3-464c-8056-835b5b43d554"
#define CHARACTERISTIC_UUID_G "4d06fd2b-3286-42d6-b218-3716ca62c5e9"
#define bleServerName "ESP32_server"

static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
static BLECharacteristic *pCharacteristicF;
static BLECharacteristic *pCharacteristicI;
static BLECharacteristic *pCharacteristicA;
static BLECharacteristic *pCharacteristicG;

static boolean connected = false;
uint8_t value = 0;

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

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  BLEDevice::init(bleServerName); //donner un nom à notre server
  BLEServer *pServer = BLEDevice::createServer();
  Serial.println("Server created!");
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(serviceUUID, 10);  // cree un service 
  Serial.println("Service created!");
  //Characteristic flex
pCharacteristicF = pService->createCharacteristic( // cree une characteristic avec droit d'etre lu et modifié
                                         CHARACTERISTIC_UUID_F,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
//Characteristic incli
pCharacteristicI = pService->createCharacteristic( // cree une characteristic avec droit d'etre lu et modifié
                                         CHARACTERISTIC_UUID_I,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );    
//Characteristic accel
pCharacteristicA = pService->createCharacteristic( // cree une characteristic avec droit d'etre lu et modifié
                                         CHARACTERISTIC_UUID_A,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );  
//Characteristic gyro
pCharacteristicG = pService->createCharacteristic( // cree une characteristic avec droit d'etre lu et modifié
                                         CHARACTERISTIC_UUID_G,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );   
Serial.println("Characteristics flags defined!");

 Serial.println("Debug1");
 pCharacteristicF->setValue("set flex");
 pCharacteristicI->setValue("set incl");
 pCharacteristicA->setValue("set accl");
 pCharacteristicG->setValue("set gyro");
Serial.println("Debug2");
  pService->start();
  Serial.println("Service started!");
  BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  //BLEAdvertising *pAdvertising = BLEDevice::getAdvertising(); // creation de l'advertiser
  /* INITIALISATION DE L'ADVERTISER*/
  pAdvertising->addServiceUUID(SERVICE_UUID); 
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising(); // Activation pour dire que "Hey je suis là"
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  if (connected)
  {
    //Serial.printf ("valeur mise des capteurs: %d\n", value);
    Serial.printf ("Mise à jour valeur des capteurs dans les characteristics\n");
    pCharacteristicF->setValue("0"); // Ecriture d'une valeur dans le characteristic qu'on va pourvoir lire ou modifier
     pCharacteristicF->notify();
     
    pCharacteristicI->setValue("1");
     pCharacteristicI->notify();
   pCharacteristicA->setValue("2");
     pCharacteristicA->notify();
   pCharacteristicG->setValue("3");
   pCharacteristicG->notify();
    //value++;
    }
  delay(2000);
}
