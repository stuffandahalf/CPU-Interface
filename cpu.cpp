#include "cpu.h"

CPU::CPU() {
    this->memory = new byte[MEMSIZE];
    this->memorybus = new MemoryBus();
    this->databus = new DataBus();
    
    this->clearMemory();
    this->setInstructions();
    //delay(2000);
    //this->reset();
    //attachInterrupt(digitalPinToInterrupt(RESET_IN), resetWrapper, CHANGE);
    //this->reset();
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

void CPU::setByte(address addr, byte data) {
    this->memory[addr] = data;
}

void CPU::setBytes(address start, int bytes, byte *data) {
    for (int i = 0; i < bytes; i++) {
        /*Serial.print(start + i, HEX);
        Serial.print(":\t");
        Serial.println(data[i], HEX);*/
        //this->memory[start + i] = data[i];
        this->setByte(start + i, data[i]);
        //Serial.println(this->memory[start + i], HEX);
    }
}

byte CPU::getByte(address addr) {
    return this->memory[addr];
}

void CPU::setInstructions() {
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
    
    this->setBytes(0x0000, 9, inst);
    this->setBytes(0x0080, 3, data);
    this->setBytes(0xFFFE - 0xFC00, 2, reset);
    //this->setBytes(1022, 2, reset);
    
    //Serial.println("Instructions set");
    //this->printAddressRange(0x0000, 0x0009);
    //this->printAddressRange(0x0080, 0x0083);
    //cpu->printAddressRange(0xFFFE, 0xFFFF);
    //this->printAddress(1022);
    //this->printAddress(1023);
    //cpu->printAddressRange(0xFFFE, 0x10000);
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

#define is_instruction (addr >= 0 && addr < 1024) || addr == 0x3FE || addr == 0x3FF

void memoryHandler() {
    //Serial.println("Clock changed");
    //Serial.println("C");
    bool read = clock & mem_mode;
    bool write = clock & !mem_mode;
    
    address raw_addr = cpu->getMemoryBus()->getAddress();
    //cpu->printAddress(raw_addr);
    //Serial.println(raw_addr, HEX);
    //cpu->printAddress(0x0082);
    if (raw_addr >= 0xFC00 && raw_addr <= 0xFFFF) {
        //Serial.println(raw_addr, HEX);
        buf->add(raw_addr);
        address addr = raw_addr - 0xFC00;
        /*if (is_instruction) {
            //Serial.println("1");
            cpu->printAddress(addr);
        }*/
        if (cpu->getByte(0x0082)) {
            digitalWrite(LED, HIGH);
        }
        //cpu->printAddress(0xFFFE - 0xFC00);
        //cpu->printAddress(0x3FE);
        //cpu->printAddress(addr);
        //address addr = cpu->getMemoryBus()->getAddress() - 0xFC00;
        //Serial.println(addr, HEX);
        //Serial.println(addr, HEX);
        //cpu->printAddress(addr);
        byte data;
        
        if (read & !write) {
        //    Serial.println("read");
        //    data = cpu->getMemory()[addr];
            data = cpu->getByte(addr);
            cpu->getDataBus()->write(data);
        //    
        }
        else if (!read & write) {
            data = cpu->getDataBus()->read();
            //cpu->getMemory()[addr] = data;
            cpu->setByte(addr, data);
        }
        //else {
        //    //Serial.println("what is this");
        //}
    }
}

void resetWrapper() {
    if (!digitalRead(RESET_IN)) {
        cpu->reset();
    }
}

void changeTest() {
    Serial.println("Clock changed");
}
