#include <Bus.h>
#include <bitset>

namespace{
	const uint16_t DIV_ADDR = 0xFF04;
	const uint16_t TIMA_ADDR = 0xFF05;
	const uint16_t TMA_ADDR = 0xFF06;
	const uint16_t TAC_ADDR = 0xFF07;
	const uint32_t FREQUENCY = 4194304;
	const uint32_t FPS = 60;
	//How many cycles we can process on each frame
	const uint32_t CYCLES_PER_FRAME = FREQUENCY/FPS;
	//DIV register is updated at a different pace, so we use it to properly update it
	const uint32_t DIV_REGISTER_INCREMENT = 16384;
	const uint32_t DIV_REGISTER_INCREMENT_PER_FRAME = DIV_REGISTER_INCREMENT/FPS;
}
Bus::Bus() : cpu(this), cartridge(this), memoryMap(this), ppu(this) {
}
Bus::~Bus () {}


//RunCycle happens on the Bus as here it is the coordinator of the whole thing.
void Bus::runCycle() {	
	//Cycles that have to be burned down from last iteration
	static uint64_t pendingCycles = 0;

	//"Global" clock
	uint32_t clock = pendingCycles; //pendingCycles;

	memoryMap.setButtonsDirections(buttons, directions);
		
	while(clock < CYCLES_PER_FRAME){
		uint32_t numberCyclesCurrent = 0;
		
		uint8_t cost = memoryMap.getAndTick4();
		if( cost == 0 &&  //Are we still paying for the DMA
			!cpu.stopped() &&  //Is the CPU stopped?
			//For revert we still continue execution, but PC will fail to increase
			(cpu.getHaltType() == CPU::HaltType::None || cpu.getHaltType() == CPU::HaltType::Revert))
		{

			cpu.enableInterruptionIfOnNext();
			//This is to create a cycle acurrate emulation, where we "burn the cycles"
			numberCyclesCurrent=cpu.tick();
			//No need to add memory cost, the DMA doest halt the CPU, it just take that many cycles to complete
			//So we dont calculate it, its the game's code job to swait for it to finish
			clock+=numberCyclesCurrent;
		} else {
			cost += 4;
		}
		if(memoryMap.triggerJOYP){
			memoryMap.triggerJOYP = false;
			setInterruptFlag(CPU::INTERRUPTIONS_TYPE::JOYP);
		}
		numberCyclesCurrent += cost;
		clock += cost;

		//We tick each clock individually (easier to control)
		for(int _clock=0; _clock < numberCyclesCurrent; _clock++){
			ppu.tick();	
			clockUpdate();
		}

		//4 ticks
		
		//Interruptions
		cpu.performInterruption();		
	}
	//Store remaining cycles to burn on next execution.
	pendingCycles = clock - CYCLES_PER_FRAME;
}

void Bus::setInterruptFlag(CPU::INTERRUPTIONS_TYPE type){
	cpu.setInterruptFlag(type);
}

//This does *NOT* implement the obscure behaviour of the DIV
//Also this is quite untested
void Bus::clockUpdate() {
	//Translate the clock select into what bit I should observe
	static uint8_t bitPosition[] = {9, 3, 5, 7};
	static bool lastCycle = false;
	if(cpu.stopped())
		return;
		
	memoryMap[DIV_ADDR]++;
	//Which bit we should mask? (use lookup table)
	uint16_t currentBitMask = 1UL << bitPosition[memoryMap[TAC_ADDR]&0x3];
	bool enabled = ((memoryMap[TAC_ADDR] & 0x4) == 0x4);
	bool currentCycle = (memoryMap[DIV_ADDR] & currentBitMask);
	currentCycle = currentCycle && enabled;
	//Falling edge
	if(!currentCycle && lastCycle){
		if(++memoryMap[TIMA_ADDR] == 0x00){
			memoryMap[TIMA_ADDR] = memoryMap[TMA_ADDR];
			cpu.setInterruptFlag(CPU::INTERRUPTIONS_TYPE::TIMER);
		}
	}
	lastCycle = currentCycle;
}

