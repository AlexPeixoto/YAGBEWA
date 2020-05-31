#pragma once

#include <CPU/LR35902.h>
#include <Memory/Cartridge/RomManager.h>
#include <Memory/MemoryMap.h>

class Bus {
private:
	//Memory writing operations can trigger interruptions.
	Memory::Map memoryMap;

public:
	//Cpu, PPU, APU and cartridge are public here as the buss just connects them.

    CPU::LR35902 cpu;
    Memory::Cartridge::RomManager cartridge;

    Bus ();
    ~Bus ();
};


class D{
public:
    D(){}
};
