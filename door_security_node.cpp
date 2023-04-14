#include <Arduino.h>
#include <Keypad.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <LittleFS.h>
#include <SD.h>
#include <Update.h>
#include <ETH.h>

#define irpin 14

const char* ssid = "Poorna";
const char* password = "12345678";

WiFiClient client;

unsigned long myChannelNumber = 2098070;
const char* myWriteAPIKey = "8G4FI8U5OAQ6SW1U";

const byte r = 4;
const byte c = 3;

char keys[r][c] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rpins[r] = {17, 5, 18, 19};
byte cpins[c] = {21, 22, 23};

Keypad keypad = Keypad(makeKeymap(keys), rpins, cpins, r, c);

const String pass = "172931";
String inpPass = "";
int attempt = 0;
int irstate = digitalRead(irpin);

void Connect_to_Wifi();
void pass_check();

void setup() {

  Serial.begin(115200);
  Connect_to_Wifi();

}

void loop() {

  pass_check();
  
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

void pass_check() {

  char key = keypad.getKey();
  if (key != NO_KEY) {
    
    if (key == '*') {
      inpPass = ""; //resetting the input password
      Serial.println("\n\tcleared\n\t");
    }
    else if (key == '#') {
      if (inpPass == pass) {
        Serial.println("\nCorrect Password\n");
        attempt = 0;
      }
      else {
        int x = ThingSpeak.setField(2, irstate);
        Serial.println("\nInvalid Password\n");
        attempt++;
        int c = ThingSpeak.setField(1, attempt);
        ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); 
        if (attempt == 3 && irstate == 0) {
          Serial.println("\nInvasion Detected!!! Sending Alert!#!#!\n");
        }

        else if (attempt == 3 && irstate == 1) {
          Serial.println("\nCloud Intrusion Detected!!! Please Shutdown the Power!!!\n");
        } 
      }
    }
    else { //if a number key is pressed
      inpPass += key; //add the pressed key to the input password
      Serial.print(key); //print the pressed key
    }
  }
}