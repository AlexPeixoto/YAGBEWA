#include <LR35902.h>
#include <Bus.h>

using namespace CPU;

namespace{
	const uint16_t IE_ADDR = 0xFFFF;
	const uint16_t IF_ADDR = 0xFF0F;

	const uint16_t INTERRUPTION_TARGET[] = {0x40, 0x48, 0x50, 0x58, 0x60};
}

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

void LR35902::setInterruptFlag(INTERRUPTIONS_TYPE type) {
    bus->memoryMap[IF_ADDR] |= (1UL << static_cast<int>(type));
}

bool LR35902::isInterruptionPending() {
	const uint8_t _IE = bus->memoryMap[IE_ADDR];
	const uint8_t _IF = bus->memoryMap[IF_ADDR];
	return ((_IF & _IE) & 0x1F);
}

//This should be moved to the CPU
void LR35902::performInterruption() {
	const uint8_t _IE = bus->memoryMap[IE_ADDR];
	const uint8_t _IF = bus->memoryMap[IF_ADDR];

	//Specific unhalt mechanism if we have an interruption to be served
    //As per documentation and some tests we unhalt even if there is no matching IE
	if(_IF & 0x1F){
		resetHalt();
		resume();
	} else {
		//No interruption to serve, so lets get out
		return;
	}

	//We undo the halt if _IF is set even if interrupts are not enabled
	if(!interruptionsEnabled())
		return;

	//RevertPC interruption bug is handled directly on executeNext.
	//If an interruption happens, and the HALT was triggered with disabled interruptions
	//We just disable halt.
	if(getHaltType() == CPU::HaltType::NoInterruption){
		return;
	}

	//Look at the 5 possible bits and check if any is both enabled and checked
	//Interruptuion priority goes from the highest bit to the lowest
	for(int x=4; x>=0; x--){
		if((_IE >> x) & 0x1 && (_IF >> x) & 0x1){
			//Disable interruption
			disableInterruptions();

			//Store PC on stack
			//Have in mind that here the PC is already incremented, so no need to increment before push
			pushPC();
            //Move to the interruption target
			setPC(INTERRUPTION_TARGET[x]);

			//Reset IF flag (we DO NOT reset the IE flag here)
			bus->memoryMap[IF_ADDR] &= ~(1UL << x);
			//Stop here, we serve this interruption, once it finishes we serve
			//the next one (if we just set the PC twice we will only serve the one)
			//with the lowest priority
			return;
		}
	}
}