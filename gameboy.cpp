#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <APU/audiocontroller.h>
//#include <Memory/Cartridge/RomLoader.h>


//This can be heavily improved, as of now this is a simple code to initialize what is needed and generate the disassembly
int main(int argc, char** argv){
    if(argc != 2)
        return 1;

    std::string filename = argv[1];

    //char* data;
    //size_t fileSize = loadFileTo(filename, &data);

	//if(!fileSize)
    //    return 2;

    //
    //Load cartridge header
    //Memory::Cartridge::RomLoader loader(begin);
	//loader.load()
	//TODO: Have to load the first and second bank of the cartridge into memory.
	
    //TODO: Memory writes MIGHT work as an interrution.
	//Example is when writting between 2000 - 3FFFF to switch the cartridge bank


    //////////////  AUDIO  /////////////

    audioController audio;






    ////////////////////////////////////
    return 0;
}

