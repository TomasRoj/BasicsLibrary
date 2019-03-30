/*
 * BasicsLibrary.h - A library for beginers with no or basic arduino knowledge.
 * Created by Tomas Roj, Started March third 2019.
 * Open source, free to use.
 */

#ifndef BasicsLibrary_h
#define BasicsLibrary_h

#include "Arduino.h"

class BasicsLibrary
{
  public:
    BasicsLibrary(int pin);
    void blinking();
    void serial(String text);
    void btn(int button);
    void btnSetup(int button);
    void rgbLed(int red, int green, int blue);
    void servoTurning(int dataPin);
    void displayWrite(const int displayPins, String text);
    void instagramData(String ssid, String password, String userName);
    void wifiScan();
    void wifiAccesPoint(String ssid, String password);
    void rtcClock(); //DS1307
    void playCrazyFrog(int pin);
    void playPirates(int pin);
    void playTitanic(int pin);
  private:
    int _pin;
};

#endif