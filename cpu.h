#ifndef CPU_H
#define CPU_H

#include <Arduino.h>

#define ADD_BUS_WIDTH 16
#define DATA_BUS_WIDTH 8
#define MEMORY_SIZE 1024

#define MODE_PIN 2
#define ADDRESS_PIN 23
#define DATA_PIN 22

#define E 8
#define Q 9

/*class MemoryBus {
    
};*/

bool getE();
bool getQ();

class Memory {
    private:
        bool readMode;
        int addressBus[ADD_BUS_WIDTH];
        byte memory[MEMORY_SIZE];
        
    public:
        Memory();
        void zero();
        unsigned short readAddress();
        bool getReadMode();
        byte write(unsigned short address, byte data);
        byte read(unsigned short address);
        void printAddress(short address);
};

class DataBus {
    private:
        int dataBus[DATA_BUS_WIDTH];
        
    public:
        DataBus();
        void setMode(int mode);
        byte read();
        void write(byte data);
};

#endif
