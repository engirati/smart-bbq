// ThermistorProbe - Library for reading thermistor based temperature probes.
// Contributions and influence from @BDub and @avidan
// https://community.spark.io/t/thermistors-and-the-spark-core/1276

#include "ThermistorProbe.h"
#include "math.h"

#define DEBUG FALSE

// TermisterProbe constructor
// pur - Pullup resistor value in ohms
// adcRef - ADC reference value
ThermistorProbe::ThermistorProbe(double pur, int adc)
{
    _pur = pur;
    _adc = adc;
}

ThermistorProbe::~ThermistorProbe() {
    ;;;
}

// Returns the temperature in Kelvin based off of the Steinhart-Hart equation.
// http://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
double ThermistorProbe::getTempK(int pin, enum ProbeType probeType, bool smooth)
{
    delay(1);
    
    if(DEBUG) {
        Serial.print("Pin: ");
        Serial.println(pin);
    }
    
    // Read in analog value
    int aval = analogRead(pin);
    
    // read in smoothly
    if(smooth==true) {
        int total = 0;
        
        for(int i=0; i<100; i++) {
            total += analogRead(pin);
            delay(1);
        }
        
        aval = total/100;
    } else {
        aval = analogRead(pin);
    }
    
    // define probe type
    _probeType = probeType;
    
    // select probe specific constants
    switch (_probeType) {
        case ET72:
            // ET-7, ET-72, ET-73, ET-72/73 probe constants
            A = 0.00023067431;
            B = 0.00023696594;
            C = 1.2636415e-7;
            break;
        case ET732: default:
            // ET-732 probe constants
            // https://github.com/CapnBry/HeaterMeter
            A = 0.00023067431;
            B = 0.00023696594;
            C = 1.2636415e-7;
            break;
    }
            
    if(DEBUG) {
        Serial.print("A: ");
        Serial.println(A,14);
        Serial.print("B: ");
        Serial.println(B,14);
        Serial.print("C: ");
        Serial.println(C,14);
        Serial.print("Analog value: ");
        Serial.println(aval);
        Serial.print("ADC ref: ");
        Serial.println(_adc);
    }
    
    // calculate resistance
    double R = (double)(1 / ((_adc / ((double) aval * 1.025)) - 1)) * (double)_pur;
    
    if(DEBUG) {
        Serial.print("R: ");
        Serial.println(R);
    }
    
    // calculate log10(R)
    R = log(R);
    
    if(DEBUG) {
        Serial.print("log(R): ");
        Serial.println(R);
    }
    
    // calculate temp
    double T = (1 / (A + B * R + C * R * R * R));
    
    if(DEBUG) {
        Serial.print("Temp: ");
        Serial.println(T);
        Serial.println();
    }
    
    // return temp
    return T;
}

// Returns temp in Celcius
double ThermistorProbe::getTempC(int pin, enum ProbeType probeType, bool smooth) {
    return getTempK(pin, probeType, smooth) - 273.15;
}

// Return temp in Fahrenheit
double ThermistorProbe::getTempF(int pin, enum ProbeType probeType, bool smooth) {
    return ((getTempC(pin, probeType, smooth) * 9.0) / 5.0 + 32.0);
}
