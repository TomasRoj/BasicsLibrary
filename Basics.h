/*
 * BasicsLibrary.h - A library for beginers with no or basic arduino knowledge.
 * Created by Tomas Roj, March third 2019.
 * Open source, free to use.
 */

#ifndef Basics_h
#define Basics_h

#include "Arduino.h"

class Basics
{
  public:
    Basics(int pin);
    void blinking();
    void serial(String text);
    void btn(int button);
    void btnSetup(int button);
    void rgbLed(int red, int green, int blue);
    void servoTurning(int dataPin);
  private:
    int _pin;
};

#endif