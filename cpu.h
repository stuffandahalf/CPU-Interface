#ifndef CPU_H
#define CPU_H

#include <Arduino.h>

//#define ADD_BUS_WIDTH 16
#define ADD_BUS_WIDTH 8
#define DATA_BUS_WIDTH 8
#define MEMORY_SIZE 1024

#define MODE_PIN 8
#define ADDRESS_PIN 23
//#define DATA_PIN 22
#define DATA_PIN 39
#define HALTPIN 6

#define E 2
#define Q 3

/*class MemoryBus {
    
};*/

bool getE();
bool getQ();

class Memory {
    private:
        bool readMode;
        int addressbus[ADD_BUS_WIDTH];
        byte memory[MEMORY_SIZE];
        
    public:
        Memory();
        void zero();
        unsigned short getAddress();
        bool getReadMode();
        byte write(unsigned short address, byte data);
        byte read(unsigned short address);
        void printAddressRange(unsigned short from, unsigned short to);
        void printAddress(unsigned short address);
};

class DataBus {
    private:
        int databus[DATA_BUS_WIDTH];
        
    public:
        DataBus();
        void setMode(int mode);
        byte read();
        void write(byte data);
};

class CPU {
    private:
        Memory *mem;
        DataBus *databus;
        
    public:
        
        CPU();
        void memoryHandler();
        Memory *getMem();
        DataBus *getDataBus();
};

void memoryHandler();

#endif
