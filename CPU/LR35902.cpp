#include <LR35902.h>
#include <Bus.h>

using namespace CPU;

Registers LR35902::registers;
bool LR35902::stop = false;
uint8_t LR35902::extraCycles = 0;

LR35902::LR35902(Bus* bus) : bus(bus) {}

LR35902::~LR35902() {}


void LR35902::clock() {
    if(cycles == 0){
        //do its stuff
    }
    cycles--;
}