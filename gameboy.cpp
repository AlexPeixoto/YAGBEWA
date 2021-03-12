#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <APU/audiocontroller.h>
#include <Bus.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

uint8_t buildJOYPDirections(const sf::Keyboard::Key& code){
    uint8_t result = 
        0x0 |
        (code == sf::Keyboard::Down) << 3 |
        (code == sf::Keyboard::Up) << 2 |
        (code == sf::Keyboard::Left) << 1 |
        (code == sf::Keyboard::Right);

    return result;
}

uint8_t buildJOYPButtons(const sf::Keyboard::Key& code){
    uint8_t result = 
        0x0 |
        (code == sf::Keyboard::Return) << 3 |
        (code == sf::Keyboard::Space) << 2 |
        (code == sf::Keyboard::B) << 1 |
        (code == sf::Keyboard::A);
        
    return result;
}

int main(int argc, char** argv){
    /*if(argc != 2)
        return 1;

    std::string filename = argv[1];
	*/
	Bus bus;

    //Games
	bus.cartridge.loadRom("Tetris.gb");
    //bus.cartridge.loadRom("drmario.gb");

    //SCX ONLY USED FOR FOOTER
    //bus.cartridge.loadRom("dmg-acid2.gb");
    //Tests
    //bus.cartridge.loadRom("01op.gb");
    //interrupts (FAILS WITH _IF instead of isInterruptionPending, which halts other tests)
    //bus.cartridge.loadRom("02op.gb"); 
    //bus.cartridge.loadRom("03op.gb");
    //bus.cartridge.loadRom("04op.gb");
    //bus.cartridge.loadRom("05op.gb");
    //bus.cartridge.loadRom("06op.gb");
    //bus.cartridge.loadRom("07op.gb");
    //bus.cartridge.loadRom("08op.gb"); //misc
    //bus.cartridge.loadRom("09op.gb");
    //bus.cartridge.loadRom("10op.gb");
    //bus.cartridge.loadRom("11op.gb");
    //bus.cartridge.loadRom("boot_regs-A.gb");
    //bus.cartridge.loadRom("boot_div-A.gb");
    bus.initCPU();

    //Yet another Gameboy emulator without audio
    sf::RenderWindow window(sf::VideoMode(160, 144), "YAGBEWA");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setSize({800, 700});

    // run the program as long as the window is open
    sf::Texture texture;
    texture.create(160, 144);
    sf::Sprite background;
    uint64_t frame = 0;
    while (window.isOpen())
    {
        sf::Event event;

        //Reset button
        bus.setDirections(0);
        bus.setButtons(0);
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                bus.setDirections(buildJOYPDirections(event.key.code));
                bus.setButtons(buildJOYPButtons(event.key.code));
            } 
        }
        window.clear();
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
        window.display();
    }
    return 0;
}

