#ifndef SERBUF_H
#define SERBUF_H

#include <Arduino.h>

typedef unsigned short address;

#define MEMSIZE 1024

class SerBuf {
    private:
        int head;
        int tail;
        address *buffer;
        
        
        void incTail();
        void incHead();
        
    public:
        SerBuf();
        void add(address addr);
        bool hasNext();
        void printNext();
};

#endif
