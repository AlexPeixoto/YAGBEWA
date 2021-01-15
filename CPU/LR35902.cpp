#include <LR35902.h>
#include <Bus.h>

using namespace CPU;

LR35902::LR35902(Bus* bus) : bus(bus), mapping(*this) {
    registers.A = 0x01;
    registers.BC._pair = 0x0013;
    registers.DE._pair = 0x00D8;
    registers.HL._pair = 0x014D;
    registers.F.Z = 1;
    registers.F.N = 0;
    registers.F.H = 1;
    registers.F.C = 1;
    registers.SP = 0xFFFE;
}

LR35902::~LR35902() {}

void LR35902::initPC() {
    registers.PC = bus->memoryMap.getMemoryAt(0x100);
}

void LR35902::setPC(uint16_t target) { 
    registers.PC = bus->memoryMap.getMemoryAt(target);
}

void LR35902::pushPC() {
    const ptrdiff_t index = (registers.PC - bus->memoryMap.getRomStart());
    mapping.push16(*this, bus->memoryMap, index);
}

void LR35902::popPC() {
    registers.PC = bus->memoryMap.getMemoryAt(mapping.pop16(*this, bus->memoryMap));
}

uint16_t LR35902::tick() {
    //do its stuff
    uint16_t val = mapping.executeNext(*this, bus->memoryMap);
    //Move to next opcode, if there was no operation that changed PC
    if(!changedPC){
        registers.PC++;
    }
    changedPC = false;
    return val;
}