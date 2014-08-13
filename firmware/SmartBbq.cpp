// SmartBbq - SmartBBQ Controller

#include "SmartBbq.h"

SmartBbq::SmartBbq(uint8_t probePin1
                , uint8_t probePin2
                , uint8_t probePin3
                , uint8_t probePin4
                , uint8_t ledPin1
                , uint8_t ledPin2
                , uint8_t ledPin3
                , uint8_t ledPin4
                , uint8_t fanPin1
                , uint8_t fanPin2) {

    // setup probe indicators(LEDs) and add them to pointer array
    //SmartProbe(uint8_t probePin, uint8_t ledPin, ThermistorProbe::ProbeType probeType = ThermistorProbe::ProbeType::ET732, float tempAlarm = 140.0);
    _smartProbes[0] = new SmartProbe(probePin1, ledPin1);
    _smartProbes[1] = new SmartProbe(probePin2, ledPin2);
    _smartProbes[2] = new SmartProbe(probePin3, ledPin3);
    _smartProbes[3] = new SmartProbe(probePin4, ledPin4);
    
    // setup ThermistorProbe
    _thermistorProbe = new ThermistorProbe(10000.0, 4095);

    // set default active probe
    _active = 0;
    _smartProbes[_active]->activate();
}

SmartBbq::~SmartBbq() {
    // deallocate memory
    if (_smartProbes) {
        delete[] _smartProbes;
    }
    
    if (_thermistorProbe) {
        delete _thermistorProbe;
    }
}

// cycles through probes
void SmartBbq::select() {
    // turn off old active led
    _smartProbes[_active]->deactivate();

    // if active probe is last one set back to first, otherwise increment
    if(_active == (PROBENUM - 1)) {
        _active = 0;
    } else {
        ++_active;
    }
    
    // turn on new active led
    _smartProbes[_active]->activate();
}

// increases set temp
void SmartBbq::up() {
    _smartProbes[_active]->setAlarmTemp(_smartProbes[_active]->getAlarmTemp() + 1);
}

// decreases set temp
void SmartBbq::down() {
    _smartProbes[_active]->setAlarmTemp(_smartProbes[_active]->getAlarmTemp() - 1);
}

// returns the active probes temp
float SmartBbq::getActiveTemp() {
    return getProbeTemp(_active);
}

// returns the active alarm
float SmartBbq::getActiveAlarm() {
    return getProbeAlarm(_active);
}

// returns probe temp
float SmartBbq::getProbeTemp(int probeIndex) {
    if(probeIndex > -1 || probeIndex < PROBENUM) {
        return _thermistorProbe->getTempF(_smartProbes[probeIndex]->getPin(), _smartProbes[probeIndex]->getProbeType());
    } else {
        return _thermistorProbe->getTempF(_smartProbes[_active]->getPin(), _smartProbes[_active]->getProbeType());
    }
}

// returns probe alarm
float SmartBbq::getProbeAlarm(int probeIndex) {
    if(probeIndex > -1 || probeIndex < PROBENUM) {
        return _smartProbes[probeIndex]->getAlarmTemp();
    } else {
        return _smartProbes[_active]->getAlarmTemp();
    }
}

// returns probe alarm enable
bool SmartBbq::getProbeAlarmE(int probeIndex) {
    if(probeIndex > -1 || probeIndex < PROBENUM) {
        return _smartProbes[probeIndex]->getAlarmEnable();
    } else {
        return _smartProbes[_active]->getAlarmEnable();
    }
}