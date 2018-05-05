#ifndef CPU_H
#define CPU_H

#include <Arduino.h>
#include "serbuf.h"

#define LED 13

/* 1kB of ram */
#define MEMSIZE 1024
#define MEMEND 0xFFFF
#define MEMSTART MEMEND - MEMSIZE
#define ADDRESS_SIZE 16
#define DATA_SIZE 8


#define MRDY 22
#define CLOCK_IN 2
//#define CLOCK_IN 3
//#define MEMMODE 3
#define MEMMODE 8
#define RESET_OUT 4

#define RESET_IN 21
#define ADDRESS_PIN 23
#define DATA_PIN 38

#define clock digitalRead(CLOCK_IN)
#define mem_mode digitalRead(MEMMODE)

typedef unsigned short address;

class MemoryBus {
    private:
        byte *addressbus;
    
    public:
        MemoryBus();
        
        address getAddress();
};

class DataBus {
    private:
        byte *databus;
    
    public:
        DataBus();
        
        void setMode(int mode);
        byte read();
        void write(byte data);
};

class CPU {
    private:
        byte *memory;
        MemoryBus *memorybus;
        DataBus *databus;
    
    public:
        CPU();
        
        void clearMemory();
        void reset();
        void setByte(address addr, byte data);
        void setBytes(address start, int bytes, byte data[]);
        byte getByte(address addr);
        void setInstructions();
        void printAddress(address addr);
        void printAddressRange(address from, address to);
        
        void setMRDY(byte state);
        
        byte *getMemory();
        MemoryBus *getMemoryBus();
        DataBus *getDataBus();
}

extern *cpu;
extern SerBuf *buf;

void pin_init();
void setInstructions();
void memoryHandler();
void resetWrapper();
void changeTest();

#endif
