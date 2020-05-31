#pragma once
#include <memory>

#include <Memory/Cartridge/Header.h>
#include <Memory/Cartridge/Controllers/ControllerBase.h>
#include <Memory/Cartridge/Controllers/None.h>


class Bus;
namespace Memory::Cartridge{
	//Rom manager acts as the "rom controller"
	class RomManager{
	private:
		Header header;
		std::unique_ptr<Controller::ControllerBase> controller;

		std::string fileName;
		size_t cartridgeSize;
        Bus* bus;

		//To make everything easier, we store the whole cartrige in memory and close the file.
		unsigned char* cartridgeBeginPtr;

		//As of now the load is only done during initialization
		void loadCartridge();
		void initController(const Cartridge::MBC &controllerType);

		//Used to load bank 1 and 2 at cartridge initial load
		void loadBanks();
	public:
		//Gets the name of the file being loaded and have access to the memory
        RomManager(Bus* bus);
		~RomManager();

		void loadRom(std::string filename);
	};
}
