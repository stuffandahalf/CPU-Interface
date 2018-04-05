#include "cpu.h"
#include "oscillator.h"

Memory *mem;
DataBus *databus;
bool e;

#define get_read (mem->getReadMode() & getClock())
#define get_write (!(mem->getReadMode() & mem->getReadMode()) & getClock())

void printTest();
void test();
void setInstructions();

void setup() {
    Serial.begin(115200);
    mem = new Memory();
    databus = new DataBus();
    new Oscillator(4);
    
    setInstructions();
    //test();
    
    e = getE();
    //Serial.println(data->read());
}

void loop() {
    if (mem->read(0xF002) != 20) {
    bool oldE = e;
    e = getE();
    if (e != oldE && e) {
        short address = mem->readAddress();
        Serial.println(address, HEX);
        byte data;
        switch (mem->getReadMode()) {
            //write to memory
            case 0:
                data = databus->read();
                mem->write(address, data);
                break;
            //read from memory
            case 1:
                data = mem->read(address);
                databus->write(data);
                break;
            default:
                break;
        }
    }
    }
    //mem->printAddress(mem->readAddress());
    //printTest();
    else{
    Serial.println(mem->read(0xF002), HEX);
    }
}

void printTest() {
    Serial.print(get_read);
    Serial.print('\t');
    Serial.print(get_write);
    Serial.print('\t');
    Serial.print(mem->readAddress());
    Serial.println();
}

void setInstructions() {
    mem->write(0xF000, 0xA);     //data 10 at address 0xF000
    Serial.println(mem->read(0xF000), HEX);
    mem->write(0xF001, 0xA);     //data 10 at address 0xF001
    mem->write(0xF002, 0x0);     //data location for result
    
    mem->write(0x0000, 0xB6);    //LDA, 0xF000
    mem->write(0x0001, 0xF0);
    mem->write(0x0002, 0x00);
    
    mem->write(0x0003, 0xBB);    //ADDA, 0xF001
    mem->write(0x0004, 0xF0);
    mem->write(0x0005, 0x01);
    
    mem->write(0x0006, 0xB7);    //STA, 0xF002
    mem->write(0x0007, 0xF0);
    mem->write(0x0008, 0x02);
    
    Serial.println("Instructions loaded");
}

void test() {
    int a = 5;
    Serial.println(a, BIN);
    //int b = 3 >> 1;
    Serial.println((a >> 2) & 1, BIN);
}
