#include "cpu.h"

DataBus::DataBus() {
    this->databus = new byte[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
        this->databus[i] = DATA_PIN + 2 * i;
        pinMode(this->databus[i], INPUT);
    }
}

void DataBus::setMode(int mode) {
    for (int i = 0; i < DATA_SIZE; i++) {
        pinMode(this->databus[i], mode);
    }
}

byte DataBus::read() {
    this->setMode(INPUT);
    byte data = 0;
    for (int i = DATA_SIZE - 1; i >= 0; i--) {
        data += digitalRead(this->databus[i]);
        if (i) {
            data <<= 1;
        }
    }
    return data;
}

void DataBus::write(byte data) {
    this->setMode(OUTPUT);
    for (int i = 0; i < DATA_SIZE; i++) {
        digitalWrite(this->databus[i], (data >> i) & 1);
    }
}
