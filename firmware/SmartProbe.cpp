// SmartProbe - Object that stores unique info for each probe.

#include "SmartProbe.h"

SmartProbe::SmartProbe(uint8_t probePin, uint8_t ledPin, ThermistorProbe::ProbeType probeType, float alarmTemp, bool alarmEnable) {
    _probePin = probePin;
    _probeType = probeType;
    _alarmTemp = alarmTemp;
    _alarmEnable = alarmEnable;
    
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

void SmartProbe::setAlarmTemp(float alarmTemp) {
    _alarmTemp = alarmTemp;
}

float SmartProbe::getAlarmTemp() {
    return _alarmTemp;
}

void SmartProbe::setAlarmEnable(bool alarmEnable) {
    _alarmEnable = alarmEnable;
}

float SmartProbe::getAlarmEnable() {
    return _alarmEnable;
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