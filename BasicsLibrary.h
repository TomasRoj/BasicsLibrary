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
    void unoBlinking();
    void serial(String text);
    void btn(int button);
    void btnSetup(int button);
    void rgbLed(int red, int green, int blue);
    void servoTurning(int dataPin);
    void displayWrite(int one, int two, int three, int four, int five, int six, String text);
    void wifiScan();
    void wifiAccesPoint(String ssid, String password);
    void rtcClock(); //DS1307
    void playCrazyFrog();
    void playPirates();
    void playTitanic();
    void playStarWars();
    void potenciometerPWM();
    void blinkNoDelay();
  private:
    int _pin;
};

#endif