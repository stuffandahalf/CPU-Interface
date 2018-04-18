#include "cpu.h"

CPU::CPU() {
    this->memory = new byte[MEMSIZE];
    this->memorybus = new MemoryBus();
    this->databus = new DataBus();
    
    this->clearMemory();
    setInstructions();
    delay(1000);
    
    attachInterrupt(digitalPinToInterrupt(CLOCK_IN), memoryHandler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RESET_IN), resetWrapper, CHANGE);
    this->reset();
    //digitalWrite(RESET, LOW);
    //delay(1000);
    //this->reset();
    //digitalWrite(RESET, HIGH);
}

void CPU::clearMemory() {
    for (int i = 0; i < MEMSIZE; i++) {
        this->memory[i] = 0xFF;
    }
}

void CPU::reset() {
    digitalWrite(RESET_OUT, LOW);
    digitalWrite(LED, LOW);
    //delay(3000);
    Serial.println("CPU Reset");
    digitalWrite(LED, HIGH);
    digitalWrite(RESET_OUT, HIGH);
}

void CPU::printAddress(address addr) {
    Serial.print(addr, HEX);
    Serial.print(":\t");
    Serial.println(this->memory[addr], HEX);
}

void CPU::printAddressRange(address from, address to) {
    for (int addr = from; addr < to; addr++) {
        this->printAddress(addr);
    }
}

void CPU::setBytes(address start, int bytes, byte *data) {
    for (int i = 0; i < bytes; i++) {
        /*Serial.print(start + i, HEX);
        Serial.print(":\t");
        Serial.println(data[i], HEX);*/
        this->memory[start + i] = data[i];
        //Serial.println(this->memory[start + i], HEX);
    }
}


byte *CPU::getMemory() {
    return this->memory;
}

MemoryBus *CPU::getMemoryBus() {
    return this->memorybus;
}

DataBus *CPU::getDataBus() {
    return this->databus;
}

void pin_init() {
    pinMode(CLOCK_IN, INPUT);
    pinMode(MEMMODE, INPUT);
    pinMode(RESET_OUT, OUTPUT);
    pinMode(RESET_IN, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
}

void setInstructions() {
    byte inst[] = {
        0xB6,       // LDA A
        0xFC,
        0x80,
        
        0xBB,       // ADDA B
        0xFC,
        0x81,
        
        0xB7,       // STA RES
        0xFC,
        0x82
    };
    
    byte data[] = {
        5,          // A
        5,          // B
        0           // RES
    };
    
    /* RESET VECTOR */
    byte reset[] = {
        0xFC,       // 0x0000
        0x00
    };
    
    cpu->setBytes(0x0000, 9, inst);
    cpu->setBytes(0x0080, 3, data);
    cpu->setBytes(0xFFFE - 0xFC00, 2, reset);
    
    Serial.println("Instructions set");
    cpu->printAddressRange(0x0000, 0x0009);
    cpu->printAddressRange(0x0080, 0x0083);
    //cpu->printAddressRange(0xFFFE, 0xFFFF);
    //cpu->printAddressRange(0xFFFE, 0x10000);
}

void memoryHandler() {
    bool read = clock & mem_mode;
    bool write = clock & !mem_mode;
    
    address raw_addr = cpu->getMemoryBus()->getAddress();
    //cpu->printAddress(addr);
    address addr = raw_addr - 0xFC00;
    if (read & !write) {
        
    }
    else if (!read & write) {
        
    }
}

void resetWrapper() {
    if (!digitalRead(RESET_IN)) {
        cpu->reset();
    }
}
