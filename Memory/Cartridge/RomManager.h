#pragma once
#include <memory>

#include <Memory/Cartridge/Header.h>
#include <Memory/Cartridge/Controllers/ControllerBase.h>
#include <Memory/Cartridge/Controllers/None.h>
#include <Memory/MemoryMap.h>

namespace Memory::Cartridge{
	class RomManager{
	private:
		Header header;
		std::unique_ptr<Controller::ControllerBase> controller;

		std::string fileName;
		size_t cartridgeSize;
		Memory::Map& mem;

		//To make everything easier, we store the whole cartrige in memory and close the file.
		unsigned char* cartridgeBeginPtr;

		//As of now the load is only done during initialization
		void loadCartridge();
		void initController(const Cartridge::MBC &controllerType);

		//Used to load bank 1 and 2 at cartridge initial load
		void loadRom();
	public:
		//Gets the name of the file being loaded and have access to the memory
		RomManager(std::string filename, Memory::Map &mem);
		~RomManager();
	};
}