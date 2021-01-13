#pragma once

#include <CPU/LR35902.h>
#include <Memory/Cartridge/RomManager.h>
#include <Memory/MemoryMap.h>

class Bus {
private:
	//Cpu, PPU, APU and cartridge are public here as the buss just connects them.

	//Has to be moved to private later
	//Memory writing operations can trigger interruptions.
	//This has to come before cpu and cartridge to ensure the ordering of the object creation
	
	uint16_t inputClockSelect;
    CPU::LR35902 cpu;
    
	void updateTimerValue();
	void clockUpdate();

public:
	Memory::Map memoryMap;
	Memory::Cartridge::RomManager cartridge;
    Bus ();
    ~Bus ();

	void runCycle();
};