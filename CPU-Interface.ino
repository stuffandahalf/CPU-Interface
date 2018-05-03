#include "serbuf.h"
#include "cpu.h"
#include "oscillator.h"

//byte mem[MEMSIZE];

//byte addressbus[ADDRESS_SIZE];
//byte databus[DATA_SIZE];

CPU *cpu;
//SerBuf *buf;

void setup() {
    Serial.begin(9600);
    pin_init();
    //buf = new SerBuf();
    cpu = new CPU();
    new Oscillator(4);
    attachInterrupt(digitalPinToInterrupt(CLOCK_IN), memoryHandler, CHANGE);
    //attachInterrupt(digitalPinToInterrupt(CLOCK_IN), changeTest, CHANGE);
    //delay(3000);
    //cpu->printAddressRange(0, 1024);
}

void loop() {
    //Serial.println(cpu->getMemory()[0x0082], HEX);
    /*if (buf->hasNext()) {
        buf->printNext();
    }*/
    //cpu->printAddress(0x0082);
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

