/*
 * BasicsLibrary.h - A library for beginers with no or basic arduino knowledge.
 * Created by Tomas Roj, March third 2019.
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

void BasicsLibrary::instagramData(String ssid, String password){

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