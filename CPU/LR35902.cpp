#include <LR35902.h>
#include <Bus.h>

using namespace CPU;

Registers LR35902::registers;
bool LR35902::stop = false;
bool LR35902::halt = false;
bool LR35902::enableInterruptions = false;
uint8_t LR35902::extraCycles = 0;

LR35902::LR35902(Bus* bus) : bus(bus) {
    LR35902::registers.A = 0x01;
    LR35902::registers.BC._pair = 0x0013;
    LR35902::registers.DE._pair = 0x00D8;
    LR35902::registers.HL._pair = 0x014D;
    LR35902::registers.F.Z = 1;
    LR35902::registers.F.N = 0;
    LR35902::registers.F.H = 1;
    LR35902::registers.F.C = 1;
    LR35902::registers.SP = 0xFFFE;
}

LR35902::~LR35902() {}


void LR35902::clock() {
    if(cycles == 0){
        //do its stuff
    }
    cycles--;
}