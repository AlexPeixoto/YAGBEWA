#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <APU/audiocontroller.h>
#include <Bus.h>


int main(int argc, char** argv){
    /*if(argc != 2)
        return 1;

    std::string filename = argv[1];
	*/
	Bus bus;

	//bus.cartridgeManager.loadRom("Tetris.gb");

	//As this code does not implement a BUS per-se all the "elements" are here.
	//Maybe later either a BUS or a "board" can be created in order to have those components out of the main function.

	//Load cartridge header
    //Memory::Cartridge::RomLoader loader(begin);
	//loader.load()
	
    //TODO: Memory writes MIGHT work as an interrution.
	//Example is when writting between 2000 - 3FFFF to switch the cartridge bank


    //////////////  AUDIO  /////////////

    audioController audio;






    ////////////////////////////////////
    return 0;
}

