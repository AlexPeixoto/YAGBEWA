#include <LR35902.h>
#include <Bus.h>

using namespace CPU;

LR35902::LR35902(Bus* bus) : bus(bus), mapping(*this) {
    registers.A = 0x11;
    registers.BC[0] = 0x01;
    registers.BC[1] = 0x00;
    registers.DE[0] = 0x00;
    registers.DE[1] = 0x08;
    registers.HL[0] = 0x00;
    registers.HL[1] = 0x7C;
    registers.F.Z = 0;
    registers.F.N = 0;
    registers.F.H = 0;
    registers.F.C = 0;
    registers.SP = 0xFFFE;
}

LR35902::~LR35902() {}

void LR35902::initPC(bool headless = false) {
    registers.PC = bus->memoryMap.getMemoryAt(headless ? 0x000 : 0x100);
    
    //abort();
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