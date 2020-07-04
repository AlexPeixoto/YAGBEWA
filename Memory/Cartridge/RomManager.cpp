#include <Memory/Cartridge/RomManager.h>
#include <Bus.h>

#include <exception>
#include <fstream>
using namespace Memory::Cartridge;

RomManager::RomManager(Bus* bus)
    : bus(bus)
{
	std::cout << "Bus: " << bus << std::endl;
	//loadCartridge();
}
RomManager::~RomManager() {}

void RomManager::loadRom(std::string fileName) {
	this->fileName = fileName;
	loadCartridge();
}

void RomManager::loadCartridge() {
	//Assumes that the first parameter is the name of the file
	//std::cout << "File opened:" << filename << std::endl;
	std::ifstream file(this->fileName, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.good()) {
		throw std::runtime_error("Failed to open the file: " + fileName);
	}

	//All the cartridge data is stored on a file
	size_t fileSize = file.tellg();

	const uint16_t headerSize = Header::getTotalHeaderSize();
	cartridgeData = new char[fileSize];

	//Go to the start of the rom file and read its content
	file.seekg(0, std::ios::beg);
	file.read(cartridgeData, fileSize);//copy file into memory

	//Get an unsigned char* from the char* (required by file.read).
	//Then uses that to load the header.
	cartridgeBeginPtr = reinterpret_cast<unsigned char*>(cartridgeData);
	header.loadData(cartridgeBeginPtr);
	initController(header.getCartridgeType().mbc);

	loadBanks();

}

void RomManager::initController(const MBC &controllerType) {
	switch (controllerType) {
	case MBC::NONE:
		//No memory passed to rom manager, most likelly each method that hopes to change it will get its reference.
		controller.reset(new Controller::None());
		break;
	default:
		break;
	}
	
}

void RomManager::loadBanks() {
	bus->memoryMap.load(reinterpret_cast<uint8_t*>(cartridgeData), Memory::romBank0.position, Memory::romBank0.size);
	bus->memoryMap.load(reinterpret_cast<unsigned char*>(cartridgeData + Memory::romBank1.position), Memory::romBank1.position, Memory::romBank1.size);
}
