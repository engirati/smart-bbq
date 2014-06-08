// ThermistorProbe - Library for reading thermistor based temperature probes.
// Contributions and influence from @BDub and @avidan
// https://community.spark.io/t/thermistors-and-the-spark-core/1276

#ifndef ThermistorProbe_h
#define ThermistorProbe_h

#include "application.h"

class ThermistorProbe
{
    public:
        enum ProbeType{ET72, ET732};
        ThermistorProbe(double pur, int adc);
        ~ThermistorProbe();
        double getTempK(int pin, enum ProbeType probeType);
        double getTempC(int pin, enum ProbeType probeType);
        double getTempF(int pin, enum ProbeType probeType);
    private:
        double _pur, A, B, C;
        int _adc;
        enum ProbeType _probeType;
};

#endif
