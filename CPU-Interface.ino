#include "cpu.h"
#include "oscillator.h"

//Memory *mem;
//DataBus *databus;
CPU *cpu;
//bool e;

#define get_read (cpu->getMem()->getReadMode() & getE())
#define get_write (!(cpu->getMem()->getReadMode() & cpu->getMem()->getReadMode()) & getE())

//#define HALTPIN 6

void printTest();
void setInstructions();

void setup() {
    pinMode(HALTPIN, OUTPUT);
    digitalWrite(HALTPIN, LOW);
    Serial.begin(115200);
    //mem = new Memory();
    //databus = new DataBus();
    cpu = new CPU();
    cpu->getMem()->zero();
    new Oscillator(4);
    
    setInstructions();
    //test();
    Serial.print(0x0082, HEX);
    Serial.print(":\t");
    Serial.println(cpu->getMem()->read(0x0082)/*, HEX*/);
    delay(3000);
    //e = getE();
    //Serial.println(data->read());
    attachInterrupt(digitalPinToInterrupt(E), memoryHandler, CHANGE);
    
    digitalWrite(HALTPIN, HIGH);
}

void loop() {
    //Serial.println(cpu->getMem()->read(0x0082)/*, HEX*/);
}

void printTest() {
    Serial.print(get_read);
    Serial.print('\t');
    Serial.print(get_write);
    Serial.print('\t');
    Serial.print(cpu->getMem()->getAddress());
    Serial.println();
}

void setInstructions() {
    Memory *mem = cpu->getMem();
    mem->write(0x0080, 0x0A);     //data 10 at address 0x0080
    mem->write(0x0081, 0x0A);     //data 10 at address 0x0081
    mem->write(0x0082, 0x00);     //data location for result
    
    mem->write(0x0000, 0xB6);    //LDA, 0x0080
    mem->write(0x0001, 0x00);
    mem->write(0x0002, 0x80);
    
    mem->write(0x0003, 0xBB);    //ADDA, 0x0081
    mem->write(0x0004, 0x00);
    mem->write(0x0005, 0x81);
    
    mem->write(0x0006, 0xB7);    //STA, 0x0082
    mem->write(0x0007, 0x00);
    mem->write(0x0008, 0x82);
    
    Serial.println("Instructions loaded");
    mem->printAddressRange(0x0000, 0x0009);
}
