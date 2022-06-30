# Led3
Evolution of the Led class with multiple modes of operation. (normal, blink, random, flicker, welding)

    In normal mode (the default upon instantiation) this class defines the passed pin as an output.
    At this point the new object can only be turned on or off. However after creating
    your Led3 object variable you can change its mode by calling setMode(newMode)
    where newMode is an enumeration from this list:
    
    enum mode {
      Normal,
      Blink,
      Random,
      Flicker,
      Welding
    };
    
    Either before or after the mode change you can also call one of several configuration methods
    for your object to set the configuration values appropriate for the mode.
    
    Any call to on or off will reset the mode back to mode = Normal.
    (As will you setting the mode to Normal explicitly of course)
    In general the alternate modes of operation are intended for achieving animation effects on model layouts.
    Playing with the configuration constants can change the effects noticeably. 
    
    This class executes in a non blocking manner. (There are no delay calls).

### Files: Led3.h, Led3.CPP

## Example Program:
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

## Instantiation:

    Led3(byte pin);                    // Only the pin is given. mode defaults to Normal and The Led will default to off at the start.

## Member Functions
    Led3(byte pin);                    // Simple definition using defined pin as output
    void update();                     // update things based on elapsed time (call this in your loop code as often as possible)
    bool getState();                   // Return the current state of LED (on / off) Allows parts of your code to run only when LED is on for example.
    mode getMode();                    // return the LEDs current mode
    void setMode(mode newMode);        // set the LEDs mode
    int  getRandomPct();               // returns the percentage of the current time interval remaining (even in random mode)
    void configRandom(long minTime, long maxTime, bool cosMode); // sets the config values for random mode. (min max delay values, and change of state mode)
    void configFlicker(int Time, int Intensity);                 // sets the config values for flicker mode.(time constant and intensity)
    void configBlink(long onTime, long offTime);                 // sets the config values for blink mode.  (on / off time values)
    void configWelding(unsigned int dutyCycle, unsigned int dutyFactor, unsigned int weldingTime, unsigned int weldingIntensity, unsigned int afteglowPin); 
                                                                 // sets the config values for welding mode including second pin for afterglow output.    
    long onTime();                      // Return the current onTime
    long offTime();                     // Return the current offTime
    void off();                         // Turning off the LED (sets mode to Normal)
    void on();                          // Turning on  the LED (sets mode to Normal)
