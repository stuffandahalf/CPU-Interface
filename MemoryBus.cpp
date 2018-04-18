#include "cpu.h"

MemoryBus::MemoryBus() {
    this->addressbus = new byte[ADDRESS_SIZE];
    for (int i = 0; i < ADDRESS_SIZE; i++) {
        this->addressbus[i] = ADDRESS_PIN + 2 * i;
        pinMode(this->addressbus[i], INPUT);
    }
}

address MemoryBus::getAddress() {
    address addr = 0;
    for (int i = ADDRESS_SIZE - 1; i >= 0; i--) {
        addr += digitalRead(this->addressbus[i]);
        if (i) {
            addr <<= 1;
        }
    }
    return addr;
}
