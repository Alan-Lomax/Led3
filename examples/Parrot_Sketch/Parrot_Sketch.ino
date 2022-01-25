#include "Led3.h"
/*
  Testing modes with the  Led3 class
*/

// #######################################################
int testCase = 4;  // choose a test case (from 1 to 7)  ##
// #######################################################

Led3     myLed1(13);             // create LED 'software object'  Yellow
Led3     myLed2(12);             // create LED 'software object'  Blue
Led3     myLed3(11);             // create LED 'software object'  Red

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);                // for debug console
  Serial.println(__FILE__);
  switch (testCase) {
    case 1:
      myLed1.setMode(Blink);
      myLed1.configBlink(10, 500);        // 1ms = a dim flash, 10ms full brightness flash
      break;
    case 2:
      myLed3.setMode(Flicker);            // Flicker works best on pins with PWM = 3,5,6,9,10,11 (on NANO)
      myLed3.configFlicker(25, 255);      // first value is timing, second is brightness, both are randomized inside class.
      break;
    case 3:
      myLed2.setMode(Random);
      myLed2.configRandom(5000, 10000, true);   // random time between 5 and 10 seconds. true means on/off direction is also random. (false means always change state)
      break;
    case 4:
      myLed2.setMode(Welding);
      myLed2.configWelding(1000, 6, 10, 200, 11); // on time, multiplier for off time, flicker timing, brightness, 2nd pin = Red Led
      break;
    case 5:
      myLed1.setMode(Flicker);            // Flicker works best on pins with PWM = 3,5,6,9,10,11 (on NANO)
      myLed1.configFlicker(25, 255);      // first value is timing, second is brightness, both are randomized inside class.

      break;
    case 6:
      myLed1.setMode(Flicker);            // Flicker works best on pins with PWM = 3,5,6,9,10,11 (on NANO)
      myLed1.configFlicker(25, 255);      // first value is timing, second is brightness, both are randomized inside class.
      myLed2.setMode(Random);
      myLed2.configRandom(5000, 10000, true);   // random time between 5 and 10 seconds. true means on/off direction is also random. (false means always change state)
      myLed3.setMode(Blink);
      myLed3.configBlink(250, 750);
      break;
    case 7:
      myLed1.setMode(Blink);
      myLed1.configBlink(50, 300);
      myLed2.setMode(Blink);
      myLed2.configBlink(250, 500);
      myLed3.setMode(Blink);
      myLed3.configBlink(850, 150);
      break;
  }
}

// the loop function runs over and over again forever
void loop() {

  switch (testCase) {
    case 1:
      myLed1.update();
      break;
    case 2:
      myLed3.update();
      break;
    case 3:
      myLed2.update();
      break;
    case 4:
      myLed2.update();
      break;
    case 5:
      myLed1.update();
      myLed3.update();
      break;
    case 6:
      myLed1.update();
      myLed2.update();
      myLed3.update();
      break;
    case 7:
      myLed1.update();
      myLed2.update();
      myLed3.update();
      break;
  }
}
