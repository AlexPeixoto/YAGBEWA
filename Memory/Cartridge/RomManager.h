#pragma once
#include <Memory/Cartridge/Header.h>

namespace Memory::Cartridge{
	class RomManager{
	private:
		Header header;
		ControllerBase controller;

		std::string fileName;
		size_t cartridgeSize;

		//To make everything easier, we store the whole cartrige in memory and close the file.
		unsigned char* cartridgeBeginPtr;

		//As of now the load is only done during initialization
		void loadCartridge();
	public:
		RomManager(std::string filename);
		~RomManager();
	};
}