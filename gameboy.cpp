#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <APU/audiocontroller.h>
#include <Bus.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main(int argc, char** argv){
    /*if(argc != 2)
        return 1;

    std::string filename = argv[1];
	*/
	Bus bus;

	bus.cartridge.loadRom("Tetris.gb");
    //bus.cartridge.loadRom("drmario.gb");
    //bus.cartridge.loadRom("cpu_instrs.gb", true);
    //bus.cartridge.loadRom("dmg_boot.gb", true);
    bus.initCPU();

    sf::RenderWindow window(sf::VideoMode(160, 144), "Gameboy");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60); // TODO, CHANGE TO 60 WHEN TIMMING IS FIXED
    window.setSize({800, 700});

    // run the program as long as the window is open
    sf::Texture texture;
    texture.create(160, 144);
    sf::Sprite background;
    uint64_t frame = 0;
    while (window.isOpen()/* || windowDebug.isOpen()*/)
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        //windowDebug.clear();
        bus.runCycle();
        auto buffer = bus.getPPUFrameBuffer();
        sf::Image image = texture.copyToImage();
        for(int x=0; x<160; x++){
            for(int y=0; y<144; y++){
                const auto pixel = buffer[x][y];
                sf::Color color(pixel.r, pixel.g, pixel.b);
                image.setPixel(x, y, color);
            }
        }
        
        texture.loadFromImage(image);
        background.setTexture(texture);
        window.draw(background);
        //std::cout << "Frame: " << std::dec << frame++ << std::endl;
        window.display();
        //windowDebug.display();
    }

	//Load cartridge header
    //Memory::Cartridge::RomLoader loader(begin);
	//loader.load()
	
    //TODO: Memory writes MIGHT work as an interrution.
	//Example is when writting between 2000 - 3FFFF to switch the cartridge bank

    

    //////////////  AUDIO  /////////////

    //audioController audio;








    ////////////////////////////////////
    return 0;
}

