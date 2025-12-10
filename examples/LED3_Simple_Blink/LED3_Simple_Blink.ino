#include "Led3.h"
/*
  Testing Blink mode with the  Led3 class

*/
Led3     myLed1(7);        // create LED 'software object'

// the setup function runs once when you press reset or power the board
void setup() {

  myLed1.setMode(Blink);

  // In the configuration below Blink time is set as 50ms on and 500 ms off.
  myLed1.configBlink(50, 500);
}

// the loop function runs over and over again forever
void loop() {
  myLed1.update();     // the update function runs code appropriate for the mode (including checking all timings)
}
