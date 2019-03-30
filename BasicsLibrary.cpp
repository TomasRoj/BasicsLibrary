/*
 * BasicsLibrary.h - A library for beginers with no or basic arduino knowledge.
 * Created by Tomas Roj, Started March third 2019.
 * Open source, free to use.
 */

#include "Arduino.h"
#include "BasicsLibrary.h"

BasicsLibrary::BasicsLibrary(int pin){
  _pin = pin;
}

void BasicsLibrary::btnSetup(int buttonPin){
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(_pin, HIGH);
}

void BasicsLibrary::blinking(){
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(1000);
}

void BasicsLibrary::serial(String text){
  Serial.begin(9600);
  Serial.println(text);
  delay(1500);
}

void BasicsLibrary::btn(int buttonPin){

  if (digitalRead(buttonPin) == LOW){
    digitalWrite(_pin, LOW);
    delay(5000);
    digitalWrite(_pin, HIGH);
  }
  else if(digitalRead(buttonPin) == HIGH){
    digitalWrite(_pin, HIGH);
  }

}

void BasicsLibrary::rgbLed(int red, int green, int blue){

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  delay(1000);
  digitalWrite(blue, LOW);
  delay(100);

}

void BasicsLibrary::servoTurning(int dataPin){
  #include <Servo.h>     
  Servo myservo;         
  int pos = 0;          

  myservo.attach(dataPin);   

  for(pos = 0; pos <= 180; pos += 1) 
  {
    myservo.write(pos);  
    delay(15);           
  } 
  for(pos = 180; pos >= 0; pos -= 1)
  {
    myservo.write(pos);  
    delay(15);           
  }

}

void BasicsLibrary::(const int displayPins, String text, int collums, int rows){
  #include <LiquidCrystal.h>
  LiquidCrystal lcd(displayPins);

  // set up the LCD's number of columns and rows:
  lcd.begin(collums, rows);
  // Print a message to the LCD.
  lcd.print(text);

  lcd.setCursor(0, 1);
}

void BasicsLibrary::instagramData(String ssid, String password, String userName){

#include "InstagramStats.h"

// ----------------------------
// Standard Libraries - Already Installed if you have ESP8266 set up
// ----------------------------

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include "JsonStreamingParser.h"

//------- Replace the following! ------
char ssid[] = ssid;         // your network SSID (name)
char password[] = password; // your network key

WiFiClientSecure client;
InstagramStats instaStats(client);

unsigned long delayBetweenChecks = 60000; //mean time between api requests
unsigned long whenDueToCheck = 0;

//Inputs
String userName = userName; // from their instagram url https://www.instagram.com/brian_lough/

void setup()
{

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  // If using ESP8266 Core 2.5 RC, uncomment the following
  // client.setInsecure();
}

void getInstagramStatsForUser()
{
  Serial.println("Getting instagram user stats for " + userName);
  InstagramUserStats response = instaStats.getUserStats(userName);
  Serial.println("Response:");
  Serial.print("Number of followers: ");
  Serial.println(response.followedByCount);
}

void loop()
{
  unsigned long timeNow = millis();
  if ((timeNow > whenDueToCheck))
  {
    getInstagramStatsForUser();
    whenDueToCheck = timeNow + delayBetweenChecks;
  }
}
}

void BasicsLibrary::wifiScan(){
  #include "ESP8266WiFi.h"

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");

  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);

}

void BasicsLibrary::wifiAccesPoint(String ssid, String password){
  
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID ssid
#define APPSK  password
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from esp!</h1>");
}

  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");


  server.handleClient();

}

void BasicsLibrary::rtcClock(){
#include <Wire.h>
#include <DS1307.h>

void setup()
{
    Serial.begin(9600);
    RTC.begin();
    
    Serial.print("Is Clock Running : ");
    if (RTC.isRunning())
            Serial.println("Yes");
    else
        Serial.println("No. Time may be Inaccurate");

    
    Serial.print("Hour Mode : ");
    if (RTC.getHourMode() == CLOCK_H24)
        Serial.println("24 Hours");
    else
        Serial.println("12 Hours");

    Serial.print(RTC.getDay());
    Serial.print("-");
    Serial.print(RTC.getMonth());
    Serial.print("-");
    Serial.print(RTC.getYear());

    Serial.print(" ");

    Serial.print(RTC.getHours());
    Serial.print(":");
    Serial.print(RTC.getMinutes());
    Serial.print(":");
    Serial.print(RTC.getSeconds());
    
    if (RTC.getHourMode() == CLOCK_H12)
    {
      switch(RTC.getMeridiem())
      {
        case HOUR_AM :
          Serial.print(" AM");
          break;
        case HOUR_PM :
          Serial.print(" PM");
          break;
      }
    }
    Serial.println("");
    Serial.print("Epoch Time : ");
    Serial.println(RTC.getEpoch());

    Serial.print("Is Out Pin Enabled : ");
    if (RTC.isOutPinEnabled())
            Serial.println("Yes");
    else
        Serial.println("No");

    Serial.print("Is SQWE Enabled : ");
    if (RTC.isSqweEnabled())
            Serial.println("Yes");
    else
        Serial.println("No");
}


void BasicsLibrary::playCrazyFog(int _pin){

  #include "pitches.h" //add Equivalent frequency for musical note
  #include "themes.h" //add Note vale and duration 

  for (int thisNote = 0; thisNote < (sizeof(CrazyFrog_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / CrazyFrog_duration[thisNote]; //convert duration to time delay
    tone(_pin, CrazyFrog_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;//Here 1.30 is tempo, decrease to play it faster
    delay(pauseBetweenNotes);
    noTone(_pin); //stop music on pin 8 
    }

}

void BasicsLibrary::playPirates(int _pin){
  #include "pitches.h" //add Equivalent frequency for musical note
  #include "themes.h" //add Note vale and duration

  for (int thisNote = 0; thisNote < (sizeof(Pirates_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Pirates_duration[thisNote];//convert duration to time delay
    tone(_pin, Pirates_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.05; //Here 1.05 is tempo, increase to play it slower
    delay(pauseBetweenNotes);
    noTone(_pin); //stop music on pin 8 
    }

}

void BasicsLibrary::playTitanic(int _pin){
  #include "pitches.h" //add Equivalent frequency for musical note
  #include "themes.h" //add Note vale and duration

  for (int thisNote = 0; thisNote < (sizeof(Titanic_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Titanic_duration[thisNote];//convert duration to time delay
    tone(_pin, Titanic_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 2.70;
    delay(pauseBetweenNotes);
    noTone(_pin); //stop music on pin 8 
    }
}