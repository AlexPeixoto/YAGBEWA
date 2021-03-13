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
	
	CPU::LR35902 cpu;
	PPU::Core ppu;
	uint8_t buttons = 0;
	uint8_t directions = 0;
    
	void clockUpdate();

public:
	Memory::Map memoryMap;
	Memory::Cartridge::RomManager cartridge;
    Bus ();
    ~Bus ();

	void initCPU(){ cpu.initPC(cartridge.isHeadless());}
	void setButtons(uint8_t buttons){this->buttons = buttons;}
	void setDirections(uint8_t directions){this->directions = directions;}

	uint8_t getButtons(){return buttons;}
	uint8_t getDirections(){return directions;}

	void runCycle();
	void setInterruptFlag(CPU::INTERRUPTIONS_TYPE type);
	auto getPPUFrameBuffer() { return ppu.returnScreen(); }
};