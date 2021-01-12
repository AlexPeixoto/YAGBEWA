#include <Bus.h>

namespace{
	const uint32_t FREQUENCY = 4194304;
	const uint32_t FPS = 60;
	//How many cycles we can process on each frame
	const uint32_t CYCLES_PER_FRAME = FREQUENCY/FPS;
	//DIV register is updated at a different pace, so we use it to properly update it
	const uint32_t DIV_REGISTER_INCREMENT = 16384;
}

Bus::Bus() : cpu(this), cartridge(this) {
}
Bus::~Bus () {}



void Bus::runCycle() {
	//first ensure that we point to the correct address
	cpu.initPC();
	uint32_t clock = 0;
	while(true){
	//Run 1 frame
	//while(clock < CYCLES_PER_FRAME){
		//This is to create a cycle acurrate emulation, where we "burn the cycles"
		clock+=cpu.tick();
		//Interruptions
		//Timer
	//}
	}
	//Graphics here, as its not done per cycle
	//ppu.tick()


	//Here I should sleep for the remaining frame time
	//Another option is use an Update function via SDL or SFML and just call runCycle on it (as it will ensure proper pacing)
	clock = 0;
}

//Maybe pass write calls from CPU to bus and here I decide to which component I forward it to?
void Bus::requestWrite(uint8_t val, uint16_t addr){
	memoryMap.write(val, addr);
}

void Bus::clockUpdate() {
	//timer.setDivValue(clock/DIV_REGISTER_INCREMENT);
	//uint32_t toDiv = cpu.memMap.read(0xFF07); THIS IS WRONG
	// Bit  2   - Timer Enable
 	//Bits 1-0 - Input Clock Select
    //        00: CPU Clock / 1024 (DMG, CGB:   4096 Hz, SGB:   ~4194 Hz)
    //        01: CPU Clock / 16   (DMG, CGB: 262144 Hz, SGB: ~268400 Hz)
    //        10: CPU Clock / 64   (DMG, CGB:  65536 Hz, SGB:  ~67110 Hz)
    //        11: CPU Clock / 256  (DMG, CGB:  16384 Hz, SGB:  ~16780 Hz)
	//if(toDiv)
	//uint32_t tima = clock/toDiv;
	//bool overflow = tima > 0xFF;
	//timer.updateTima(overflow ? 0 : tima);
	//timer.setTMA(overflow);
	/*
	if(stop){
		timer.zeroDiv();
	}
	*/
}