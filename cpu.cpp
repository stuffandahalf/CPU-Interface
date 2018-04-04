#include "cpu.h"

Address::Address() {
    for (int i = 0; i < ADD_BUS_WIDTH; i++) {
        address[i] = false;
        addressBus[i] = 22 + i * 2;
        pinMode(addressBus[i], INPUT);
    }
    Serial.println();
}

void Address::getAddress() {
    for (int i = 0; i < ADD_BUS_WIDTH; i++) {
        address[i] = digitalRead(addressBus[i]);
    }
}

void Address::printAddress() {
    for (int i = 0; i < ADD_BUS_WIDTH; i++) {
        Serial.print(this->address[i]);
    }
    Serial.println();
}
