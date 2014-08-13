// SmartBbq - SmartBBQ Controller

#ifndef SmartBbq_h
#define SmartBbq_h

#include "application.h"
#include "ThermistorProbe.h"
#include "SmartProbe.h"

#define PROBENUM 4
#define FANNUM2

class SmartBbq
{
    public:
        SmartBbq(uint8_t probePin1
                , uint8_t probePin2
                , uint8_t probePin3
                , uint8_t probePin4
                , uint8_t ledPin1
                , uint8_t ledPin2
                , uint8_t ledPin3
                , uint8_t ledPin4
                , uint8_t fanPin1
                , uint8_t fanPin2);
        ~SmartBbq();
        void select();
        void up();
        void down();
        float getActiveTemp();
        float getActiveAlarm();
        float getProbeTemp(int probeIndex);
        float getProbeAlarm(int probeIndex);
        bool getProbeAlarmE(int probeIndex);
    private:
        ThermistorProbe * _thermistorProbe; // Define ThermisterProbe
        SmartProbe * _smartProbes[PROBENUM]; // array of SmartProbe objects
        uint8_t _active; // index of currently selected probe 0-3
};

#endif