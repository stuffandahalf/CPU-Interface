#include "cpu.h"

bool getE() {
    return digitalRead(E);
}

Memory::Memory() {
    this->readMode = this->getReadMode();
    this->zero();
    for (int b = 0; b < ADD_BUS_WIDTH; b++) {
        this->addressbus[b] = ADDRESS_PIN + b * 2;
        pinMode(this->addressbus[b], INPUT);
    }
}

void Memory::zero() {
    for (int a = 0; a < MEMORY_SIZE; a++) {
        this->memory[a] = 0;
    }
}

unsigned short Memory::getAddress() {
    unsigned short address = 0;
    //for (int b = ADD_BUS_WIDTH - 1; b >= 0; b--) {
    for (int b = 0; b < ADD_BUS_WIDTH; b++) {
        address += digitalRead(addressbus[b]);
        if (b) {
            address = address << 1;
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

void Memory::printAddressRange(unsigned short from, unsigned short to) {
    for (int i = from; i < to; i++) {
        Serial.print(i, HEX);
        Serial.print(":\t");
        Serial.println(this->memory[i], HEX);
    }
}

void Memory::printAddress(unsigned short address) {
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
        this->databus[b] = DATA_PIN + b * 2;
        pinMode(this->databus[b], INPUT);
    }
}

void DataBus::setMode(int mode) {
    for (int b = 0; b < DATA_BUS_WIDTH; b++) {
        pinMode(this->databus[b], mode);
    }
}

byte DataBus::read() {
    setMode(INPUT);
    byte data = 0;
    for (int b = DATA_BUS_WIDTH - 1; b >= 0; b--) {
        data += digitalRead(this->databus[b]);
        if (b) {
            data = data << 1;
        }
    }
    return data;
}

void DataBus::write(byte data) {
    setMode(OUTPUT);
    bool bits[8];
    for(int i = 0; i < 8; i++) {
        bits[i] = (data >> i) & 1;
        //Serial.print(bits[i]);
        digitalWrite(this->databus[i], bits[i]);
    }
    //Serial.println();
}

CPU::CPU() {
    this->mem = new Memory();
    this->databus = new DataBus();
}

Memory *CPU::getMem() {
    return this->mem;
}

DataBus *CPU::getDataBus() {
    return this->databus;
}

extern CPU *cpu;

void memoryHandler() {
    //static bool eState = getE();
    //Serial.println("clock changed state");
    bool read = (cpu->getMem()->getReadMode() & getE());
    byte data;
    unsigned short address = cpu->getMem()->getAddress();
    //Serial.println(address);
    if (read) {
        data = cpu->getMem()->read(address);
        cpu->getDataBus()->write(data);
    }
    else {
        data = cpu->getDataBus()->read();
        Serial.println(address, HEX);
        Serial.println(data, HEX);
        cpu->getMem()->write(address, data);
    }
    /*if (cpu->getMem()->read(0x0082))
    {
        digitalWrite(HALTPIN, LOW);
    }*/
}
