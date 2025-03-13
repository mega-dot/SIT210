/*
  WriteMultipleFields
  
  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 20 seconds.
  
  Hardware: Arduino MKR1000
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
  - Requires WiFi101 library version 0.15.3 or newer.
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/

#include <WiFiNINA.h>
#include "ThingSpeak.h"
#include "secrets.h"  // Include the secrets file

WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int LDR_PIN = A0;  // Light sensor connected to A0

void setup() {
    Serial.begin(115200);
    while (!Serial);

    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("WiFi module not found!");
        while (true);
    }

    Serial.print("Connecting to Wi-Fi...");
    while (WiFi.begin(SECRET_SSID, SECRET_PASS) != WL_CONNECTED) {
        Serial.print(".");
        delay(5000);
    }
    Serial.println("Connected!");

    ThingSpeak.begin(client);
}

void loop() {
    int lightValue = analogRead(LDR_PIN);
    Serial.print("Light Intensity: ");
    Serial.println(lightValue);

    ThingSpeak.setField(1, lightValue);
    int response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (response == 200) {
        Serial.println("Data sent successfully!");
    } else {
        Serial.println("Error sending data: " + String(response));
    }

    delay(60000); // Send data every 60 seconds
}
