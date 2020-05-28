#pragma once
#include <memory>

#include <Memory/Cartridge/Header.h>
#include <Memory/Cartridge/Controllers/ControllerBase.h>
#include <Memory/Cartridge/Controllers/None.h>

namespace Memory::Cartridge{
	class RomManager{
	private:
		Header header;
		std::unique_ptr<Controller::ControllerBase> controller;

		std::string fileName;
		size_t cartridgeSize;

		//To make everything easier, we store the whole cartrige in memory and close the file.
		unsigned char* cartridgeBeginPtr;

		//As of now the load is only done during initialization
		void loadCartridge();
		void initController(const Cartridge::MBC &controllerType);
	public:
		RomManager(std::string filename);
		~RomManager();
	};
}