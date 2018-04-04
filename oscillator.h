#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <Arduino.h>

#ifdef __AVR_ATmega2560__
    //const byte CLOCKOUT = 11;
#define CLOCKOUT 11
#else
    //const byte CLOCKOUT = 9;
#define CLOCKOUT 9
#endif

#define in_range(l, h, v) (l) <= (v) && (h) > (v)

//void test();
class Oscillator {
    private:
    public:
        //static void init(int freq);
        Oscillator(int freq);
        static int divisor(int freq);
};

#endif
