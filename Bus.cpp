#include <Bus.h>
#include <bitset>

namespace{
	const uint32_t FREQUENCY = 4194304;
	const uint32_t FPS = 60;
	//How many cycles we can process on each frame
	const uint32_t CYCLES_PER_FRAME = FREQUENCY/FPS;
	//DIV register is updated at a different pace, so we use it to properly update it
	const uint32_t DIV_REGISTER_INCREMENT = 16384;
	const uint32_t DIV_REGISTER_INCREMENT_PER_FRAME = DIV_REGISTER_INCREMENT/FPS;
}
Bus::Bus() : cpu(this), cartridge(this), memoryMap(this), ppu(this) {
	inputClockSelect = 1024;
}
Bus::~Bus () {}


//RunCycle happens on the Bus as here it is the coordinator of the whole thing.
void Bus::runCycle() {	
	//Debug
	static uint64_t totalCycles = 0;
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
			totalCycles+=numberCyclesCurrent;
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
		}

		//Read the TAC here
		updateTimerValue();
		clockUpdate(numberCyclesCurrent);

		//Interruptions
		cpu.performInterruption();		
	}
	//Store remaining cycles to burn on next execution.
	pendingCycles = clock - CYCLES_PER_FRAME;
}

//Left timer here for simplicity.
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
	cpu.setInterruptFlag(type);
}

//This does *NOT* implement the obscure behaviour of the DIV
//Also this is quite untested
void Bus::clockUpdate(uint16_t ticks) {
	//Isolated number of ticks for the timer
	static uint32_t clockTicks=0;
	//Isolated number of ticks for the "real TIMER";
	static uint32_t clockTicksReal=0;
	if(cpu.stopped()){
		clockTicks = 0;	
		return;
	} else {
		clockTicks += ticks;
		clockTicksReal += ticks;
	}
	//Every time that the clock reaches the "selected update mode"
	//We increase FF05.
	if(clockTicks > inputClockSelect){
		if(memoryMap[0xFF05] >= 0xFF){
			memoryMap[0xFF05]=memoryMap[0xFF06];
			setInterruptFlag(CPU::INTERRUPTIONS_TYPE::TIMER);
			clockTicks = 0;
		}
		//Is Timer enabled?
		else if((memoryMap[0xFF07] & 0x4) == 0x4){
			memoryMap[0xFF05]++;
		}
	}
	
	if(!cpu.stopped()){
		//We increment but mod it by the number of clocks per second
		memoryMap[0xFF04] += (clockTicksReal%DIV_REGISTER_INCREMENT_PER_FRAME == 0)%DIV_REGISTER_INCREMENT;
	}
}

