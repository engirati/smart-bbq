// SimpleLed - Library for maintaining and changing LED state.

#ifndef SimpleLed_h
#define SimpleLed_h

#include "application.h"

#define ON HIGH
#define OFF LOW

class SimpleLed
{
    public:
        SimpleLed(uint8_t pin, bool initialState = OFF);
        bool getState();
        void setState(bool state);
        void on();
        void off();
        void toggle();
    private:
        bool _state;
        int _pin;
        void updateLed();
};

#endif