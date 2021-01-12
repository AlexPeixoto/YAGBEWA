#pragma once

#include <CPU/LR35902.h>
#include <Memory/Cartridge/RomManager.h>
#include <Memory/MemoryMap.h>

class Bus {
private:
public:
	//Cpu, PPU, APU and cartridge are public here as the buss just connects them.

	//Has to be moved to private later
	//Memory writing operations can trigger interruptions.
	//This has to come before cpu and cartridge to ensure the ordering of the object creation
	Memory::Map memoryMap;

    CPU::LR35902 cpu;
    Memory::Cartridge::RomManager cartridge;

    Bus ();
    ~Bus ();

	void runCycle();
	void clockUpdate();

	void requestWrite(uint8_t val, uint16_t addr);

	Memory::Map& getMemoryMap(){
		return memoryMap;
	}

};