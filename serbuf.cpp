#include "serbuf.h"

SerBuf::SerBuf() {
    this->head = 0;
    this->tail = 0;
    this->buffer = new address[MEMSIZE * 2];
}

void SerBuf::incTail() {
    this->tail++;
    if (this->tail > MEMSIZE * 2) {
        this->tail = 0;
    }
}

void SerBuf::incHead() {
    this->head++;
    if(this->head > MEMSIZE * 2) {
        this->head = 0;
    }
}

void SerBuf::add(address addr) {
    this->buffer[this->tail] = addr;
    this->incTail();
}

bool SerBuf::hasNext() {
    return this->head != this->tail;
}

void SerBuf::printNext() {
    Serial.println(this->buffer[head], HEX);
    this->incHead();
}
