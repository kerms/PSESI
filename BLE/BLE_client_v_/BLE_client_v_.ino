/**
 * A BLE client example that is rich in capabilities.
 * There is a lot new capabilities implemented.
 * author unknown
 * updated by chegewara
 */

#include "BLEDevice.h"
//#include "BLEScan.h"

// The remote service we wish to connect to.
static BLEUUID serviceUUID("139095a1-f62a-435d-87ca-a926a6776ce9"); // configurer cet UUID dans l'autre device qui se comporte comme le server
// The characteristic of the remote service we are interested in.
/*Definir plusieurs UUID characteristic pour chaque capteur*/
// configurer cet UUID dans notre device qui se comporte comme le server
static BLEUUID    charUUID_FL("28b5fa91-134a-4a11-8600-d67ac69821ae"); /////FLEX UUID À DEF....
static BLEUUID    charUUID_INC("9a0ba601-2289-41c1-9be1-aaabd4b73239");/////INCLINAISON
static BLEUUID    charUUID_ACCEL("a674cb19-8da3-464c-8056-835b5b43d554");/////ACCEL (X,Y,Z)
static BLEUUID    charUUID_GYRO("6bd02261-806c-4432-b1ff-d4f7853b18cc"); ////GYRO   (X,Y,Z)
static boolean doConnect = false;
//static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristicF;
static BLERemoteCharacteristic* pRemoteCharacteristicI;
static BLERemoteCharacteristic* pRemoteCharacteristicA;
static BLERemoteCharacteristic* pRemoteCharacteristicG;
static BLEAdvertisedDevice* myDevice;

/*static void notifyCallback( ///?????
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.print("data: ");
    Serial.println((char*)pData);
}*/ 
static void FlexnotifyCallback( ///La connexion qui sera executée 
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.print("data: ");
    Serial.println((char*)pData);
}


/*class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};*/
bool connectToServer() {/// exec
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    //pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID); 
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      return false;
    }
    Serial.println(" - Found our service");

    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristicF = pRemoteService->getCharacteristic(charUUID_FL);
    pRemoteCharacteristicI = pRemoteService->getCharacteristic(charUUID_INC);
    pRemoteCharacteristicA = pRemoteService->getCharacteristic(charUUID_ACCEL);
    pRemoteCharacteristicG = pRemoteService->getCharacteristic(charUUID_GYRO);    


    if (pRemoteCharacteristicF == nullptr || pRemoteCharacteristicI == nullptr || pRemoteCharacteristicA == nullptr || pRemoteCharacteristicG == nullptr) {                                         //ECHEC A LA CONNEXION AU CHARACTERISTIC
      Serial.print("Erreur pour trouver les characteristics  ");
      return false;
    } 
    Serial.println(" - characteristics trouvé");                                //SUCCES A LA CONNEXION AU SERVICE


   if(pRemoteCharacteristicF->canNotify())
      pRemoteCharacteristicF->registerForNotify(FlexnotifyCallback);

    //if(pRemoteCharacteristicI->canNotify())
    //pRemoteCharacteristicI->registerForNotify(InclnotifyCallback);

    //if(pRemoteCharacteristicA->canNotify())
    //  pRemoteCharacteristicA->registerForNotify(AccnotifyCallback);

    //if(pRemoteCharacteristicG->canNotify())
    //  pRemoteCharacteristicG->registerForNotify(GyronotifyCallback);

    // Read the value of the characteristic. /*On lit la valeur des caracteristiques pour chaque capteurs*/
    /*if(pRemoteCharacteristicF->canRead()) {
      std::string value = pRemoteCharacteristicF->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }
  
    if(pRemoteCharacteristicI->canRead()) {
      std::string value = pRemoteCharacteristicI->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristicA->canRead()) {
      std::string value = pRemoteCharacteristicA->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristicG->canRead()) {
      std::string value = pRemoteCharacteristicA->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    connected = true;*/
}
/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {/////exec
 /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();//on a trouvé ce qu'on cherchait, on stop
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true; //Pour dire qu'on est pret pour etre connecté
      Serial.println("Device found. Connecting!");
      doScan = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks


void setup() {
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
} // End of setup.


// This is the Arduino main loop function.
void loop() {

  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server and getting data");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

  
  
  delay(1000); // Delay a second between loops.
} // End of loop
