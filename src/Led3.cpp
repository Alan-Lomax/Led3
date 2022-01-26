#include "Led3.h"

Led3::Led3(byte pin) {
  // Save the passed pin
  _pin = pin;
  _mode = Normal;    // assume normal mode until it is changed
  init();
}

void Led3::init() {
  pinMode(_pin, OUTPUT);    // define our output pin
  off();                    // call the function that sets out LED to off initially
}

void Led3::update() {
  switch (_mode) {
    case Blink:
      // If in blinking mode look at timing first
      if ( millis() >= _nextTime) {                                       // It is time to do something.
        _state = !_state;                                                 // swap states
        _startTime =  millis();                                           // capture the start time
        _nextTime =  millis() + (_state == HIGH ? _onTime : _offTime);    // and calculate when next
        // change of state is due
      }
      break;
    case Random:                                                // If in random mode look at timing first
      if ( millis() >= _nextTime) {                                       // It is time to do something.
        if (_randomCOS == true) {                                         // if the change of state itself is randomized
          long xfactor = random(0, 100);                                  // calculate a new random number
          _state =  (xfactor <= 50 ? HIGH : LOW);                         // state has 50/50 chance of going high or low. Doesnt matter what current state is.
        }
        else {
          _state = !_state;                                               // just swap states
        }
        _startTime = millis();
        _nextTime  = millis() + random(_minRandomTime, _maxRandomTime);   // calculate when next change of state will be due
      }
      break;
    case Flicker:
      if ( millis() >= _nextTime) {                             // It is time to do something.
        int bigFlicker = random(50, 50 + _flickerIntensity);    // calculate a random flicker intensity
        if ( bigFlicker >= 255) {
          bigFlicker = 255;                                     // Flicker intensity is capped
        }
        analogWrite(_pin, bigFlicker);
        _startTime = millis();
        _nextTime = millis() + random(10, _flickerTime);
      }
      break;
    case Welding:
      if ( millis() >= _nextTime) {                             // It is time to do something.
        if ( _dutyState) {                                      // duty state is like a random on off (welding or no welding)
          int bigFlicker = random(50, 70 + _flickerIntensity);  // calculate a random flicker intensity
          if ( bigFlicker >= 255) {
            bigFlicker = 255;                                   // Flicker intensity is capped
          }
          analogWrite(_pin, bigFlicker);
          if ( bigFlicker >= 100) {
            _weldingDecay++;                                    // Only add to counter for the welding afterglow during bright flickers
          }
          if ( _weldingDecay >= 200) {                          // Afterglow is capped
            _weldingDecay = 200;
          }
          analogWrite(_pin2, _weldingDecay / 2);                // build the after glow (only half brightness if main led is on)
        }
        else {
          analogWrite(_pin, 0);                                 // main pin is off
          if (_weldingDecay >= 100) {                           // decaying once welding stops
            _weldingDecay -= 3;                                 // start lowering the decay value rapidly at first
            analogWrite(_pin2, _weldingDecay);
          }
          else {
            analogWrite(_pin2, _weldingDecay--);                // slower decaying later
          }
          if (_weldingDecay <= 3) {                             // and finally a cut of point
            {
              analogWrite(_pin2, 0);
            }
          }
          _startTime = millis();
          _nextTime = millis() + random(20, _flickerTime);
        }
        if ( millis() >= _nextDutyTime) {
          _dutyState = !_dutyState;                               // Swap states
          if ( _dutyState) {
            _startTime = millis();
            _nextDutyTime = millis() + random(20, _weldingDuty);   // calculate when next duty cycle change of state will be due.
          }
          else {
            _startTime = millis();
            _nextDutyTime = millis() + (_weldingDutyFactor * random(20, _weldingDuty)); // off time has a multiplier factored in
          }
        }
      }
      break;
    case Normal:
      // do nothing special
      break;
  }
  if ((_mode != Flicker) && (_mode != Welding)) {
    digitalWrite(_pin, _state);                                           // update the actual output according to desired state
  }
}

bool Led3::getState() {
  // return the current state of the led (True or False)
  return _state;
}

mode Led3::getMode() {
  // return the current mode of the led (defined by enum)
  return _mode;
}

void Led3::setMode(mode newMode) {
  // set a new mode for the led (defined by enum)
  _mode = newMode;
  switch (_mode) {
    case Normal:
      _state = false;                      // In case it happened to be on when mode changed happened.
      break;
    case Blink:
      _startTime = millis();
      _nextTime =  millis() + _offTime;    // Next change of state will be when the off time has expired
      break;
    case Random:
      _startTime = millis();                                            // capture the start time
      _nextTime  = millis() + random(_minRandomTime, _maxRandomTime);   // calculate when next change of state will be due
      break;
    case Flicker:
      _startTime = millis();                                            // capture the start time
      _nextTime = millis() + random(_flickerTime);
      break;
    case Welding:
      _dutyState = false;
      _startTime = millis();                                  // capture the start time
      _nextTime = millis() + random(_flickerTime);
      _nextDutyTime = millis() + random(20, _weldingDuty);    // calculate when next duty cycle change of state will be due. 20ms is the minimum
      break;
  }
}

int Led3::getRandomPct() {
  // return the percent of the interval remaining
  return map(millis(), _startTime, _nextTime, 0, 100);
}

void Led3::configRandom(long minTime, long maxTime, bool cosMode) {
  _maxRandomTime = maxTime;      // max milliseconds of Random
  _minRandomTime = minTime;      // min milliseconds of Random
  _randomCOS = cosMode;          // true if change of state will itself be random. If false new state will be opposite of current state
  _startTime = millis();                                            // capture the start time
  _nextTime  = millis() + random(_minRandomTime, _maxRandomTime);   // calculate when next change of state will be due
}

void Led3::configFlicker(int Time, int Intensity) {
  _flickerTime = Time;
  _flickerIntensity = Intensity;
  _startTime = millis();                                  // capture the start time
  _nextTime = millis() + random(_flickerTime);
}

void Led3::configBlink(long onTime, long offTime) {
  _onTime = onTime;
  _offTime = offTime;
}

void Led3::configWelding(unsigned int duty, unsigned int dutyFactor, unsigned int weldingTime, unsigned int weldingIntensity, unsigned int afterGlowPin) {
  _pin2 = afterGlowPin;
  pinMode(_pin2, OUTPUT);                // define our output pin for afterglow
  digitalWrite(_pin2, false);            // force it off for now
  _dutyState = false;                    // start off not weldng
  _weldingDuty = duty;                   // maximum ms time spent welding (randomized)
  _weldingDutyFactor = dutyFactor;       // A multiplier on the off time (eg 4 means 4 times longer off time than on time) Still randomized
  _flickerTime = weldingTime;            // reuse _flickerTime as time value for welding effect
  _flickerIntensity = weldingIntensity;  // reuse _flickerIntensity (brightness) for welding
  _startTime = millis();                                  // capture the start time
  _nextTime = millis() + random(_flickerTime);
  _nextDutyTime = millis() + random(20, _weldingDuty);    // calculate when next duty cycle change of state will be due. 20ms is the minimum
}

long Led3::onTime() {
  // return the current on time of the led
  return _onTime;
}

long Led3::offTime() {
  // return the current off time of the led
  return _offTime;
}

void Led3::off() {
  _mode = Normal;         // Set the mode to Normal (cancels blink, random and flicker by doing so.)
  _state = LOW;           // Set the desired state - LED will turn off on next call to update
}

void Led3::on() {
  _mode = Normal;         // Set the mode to Normal (cancels blink, random and flicker by doing so.)
  _state = HIGH;          // Set desired state LED will turn on with next call to update
}
