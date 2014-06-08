// SimpleLed - Library for maintaining and changing LED state.

#include "SimpleLed.h"
#include "application.h"

SimpleLed::SimpleLed(uint8_t pin, bool initialState) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
    setState(initialState);
}

// returns state of led
bool SimpleLed::getState() {
    return _state;
}

// set state of led and updates led
void SimpleLed::setState(bool state) {
    _state = state;
    updateLed();
}

// turns led on
void SimpleLed::on() {
    setState(ON);
}

// turns led off
void SimpleLed::off() {
    setState(OFF);
}

// toggles state of led and updates led
void SimpleLed::toggle() {
    setState(!_state);
}

// updates led to match the state
void SimpleLed::updateLed() {
    digitalWrite(_pin, _state);
}