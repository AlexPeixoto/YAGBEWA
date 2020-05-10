#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

//#include <Memory/Cartridge/RomLoader.h>


std::size_t loadFileTo(std::string filename, char** data)
{
    //Assumes that the first parameter is the name of the file
    std::cout << "File opened:" << filename << std::endl;
    std::ifstream file(filename, std::ios::in |std::ios::binary | std::ios::ate);
    if(!file.good()){
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return 0;
    }

    //All the cartridge data is stored on a file
    size_t fileSize = file.tellg();
    *data = new char[fileSize];
    file.seekg (0, std::ios::beg);
	file.read (*data, fileSize);//copy file into memory

    return fileSize;
}

//This can be heavily improved, as of now this is a simple code to initialize what is needed and generate the disassembly
int main(int argc, char** argv){
    if(argc != 2)
        return 1;

    std::string filename = argv[1];
    char* data;
    size_t fileSize = loadFileTo(filename, &data);

	if(!fileSize)
        return 2;

    unsigned char* begin = reinterpret_cast<unsigned char*>(data);
    //Load cartridge header
    //Memory::Cartridge::RomLoader loader(begin);
	//loader.load()
	//TODO: Have to load the first and second bank of the cartridge into memory.
	
    //TODO: Memory writes MIGHT work as an interrution.
	//Example is when writting between 2000 - 3FFFF to switch the cartridge bank
    return 0;
}

