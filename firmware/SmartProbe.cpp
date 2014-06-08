// SmartProbe - Object that stores unique info for each probe.

#include "SmartProbe.h"

SmartProbe::SmartProbe(uint8_t probePin, uint8_t ledPin, ThermistorProbe::ProbeType probeType, float tempAlarm) {
    _probePin = probePin;
    _probeType = probeType;
    _tempAlarm = tempAlarm;
    
    _indicator = new SimpleLed(ledPin);
}

SmartProbe::~SmartProbe() {
    if(_indicator) {
        delete _indicator;
    }
}

void SmartProbe::setProbeType(ThermistorProbe::ProbeType probeType) {
    _probeType = probeType;
}

ThermistorProbe::ProbeType SmartProbe::getProbeType() {
    return _probeType;
}

void SmartProbe::setTempAlarm(float tempAlarm) {
    _tempAlarm = tempAlarm;
}

float SmartProbe::getTempAlarm() {
    return _tempAlarm;
}

void SmartProbe::activate() {
    _indicator->on();
}

void SmartProbe::deactivate() {
    _indicator->off();
}

uint8_t SmartProbe::getPin() {
    return _probePin;
}