#include "cpu.h"
#include "oscillator.h"

#define LEDPIN 14

CPU *cpu;

void printTest();
void setInstructions();

void setup() {
    Serial.begin(115200);
    
    cpu = new CPU();
    //new Oscillator(4);
    
    setInstructions();
    
    pinMode(LEDPIN, OUTPUT);
    //digitalWrite(LEDPIN, LOW);
    
    //cpu->getMem()->printAddress(1023);
    //Serial.println(0x80 + 0xFC00, HEX);
    //Serial.println(cpu->getMem()->getAddress());
    delay(3000);
    //Serial.println(data->read());
    attachInterrupt(digitalPinToInterrupt(E), memoryHandler, CHANGE);
    //attachInterrupt(digitalPinToInterrupt(E), memoryHandler, RISING);
    //Serial.println(cpu->getMem()->getAddress());
    cpu->toggleHalt();
    //cpu->getDataBus()->write(0xFC);
}

void loop() {
    //Serial.println(cpu->getMem()->read(0x0082)/*, HEX*/);
    //cpu->getMem()->printAddress(0x0082);
    /*if (cpu->getMem()->read(0x0082) == 11) {
        digitalWrite(LEDPIN, HIGH);
    }*/
}

void setInstructions() {
    Memory *mem = cpu->getMem();
    
    mem->write(0x0000, 0xB6);     //LDA, 0x0080
    mem->write(0x0001, 0xFC);
    mem->write(0x0002, 0x80);
    
    mem->write(0x0003, 0xBB);     //ADDA, 0x0081
    mem->write(0x0004, 0xFC);
    mem->write(0x0005, 0x81);
    
    mem->write(0x0006, 0xB7);     //STA, 0x0082
    mem->write(0x0007, 0xFC);
    mem->write(0x0008, 0x82);
    
    mem->write(0x0080, 0x05);     //data 5 at address 0x0080
    mem->write(0x0081, 0x06);     //data 6 at address 0x0081
    mem->write(0x0082, 0x00);     //data location for result
    
    //mem->write(0xfffe, 0x00);   //reset vector
    //mem->write(0xffff, 0x00);
    mem->write(0xFFFE - 0xFC00, 0xFC);   //reset vector
    mem->write(0xFFFF - 0xFC00, 0x00);
    
    Serial.println("Instructions loaded");
    mem->printAddressRange(0x0000, 0x0009);
}
