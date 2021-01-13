#include <Bus.h>

namespace{
	const uint32_t FREQUENCY = 4194304;
	const uint32_t FPS = 60;
	//How many cycles we can process on each frame
	const uint32_t CYCLES_PER_FRAME = FREQUENCY/FPS;
	//DIV register is updated at a different pace, so we use it to properly update it
	const uint32_t DIV_REGISTER_INCREMENT = 16384;
}

Bus::Bus() : cpu(this), cartridge(this), memoryMap(this) {
	cpu.initPC();
	inputClockSelect = 1024;
}
Bus::~Bus () {}


//RunCycle happens on the Bus as here it is the coordinator of the whole thing.
void Bus::runCycle() {	
	uint32_t clock = 0;
	while(true){
	//Run 1 frame
	//while(clock < CYCLES_PER_FRAME){
		//This is to create a cycle acurrate emulation, where we "burn the cycles"
		//clock+=
		cpu.tick();
		//Interruptions
		//Timer
		updateTimerValue();
	//}
	}
	//Graphics here, as its not done per cycle
	//ppu.tick()

	//Here I should sleep for the remaining frame time
	//Another option is use an Update function via SDL or SFML and just call runCycle on it (as it will ensure proper pacing)
	clock = 0;
}

/*void RomManager::checkInterruptions(){

}*/

void Bus::updateTimerValue() {
	int8_t toDiv = memoryMap.read(0xFF07);
	if(toDiv & 0b00000100) {
		switch(toDiv) {
			case 0x00:
				inputClockSelect = 1024;
				break;
			case 0x01:
				inputClockSelect = 16;
				break;
			case 0x10:
				inputClockSelect = 64;
				break;
			case 0x11:
				inputClockSelect = 256;
				break;
			default:
				abort();
		}
	}
}
void Bus::clockUpdate() {
	//Isolated number of ticks for the timer
	static uint32_t clockTicks=0;
	
	if(clockTicks > 0 && (clockTicks % inputClockSelect) == 0){
		if(memoryMap[0xFF05] == 0xFF){
			memoryMap[0xFF05]=memoryMap[0xFF06];
			//TRIGGER INTERRUPT HERE
		}
		else
			memoryMap[0xFF05]++;
	}
	if(!CPU::LR35902::stopped() && clockTicks == 0xFF){
		clockTicks = 0;
		memoryMap[0xFF04]++;
		return;
	}
	if(clockTicks == 0xFF){
		clockTicks = 0;
		return;
	}
	clockTicks++;
}