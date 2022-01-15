#include <Arduino.h>
#include "WiFi.h"

#define WIFI_NETWORK "Red"
#define WIFI_PASSWORD "28ff84b5c2b2"
#define WIFI_TIMEOUT_MS 20000

void connectToWifi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
  
  unsigned long startAttemptTime = millis();
  
  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000){
    Serial.print(".");
    delay(100);
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println(" Failed");
    //take action
  }else{
    Serial.print(" Connected");
    Serial.println("Wifi.localIP()");
  
}

void setup(){
  Serial.begin(9600);
  connectToWifi();
}

void loop(){}
