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

void BasicsLibrary::unoBlinking(){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  
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

//Shows all of basic colors on connected rgb led.
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

//Turns servo from 0 to 180 degrees.
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

//This code will run only if the board is eps8266 or esp32 based.
#if defined(ESP8266) || defined(ESP32)

  void BasicsLibrary::wifiAccesPoint(String ssid, String password){
    
    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266WebServer.h>

    #ifndef APSSID
    #define APSSID ssid //Uses variables from arguments.
    #define APPSK  password
    #endif

    const char *ssid = APSSID;
    const char *password = APPSK;

    ESP8266WebServer server(80);

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
//Ends esp8266 or esp32 based boards code.
#endif

void BasicsLibrary::rtcClock(){
  // Real time clock DS1307

#include <Wire.h>
#include "RTClib.h"

// Instance from library.
RTC_DS1307 DS1307;

// Days in week.
char seznamDni[7][8] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


  // Start serial communicaation 9600 baud
  Serial.begin(9600);
  // check status.
  if (! DS1307.begin()) {
    Serial.println("RTC is not connected!");
    while (1);
  }

  if (! DS1307.isrunning()) {
    Serial.println("RTC is not on. Turning on...");
  }
  // Only one time setting time.
  // In this style:  year, month, days, hour, minute, secon
  // Example: 26.4.2016 9:10:11
  DS1307.adjust(DateTime(2016, 4, 26, 9, 10, 11));


  // Load actual time to datumCas variable
  DateTime datumCas = DS1307.now();
  // Sends actual time on serial.
  Serial.print("Actual time: ");
  Serial.print(datumCas.hour());
  Serial.print(':');
  Serial.print(datumCas.minute());
  Serial.print(':');
  Serial.print(datumCas.second());
  Serial.print(", ");
  Serial.print(seznamDni[datumCas.dayOfTheWeek()]);
  Serial.print(" ");
  Serial.print(datumCas.day());
  Serial.print('.');
  Serial.print(datumCas.month());
  Serial.print('.');
  Serial.print(datumCas.year());
  Serial.println();
  // Some delay
  delay(2000);

}

//Theese functions plays melody on buzzer.

void BasicsLibrary::playCrazyFrog(){

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

void BasicsLibrary::playPirates(){
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

void BasicsLibrary::playTitanic(){
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

//Writes some text on display. Normally set on 16x2 [Needs some remake].

void BasicsLibrary::displayWrite(int one, int two, int three, int four, int five, int six, String text){
  // Library
  #include <LiquidCrystal.h>

  // Pin setting. Connected to ins in argument.
  LiquidCrystal lcd(one, two, three, four, five, six);

    // Here the problem is. Default set to 16x2. Needs some remake.
    lcd.begin(16, 2);
    // Prints text. Dont forget we start counting from 0 :-D
    lcd.setCursor ( 0, 1 );
    lcd.print(text);
}

void BasicsLibrary::potenciometerPWM(int potenciometer){

  int potPin = potenciometer;    // číslo pinu připojeného potenciometru
  int ledPin = _pin;     // číslo pinu připojené LED diody

  int potProm = 0;    // proměnná pro analogovou hodnotu potenciometru
  int ledProm = 0;    // proměnná pro analogovou hodnotu PWM

  pinMode(potPin, INPUT);

  // načtení analogové hodnoty senzoru a uložení do proměnné
  potProm = analogRead(potPin);
  // přepočet hodnot z potenciometru na PWM LED diody
  ledProm = map(potProm, 0, 1023, 0, 255);
  // nastavení napětí na LED diodě odpovídající hodnotě PWM
  analogWrite(ledPin, ledProm);


  // pauza programu na 2 ms pro ustálení 
  // analogově-digitálního převodníku
  // po předchozím čtení hodnot
  delay(2);

}

void BasicsLibrary::blinkNoDelay(){
  const int ledPin =  _pin;
  int ledState = LOW;
  unsigned long previousMillis = 0;
  unsigned long interval = 1000;
 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(ledPin, ledState);
  }

}