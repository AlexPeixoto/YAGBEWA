#pragma once

#include <array>
#include <ctype.h>

class Bus;

namespace PPU{
    class Core{
        private:
        struct pixel{
            uint8_t color:2;
        };
        //Gameboy resolution is 160x144.
        //Even if this data is duplicated in memory, as of now the idea is to copy
        //it somewhere so whoever renders it uses a more "friendly" approach
        std::array<std::array<uint8_t, 160>, 144> screen;

        Bus* bus;

        public:
        Core(Bus* bus);
        void tick();
    };
}