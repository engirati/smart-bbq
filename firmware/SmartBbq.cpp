// SmartBbq - SmartBBQ Controller

#include "SmartBbq.h"

SmartBbq::SmartBbq(uint8_t probePin1
                , uint8_t probePin2
                , uint8_t probePin3
                , uint8_t probePin4
                , uint8_t ledPin1
                , uint8_t ledPin2
                , uint8_t ledPin3
                , uint8_t ledPin4) {

    // setup probe indicators(LEDs) and add them to pointer array
    _smartProbes[0] = new SmartProbe(probePin1, ledPin1);
    _smartProbes[1] = new SmartProbe(probePin2, ledPin2);
    _smartProbes[2] = new SmartProbe(probePin3, ledPin3);
    _smartProbes[3] = new SmartProbe(probePin4, ledPin4);
    
    // setup ThermistorProbe
    _thermistorProbe = new ThermistorProbe(21570.0, 4095);

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
        _active += 1;
    }
    
    // turn on new active led
    _smartProbes[_active]->activate();
}

// increases set temp
void SmartBbq::up() {
    _smartProbes[_active]->setTempAlarm(_smartProbes[_active]->getTempAlarm() + 1);
}

// decreases set temp
void SmartBbq::down() {
    _smartProbes[_active]->setTempAlarm(_smartProbes[_active]->getTempAlarm() - 1);
}

// returns the active probes temp
float SmartBbq::getActiveTemp() {
    return _thermistorProbe->getTempF(_smartProbes[_active]->getPin(), _smartProbes[_active]->getProbeType());
}
