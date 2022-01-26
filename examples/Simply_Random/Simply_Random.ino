#include "Led3.h"
/*
  Testing Random mode with the  Led3 class

  For this class the valid modes are given by this enumeration.
  enum mode {
     Normal,
     Blink,
     Random,
     Flicker,
     Welding
   };

   This example demonstrates only one mode - Random
*/
Led3     myLed1(LED_BUILTIN);        // create LED 'software object'

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);                // for debug console
  Serial.println(__FILE__);

  myLed1.setMode(Random);

  // In the configuration below random time are configured to be between 5 and 10 seconds
  // The third parameter = true  means state change is also random
  //    (For example if LED is on: after the random time expires the commnad could still be to turn it on)
  // The third parameter = false means state will always flip
  //    (For example if LED is on: after the random time expires the commnad will always be to turn it off)
  myLed1.configRandom(5000, 10000, true);
}

// the loop function runs over and over again forever
void loop() {
  myLed1.update();     // the update function runs code appropriate for the mode (including checking all timings)
}
