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

Bus::Bus() : cpu(this), cartridge(this), memoryMap(this), ppu(this) {
	cpu.initPC();
	inputClockSelect = 1024;
}
Bus::~Bus () {}


//RunCycle happens on the Bus as here it is the coordinator of the whole thing.
void Bus::runCycle() {	
	uint16_t clock = 0;
	//uint32_t pending = 0;
	while(true){
	//Run 1 frame
	//while(clock < CYCLES_PER_FRAME){
		//Check for halt here

		//Burn the cycles
		if(clock > 0){
			clock--;
			continue;
		}

		//For revert we still continue execution, but PC will fail to increase
		if(cpu.getHaltType() == CPU::HaltType::None || cpu.getHaltType() == CPU::HaltType::Revert)
		{
			cpu.enableInterruptionIfOnNext();

			//This is to create a cycle acurrate emulation, where we "burn the cycles"
			clock=cpu.tick();	
		}
		//Graphics here, IT IS DONE with the CPU, the renderFrame function is once per frame
		ppu.tick(clock);
		//Timer, we use pending here
		updateTimerValue();
		clockUpdate(clock);
		//Interruptions
		performInterruption();
		//renderFrame()
	//}
	}
	

	//I use an Update function via SDL or SFML and just call runCycle on it (as it will ensure proper pacing)
	//clock = 0;
}

/*void RomManager::checkInterruptions(){

}*/

void Bus::updateTimerValue() {
	int8_t toDiv = memoryMap.read(0xFF07);
	if(toDiv & 0b00000100) {
		switch(toDiv & 0b00000011) {
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
		}
	}
}

void Bus::setInterruptFlag(CPU::INTERRUPTIONS_TYPE type){
	memoryMap[IF_ADDR] |= (1UL << static_cast<int>(type));
}

//This does *NOT* implement the obscure behaviour of the DIV
void Bus::clockUpdate(uint16_t ticks) {
	//Isolated number of ticks for the timer
	static uint32_t clockTicks=0;
	clockTicks+=ticks;
	
	//Every time that the clock reaches the "selected update mode"
	//We increase FF05.
	if(clockTicks > inputClockSelect){
		if(memoryMap[0xFF05] == 0xFF){
			memoryMap[0xFF05]=memoryMap[0xFF06];
			setInterruptFlag(CPU::INTERRUPTIONS_TYPE::TIMER);
			clockTicks-=inputClockSelect;
		}
		else
			memoryMap[0xFF05]++;
	}
	if(!cpu.stopped() && clockTicks == 0xFF){
		clockTicks = 0;
		memoryMap[0xFF04]++;
		return;
	}

	//Just reset the clock (for safekeeping),
	//probably not necessary
	if(clockTicks >= 0xFF){
		clockTicks = 0;
		return;
	}
}

void Bus::performInterruption() {
	if(!cpu.interruptionsEnabled())
		return;
	//std::cout << "Yay?" << std::endl;

	//Reset halt so CPU can continue to execute instructions
	cpu.resetHalt();

	//RevertPC interruption bug is handled directly on executeNext.
	//If an interruption happens, and the HALT was triggered with disabled interruptions
	//We just disable halt.
	if(cpu.getHaltType() == CPU::HaltType::NoInterruption){
		//Instead of jumping we just continue here.
		return;
	}

	//If there is any interruption enabled, and if there was any interruption triggered
	const uint8_t _IE = memoryMap[IE_ADDR];
	const uint8_t _IF = memoryMap[IF_ADDR];
	if(_IE != 0 && _IF != 0){
		//Disable interruption
		cpu.disableInterruptions();

		//Store PC on stack
		//Have in mind that here the PC is already incremented, so no need to increment before push
		cpu.pushPC();

		//Look at the 5 possible bits and check if any is both enabled and checked
		//Interruptuion priority goes from the highest bit to the lowest
		for(int x=4; x>=0; x--){
			if((_IE >> x) & 0x1Ul && (_IF >> x) & 0x1Ul){
				std::cout << "Interruption triggered" << std::endl;
				cpu.setPC(INTERRUPTION_TARGET[x]);
				//Reset IF flag
				memoryMap[IF_ADDR] &= ~(1UL << x);
				//Stop here, we serve this interruption, once it finishes we serve
				//the next one (id we just set the PC twice we will only serve the one)
				//with the lowest priority
				return;
			}
		}
	}
}