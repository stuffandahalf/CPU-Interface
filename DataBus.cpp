#include "cpu.h"

DataBus::DataBus() {
    this->databus = new byte[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
        this->databus[i] = DATA_SIZE + 2 * i;
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
    for (int i = DATA_SIZE - 1; i >= 0; i++) {
        
    }
}
