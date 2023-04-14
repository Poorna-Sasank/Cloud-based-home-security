#include <Arduino.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <LittleFS.h>
#include <SD.h>
#include <Update.h>
#include <ETH.h>


#define irpin 14
#define flamepin 13
#define smokepin 33
#define ledpin1 18
#define ledpin2 16


const char* ssid = "nice";
const char* password = "12345678";

WiFiClient client;

unsigned long myChannelNumber = 2098070;
const char* myWriteAPIKey = "8G4FI8U5OAQ6SW1U";
const char* server = "api.thingspeak.com";


void Connect_to_Wifi();
void flame_check();

int smoke_conc = 0;

void setup() {

  Serial.begin(115200);
  Connect_to_Wifi();
  pinMode(flamepin, INPUT);
  pinMode(smokepin, INPUT);

}

void loop() {
  flame_check();
}

void Connect_to_Wifi() {

  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnection to ThingSpeak Server Established!!!\n");
  }
  
  ThingSpeak.begin(client);

}

void flame_check() {

  int flamestate = digitalRead(flamepin);
  int smoke_conc = analogRead(smokepin);

  int f_s = ThingSpeak.setField(3, flamestate);
  int s_s = ThingSpeak.setField(4, smoke_conc);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (flamestate == 0) 
  {
    Serial.println("Fire Detected");
    
  }
  /* if (flamestate == 1 && irstate == 1 && smoke_conc < 650) {
      Serial.println("No fire No Motion No smoke safe safe!");
    }
  else if (flamestate == 0 && irstate == 0) {
    Serial.println("Fire Detected at living place!");
    
  }
  else if (flamestate == 1 && irstate == 0) {
    Serial.println("Motion Detected!, safely no fire");
 
  }
  else if (flamestate == 0 && irstate == 1) {
    Serial.println("Fire detected!, No motion :)");
    
  }
  if (smoke_conc > 800) {
    Serial.print(smoke_conc);
    Serial.println("SOmke detected");
  }
  else {
    Serial.print(smoke_conc);
    Serial.println("No smoke");
  } */
}