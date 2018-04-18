#include "cpu.h"

byte mem[MEMSIZE];

byte addressbus[ADDRESS_SIZE];
byte databus[DATA_SIZE];

CPU *cpu;

void setup() {
    Serial.begin(115200);
    pin_init();
    cpu = new CPU();
    setInstructions();
    //cpu->reset();
    //delay(3000);
    //cpu->printAddressRange(0, 1024);
}

void loop() {
    
}

/*void initAddressBus() {
    for (int i = 0; i < ADDRESS_SIZE; i++) {
        addressbus[i] = ADDRESS_PIN + 2 * i;
        pinMode(addressbus[i], INPUT);
    }
}

void initDataBus() {
    for (int i = 0; i < DATA_SIZE; i++) {
        databus[i] = DATA_PIN + 2 * i;
        pinMode(databus[i], OUTPUT);
    }
}

unsigned short getAddress() {
    unsigned short address = 0;
    for (int i = ADDRESS_SIZE - 1; i >= 0; i--) {
        address += digitalRead(addressbus[i]);
    }
}*/

