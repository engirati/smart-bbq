// SimpleButton - Library for simple one click button with internal pullup.
// http://arduino.cc/en/Tutorial/Debounce

#include "SimpleButton.h"
#include "application.h"

SimpleButton::SimpleButton(uint8_t pin, long debounceDelay) {
    _pin = pin;
    _debounceDelay = debounceDelay;
    _lastButtonState = LOW;
    pinMode(_pin, INPUT_PULLUP);
}

// check if the button was pressed
// http://arduino.cc/en/Tutorial/Debounce
bool SimpleButton::isPressed() {
    // assume button has not been pressed
    _rval = false;
    
    // read the state of the switch into a local variable:
    int _reading = digitalRead(_pin);
    
    // check to see if you just pressed the button 
    // (i.e. the input went from LOW to HIGH),  and you've waited 
    // long enough since the last press to ignore any noise:  
    
    // If the switch changed, due to noise or pressing:
    if (_reading != _lastButtonState) {
        // reset the debouncing timer
        _lastDebounceTime = (long)millis();
    }
    
    if (((long)millis() - _lastDebounceTime) > _debounceDelay) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:
        
        // if the button state has changed:
        if (_reading != _buttonState) {
            _buttonState = _reading;
            
            // only toggle the LED if the new button state is HIGH
            if (_buttonState == HIGH) {
                _rval = true;
            }
        }
    }
    
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    _lastButtonState = _reading;

    return _rval;
}