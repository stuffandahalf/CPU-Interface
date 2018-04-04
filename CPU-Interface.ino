#include "cpu.h"
#include "oscillator.h"

Address *a;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    a = new Address();
    //Oscillator::init(4);
    new Oscillator(4);
}

void loop() {
    // put your main code here, to run repeatedly:
    a->getAddress();
    a->printAddress();
}
