#include <LR35902.h>
#include <Bus.h>

using namespace CPU;

Registers LR35902::registers;
bool LR35902::stop = false;
bool LR35902::halt = false;
bool LR35902::changedPC = false;

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

void LR35902::initPC() {
    LR35902::registers.PC = bus->memoryMap.getMemoryAt(0x100);
}

void LR35902::setPC(uint16_t target) { 
    LR35902::registers.PC = bus->memoryMap.getMemoryAt(target);
}

void LR35902::pushPC() {
    const ptrdiff_t index = (LR35902::registers.PC - bus->memoryMap.getRomStart());
    mapping.push16(bus->memoryMap, index);
}

void LR35902::popPC() {
    LR35902::registers.PC = bus->memoryMap.getMemoryAt(mapping.pop16(bus->memoryMap));
}

uint16_t LR35902::tick() {
    //do its stuff
    uint16_t val = mapping.executeNext(bus->memoryMap);
    //Move to next opcode, if there was no operation that changed PC
    if(!changedPC){
        LR35902::registers.PC++;
    }
    changedPC = false;
    return val;
}