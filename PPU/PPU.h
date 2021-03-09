#pragma once

#include <array>
#include <unordered_set>
#include <ctype.h>

class Bus;

namespace PPU{
    class Core{
        private:
        

        struct Color{
            uint8_t r, g, b;
        };

        //10 sprites per line
        struct Sprite{
            //0 means that its inside the "screen" (as we want to be able to make in move inside)
            //So 0x10 (as the sprite is 16 pixels height) means "0" on the screen
            uint8_t posY;
            //0 means that its inside the "screen" (as we want to be able to make in move inside)
            //So 0x08 (as the sprite is 8 pixels width) means "0" on the screen
            uint8_t posX;
            uint8_t tileIndex; //index;
            //DOUBLE CHECK
            //1 - Above background pixels with value 0, below non-0 pixels
            //0 - On top of everything (There is an weird behaviour depending on the position, not sure if that will be emulated)
            uint8_t priority:1;
            uint8_t flipX:1;
            uint8_t flipY:1;
            uint8_t pallete:1; //ff48 for 0 or FF49 for 1
        }; 
        //Gameboy resolution is 160x144.
        //Even if this data is duplicated in memory, as of now the idea is to copy
        //it somewhere so whoever renders it uses a more "friendly" approach
        std::array<std::array<Color, 144>, 160> screen, internalBuffer;
        
        //Set pixel value for 00, 01, 10, 11.
        std::array<Color, 4> backgroundColorMap, objectPallete1, objectPallete2;
        //Store sprites
        std::array<Sprite, 40> sprites;
        //Store the used sprites at this time.
        std::array<uint8_t, 10> spritesIndex;
        //Total of sprites on line
        uint8_t spritesOnLine;
        //Mark an invalid mode
        uint8_t modeProcessed=5;
        //Check if vblank was served this frame
        bool vblankServed = false;

        Bus* bus;

        void checkLYC_LY();

        bool isLCDEnabled();
        bool isWindowTileMapDisplaySelectHigh();
        bool isWindowDisplayEnabled();
        bool isTileDataSelectHigh();
        bool isBgTileMapHigh();
        bool isSpriteDoubleHeight();
        bool isSpriteEnabled();
        bool isBGWindowDisplayPriority();

        void renderLine();
        void renderWindow();

        void setMode(uint8_t mode);
        uint8_t getMode();

        void initPalleteTable(std::array<Color, 4>& palette, uint16_t memPosition);
        void initSprites();
        void getSpritesOnLine();

        void processModes();
        void processMode0();
        void processMode1();
        void processMode2();
        void processMode3();

        public:
        Core(Bus* bus);
        void tick();
        auto returnScreen() { return screen; }
    };
}