#ifndef __WIFI_CLIENT__
#define __WIFI_CLIENT__

#include <Arduino.h>
#include <WiFi.h>

#define _STR(x) #x
#define STR(x) _STR(x)

#define GR_NO 6
#define SESI_SSID "dd-wrt"
#define SESS_PASS "peri2019"
#define SESI_IPv4 "192.168.1.4" STR(GR_NO)
#define SESI_PORT 8800 + 40 + GR_NO

//int wifi_connect(const char * SSID, const char * PASS = NULL, int timeout=0);

int wifi_connect(const char * SSID, const char * PASS=NULL, int timeout=0) {
  int err = 0;

  if ( err = WiFi.begin(SSID, PASS)) {
    return err;
  }

  if (!timeout){
    return WiFi.status();
  }

  if (timeout <= -1) {
    while(WiFi.status() != WL_CONNECTED) {
          Serial.print(".");
          delay(500);
      }
  } else {
    delay(timeout);
    err = WiFi.status(); 
    if ( err != WL_CONNECTED) {
      return err;
    }
  }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    return err;
}

int wifi_connect_server( char * host,uint16_t port, int timeout=0) {
    int err = 0;



  if ( err = client.connect(host, port)) {
    return err;
  }

  if (!timeout){
    return WiFi.status();
  }

  if (timeout <= -1) {
    while(!client.connect(host, port)) {
          Serial.print(".");
          delay(500);
      }
  } else {
    delay(timeout);
    err = client.connect(host, port); 
    if ( err != WL_CONNECTED) {
      return err;
    }
  }
    

    return err;

  
}


#endif
