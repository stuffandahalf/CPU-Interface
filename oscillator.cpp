#include "oscillator.h"

//static void Oscillator::init(int freq) {
Oscillator::Oscillator(int freq) {
    if (in_range(0, 8, freq) && (8 % freq == 0)) {
        pinMode(CLOCKOUT, OUTPUT);
        TCCR1A = bit(COM1A0);
        TCCR1B = bit(WGM12) | bit(CS10);
        // FIND THER VALUES
        //OCR1A = 8 / freq;
        // 4 MHz
        OCR1A = Oscillator::divisor(freq);
    }
}

int Oscillator::divisor(int freq) {
    switch (freq) {
        case 8:
            return 0;
        case 4:
            return 1;
        default:
            return -1;
    }
}
