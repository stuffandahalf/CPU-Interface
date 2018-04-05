#include "cpu.h"

bool getE() {
    return digitalRead(E);
}

Memory::Memory() {
    this->readMode = this->getReadMode();
    this->zero();
    for (int b = 0; b < ADD_BUS_WIDTH; b++) {
        this->addressBus[b] = ADDRESS_PIN + b * 2;
        pinMode(this->addressBus[b], INPUT);
    }
}

void Memory::zero() {
    for (int a = 0; a < MEMORY_SIZE; a++) {
        this->memory[a] = 0;
    }
}

unsigned short Memory::readAddress() {
    unsigned short address = 0;
    for (int b = ADD_BUS_WIDTH - 1; b >= 0; b--) {
        address += digitalRead(addressBus[b]);
        if (b) {
            address << 1;
        }
    }
    return address;
}

bool Memory::getReadMode() {
    /*bool oldMode = this->read;
    this->read = digitalRead(MODE_PIN);
    Serial.println(this->read);
    if (oldMode != this->read) {
        if (this->read) {
            
        }
    }*/
    return digitalRead(MODE_PIN);
}

byte Memory::write(unsigned short address, byte data) {
    byte oldByte = this->memory[address];
    this->memory[address] = data;
    
    /*Serial.print("Wrote 0x");
    Serial.print(data, HEX);
    Serial.print(" to address 0x");
    Serial.print(address, HEX);
    Serial.println(".");*/
    
    return oldByte;
}

byte Memory::read(unsigned short address) {
    byte data = this->memory[address];
    
    /*Serial.print("Read 0x");
    Serial.print(data, HEX);
    Serial.print(" from address 0x");
    Serial.print(address, HEX);
    Serial.println(".");*/
    
    return data;
}

void Memory::printAddress(short address) {
    if (address < 0x10) {
        Serial.print("000");
    }
    else if (address < 0x100) {
        Serial.print("00");
    }
    else if (address < 0x1000) {
        Serial.print("0");
    }
    Serial.println(address, HEX);
}



DataBus::DataBus() {
    for (int b = 0; b < DATA_BUS_WIDTH; b++) {
        this->dataBus[b] = DATA_PIN + b * 2;
        pinMode(this->dataBus[b], INPUT);
    }
}

void DataBus::setMode(int mode) {
    for (int b = 0; b < DATA_BUS_WIDTH; b++) {
        pinMode(this->dataBus[b], mode);
    }
}

byte DataBus::read() {
    setMode(INPUT);
    byte data = 0;
    for (int b = DATA_BUS_WIDTH - 1; b >= 0; b--) {
        data += digitalRead(this->dataBus[b]);
        if (b) {
            data << 1;
        }
    }
    return data;
}

void DataBus::write(byte data) {
    setMode(OUTPUT);
    bool bits[8];
    for(int i = 0; i < 8; i++) {
        bits[i] = (data >> i) & 1;
        Serial.print(bits[i]);
        digitalWrite(this->dataBus[i], bits[i]);
    }
    Serial.println();
}
