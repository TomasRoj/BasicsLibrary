## Welcome to BasicsLibrary docs.
An easy to-use library for beginners with examples to start their adventure with arduino.

### What is it & why you should use it.

BasicsLibrary is an open-source library for Arduino beginners. With easy to-use experience I made it. If you or your friend is having trouble with basics of arduino my library will problably help him. All you must know is how to use breadboard, connect wires and electronic componets to it. And thats all. Dont worry about source code again! With simple methods included you can just call one and focus on hardware. 

### How to set up:

1. Download and install BasicsLibrary from Arduino library manager (CTRL + SHIFT + I).
2. Use the following code into your Arduino sketch: 

```markdown
# #include <BasicsLibrary.h> //imports the library

# BasicsLibrary instance(4); 
//Creates the BasicsLibrary instance. There must be pin number even
//if you dont must to.
```
3. And thats it! Then just use your breadboard and one of the following methods with the instance name.
ex. instanceName.blinking().

### All methods - usage and requirements.

```markdown
# btnSetup(button pin);  
//Does the required setup of button.

# btn(button pin);   
//Defines code of button. Must be used with the btnSetup() method.

# blinking(); 
//Led blinking. Uses pin from instance creation.

# serial(String text);
//Starts and prints text to serial (9600 bauds.). Must be used with the string with text.

# rgbLed(int red, int green, int blue); 
//RGB led blinking with all of its colors. You must define pin of all three diod pins.

# servoTurning(int dataPin);
//turns servo from 0 to 180 degrees. Must be included with OUT pin of servo.

# displayWrite(const int displayPins, String text, int collums, int rows);
//Writes some text to display. Define connected pins, text and info about your display (collums, rows).

# instagramData(String ssid, String password, String userName);
//Gets number of instagram followers on your instagram. (ESP8266/ESP32).

```

### Support or Contact

Still Having trouble with BasicsLibrary? Write me on email - rojtomas@email.cz and I can help you with that! Or visit me on my personal website - www.tomasroj.herokuapp.com. Thanks for support! PS: Dont worry to contribute!
