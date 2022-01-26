#ifndef MY_LED3_H
#define MY_LED3_H
#include <arduino.h>
/*
 *****************************************************
 ** LED3_H                                          **
 **                                                 **
 ** This class implements standard LED on-off       **
 ** logic on a pin you specify plus several         **
 ** configurable mode effects. It does this without ** 
 ** any delay calls. (no blocking code)             **
 ** Jan 2022 : added random, flicker and welding    **
 **                                                 **
 *****************************************************
*/
enum mode {
  Normal,
  Blink,
  Random,
  Flicker,
  Welding
};

class Led3 {
  private:
    int _pin;                           // the number of the LED pin (for welding recommend blue or white LED, for flicker yellow)
    int _pin2;                          // a second pin number for afterglow effect when welding (recommend red LED)
    unsigned long _onTime;              // milliseconds of on-time
    unsigned long _offTime;             // milliseconds of off-time
    unsigned long _maxRandomTime;       // max milliseconds of Random
    unsigned long _minRandomTime;       // min milliseconds of Random
    unsigned int  _flickerTime;         // time value for flicker or welding effect
    unsigned int  _flickerIntensity;    // intensity (brightness) for flicker or welding
    unsigned int  _weldingDuty;         // Max ms time spent welding (Randomized) 
    unsigned int  _weldingDutyFactor;   // A multiplier on the off time (eg 4 means 4 times longer off time than on time) Still randomized
    int           _weldingDecay;        // Counter used to decay the afterglow effect
    bool          _randomCOS;           // true if change of state will be random. If false new state will be opposite of current state
    unsigned long _nextTime;            // next time change in milliseconds
    unsigned long _nextDutyTime;        // next time of welding duty in milliseconds
    bool          _dutyState;           // what is the current duty state (t/f)
    unsigned long _startTime;           // the start time of the current time interval in milliseconds
    mode _mode = Normal;                // by default start off in normal on/off mode.
    int _state;                         // ledstate used to set the LED
    void init();                        // Initialization code
    void initRandom();                  // Initialization code when in random mode

  public:
    Led3(byte pin);                     // Simple definition using defined pin as output
    void update();                      // update things based on elapsed time (call this as often as possible)
    bool getState();                    // Return the current state of LED (on / off) Allows parts of your code to run only when LED is on for example.
    mode getMode();                     // return the LEDs current mode
    void setMode(mode newMode);         // set the LEDs mode
    int  getRandomPct();                // returns the percentage of the current time interval remaining (even in random mode)
    void configRandom(long minTime, long maxTime, bool cosMode); // sets the config values for random mode. (min max delay values, and change of state mode)
    void configFlicker(int Time, int Intensity);                 // sets the config values for flicker mode.(time constant and intensity)
    void configBlink(long onTime, long offTime);                 // sets the config values for blink mode.  (on / off time values)
    void configWelding(unsigned int dutyCycle, unsigned int dutyFactor, unsigned int weldingTime, unsigned int weldingIntensity, unsigned int afteglowPin); 
                                                                 // sets the config values for welding mode including second pin for afterglow output.    
    long onTime();                      // Return the current onTime
    long offTime();                     // Return the current offTime
    void off();                         // Turning off the LED (sets mode to Normal)
    void on();                          // Turning on  the LED (sets mode to Normal)
};
#endif
