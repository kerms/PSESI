/*
 *  This sketch sends a message to a TCP server
 *
 */
 
#include <Arduino.h>
#include <WiFi.h>

#include "wifi_client.h"




void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFi.begin(SESI_SSID, SESS_PASS);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}

const char * host = SESI_IPv4; // 194.168.1.40+N
const uint16_t port = 8000; // 8800+x router for 192.168.1.x
WiFiClient client;
char mess = 0;

void loop()
{
    Serial.print("connecting to ");
    Serial.print(host);
    Serial.print(":");
    Serial.println(String(port) );

    // Use WiFiClient class to create TCP connections


    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    if (mess == 115){
    // This will send the request to the server
        client.print("ok");
        Serial.println("mess ok send");
    }
    else if (mess == 114) {
        client.print("ko");
        Serial.println("mess ko send");
    } else {
        client.print("PERI2019 chaine envoyee\n");
        Serial.println("mess peri send");
    }


    //read back one line from server
    //String line = client.readStringUntil('\r');
    //client.println(line);

    Serial.println("closing connection");
    client.stop();

    Serial.println("wait 1 sec...");
    delay(1000);
}
