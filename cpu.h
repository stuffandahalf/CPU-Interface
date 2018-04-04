#ifndef CPU_H
#define CPU_H

#include <Arduino.h>

#define ADD_BUS_WIDTH 16
#define DATA_BUS_WIDTH 8
#define MEMORY_SIZE 1024

class Address {
    private:
        bool address[ADD_BUS_WIDTH];
        int addressBus[ADD_BUS_WIDTH];
        
    
    public:
        Address();

        void getAddress();
        void printAddress();
};

class Memory {
    private:
        int addressBus[ADD_BUS_WIDTH];
        byte memory[MEMORY_SIZE];
    public:
        
};

#endif
