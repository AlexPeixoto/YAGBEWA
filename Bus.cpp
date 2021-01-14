#include <Bus.h>

namespace{
	const uint32_t FREQUENCY = 4194304;
	const uint32_t FPS = 60;
	//How many cycles we can process on each frame
	const uint32_t CYCLES_PER_FRAME = FREQUENCY/FPS;
	//DIV register is updated at a different pace, so we use it to properly update it
	const uint32_t DIV_REGISTER_INCREMENT = 16384;
	const uint16_t IE_ADDR = 0xFFFF;
	const uint16_t IF_ADDR = 0xFF0F;

	const uint16_t INTERRUPTION_TARGET[] = {0x40, 0x48, 0x50, 0x58, 0x60};
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
		performInterruption();
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

//This does *NOT* implement the obscure behaviour of the DIV
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

void Bus::performInterruption() {
	if(!CPU::LR35902::interruptionsEnabled())
		return;
	//RevertPC interruption bug is handled directly on executeNext;
	if(CPU::LR35902::getHaltType() == CPU::HaltType::NoInterruption){
		//Instead of jumping we just continue here.
		CPU::LR35902::resetHalt();
		return;
	}
	//If there is any interruption enabled, and if there was any interruption triggered
	const uint8_t _IE = memoryMap[IE_ADDR];
	const uint8_t _IF = memoryMap[IF_ADDR];
	if(_IE != 0 && _IF != 0){
		//Disable interruption
		CPU::LR35902::disableInterruptions();
		//Store PC on stack
		cpu.pushPC();
		uint16_t interruptionDestinationAddress=0;
		//Look at the 5 possible bits and check if any is both enabled and checked
		//Interruptuion priority goes from the highest bit to the lowest
		for(int x=4; x>=0; x--){
			if((_IE >> x) & 0x1Ul && (_IF >> x) & 0x1Ul){
				cpu.setPC(INTERRUPTION_TARGET[x]);
				//Reset IF flag
				memoryMap[IF_ADDR] &= ~(1UL << x);
			}
		}
	}
}