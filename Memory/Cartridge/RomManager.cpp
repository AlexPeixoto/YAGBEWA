#include <Memory/Cartridge/RomManager.h>

#include <exception>
#include <fstream>
using namespace Memory::Cartridge;

RomManager::RomManager(std::string fileName) {
	this->loadCartridge();
}
RomManager::~RomManager() {}

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
	char *data = new char[fileSize];

	//Go to the start of the rom file and read its content
	file.seekg(0, std::ios::beg);
	file.read(data, fileSize);//copy file into memory

	//Get an unsigned char* from the char* (required by file.read).
	//Then uses that to load the header.
	cartridgeBeginPtr = reinterpret_cast<unsigned char*>(data);
	header.loadData(cartridgeBeginPtr);
}

void RomManager::initController(const MBC &controllerType) {
	
}