#pragma once

#include <array>
#include <ctype.h>

class Bus;

namespace PPU{
    class Core{
        private:
        const uint16_t LCD_CONTROL_REGISTER_ADDR = 0xFF40;

        struct pixel{
            uint8_t color:2;
        };
        //Gameboy resolution is 160x144.
        //Even if this data is duplicated in memory, as of now the idea is to copy
        //it somewhere so whoever renders it uses a more "friendly" approach
        std::array<std::array<uint8_t, 160>, 144> screen;
        //Mark an invalid mode
        uint8_t modeProcessed=5;

        Bus* bus;

        void checkLYC_LY();

        bool isLCDEnabled();
        bool isWindowTileMapDisplaySelectHigh();
        bool isWindowDisplayEnabled();
        bool isBgWindowTtileHigh();
        bool isBgTileMapHigh();
        bool isOBGSize();
        bool isOBGDisplayEnabled();
        bool isBGWindowDisplayPriority();

        void renderLine();
        void renderWindow();

        void setMode(uint8_t mode);
        uint8_t getMode();

        void processModes();
        void processMode0();
        void processMode1();
        void processMode2();
        void processMode3();

        public:
        Core(Bus* bus);
        void tick(uint16_t ticks);
    };
}