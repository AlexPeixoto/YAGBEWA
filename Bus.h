#pragma once

#include <PPU/PPU.h>
#include <CPU/LR35902.h>
#include <Memory/Cartridge/RomManager.h>
#include <Memory/MemoryMap.h>

//Probably BUS is not the best name to call this.
//But this is the "glue code" that call all the main operations (cpu tick, ppu tick, timer update and interruption check)
class Bus {
private:
	//Cpu, PPU, APU and cartridge are public here as the buss just connects them.

	//Has to be moved to private later
	//Memory writing operations can trigger interruptions.
	//This has to come before cpu and cartridge to ensure the ordering of the object creation
	
	uint16_t inputClockSelect;
    CPU::LR35902 cpu;
    
	void updateTimerValue();
	void clockUpdate(uint16_t ticks);
	void performInterruption();

public:
	Memory::Map memoryMap;
	Memory::Cartridge::RomManager cartridge;
    Bus ();
    ~Bus ();

	void runCycle();
};