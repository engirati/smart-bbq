// SmartProbe - Object that stores unique info for each probe.

#ifndef SmartProbe_h
#define SmartProbe_h

#include "application.h"
#include "ThermistorProbe.h"
#include "SimpleLed.h"

class SmartProbe
{
    public:
        SmartProbe(uint8_t probePin, uint8_t ledPin, ThermistorProbe::ProbeType probeType = ThermistorProbe::ProbeType::ET732, float tempAlarm = 140.0);
        ~SmartProbe();
        void setProbeType(ThermistorProbe::ProbeType probeType);
        ThermistorProbe::ProbeType getProbeType();
        void setTempAlarm(float tempAlarm);
        float getTempAlarm();
        void activate();
        void deactivate();
        uint8_t getPin();
    private:
        uint8_t _probePin; // probe pin
        ThermistorProbe::ProbeType _probeType; // probe type
        float _tempAlarm; // temperature alarm
        SimpleLed * _indicator; // probeindicator
};

#endif