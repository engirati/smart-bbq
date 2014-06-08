// SimpleButton - Library for simple one click button with internal pullup.

#ifndef SimpleButton_h
#define SimpleButton_h

#include "application.h"

class SimpleButton
{
    public:
        SimpleButton(uint8_t pin, long debounceDelay = 20);
        bool isPressed();
    private:
        int _pin;
        long _debounceDelay;
        bool _active;
        int _reading;
        long _lastDebounceTime;
        bool _buttonState;
        bool _lastButtonState;
        bool _rval;
};

#endif