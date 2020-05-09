#include <array>

namespace Memory{
    struct Segment{
        uint16_t position;
        uint16_t size;
    };
    //The whole memory map (As of now) is here
    class Map{
        private:
            std::array<uint8_t, 0xFFFF> memory;
            
            //MemorySegments
            const Segment romBank0{0x0000, 0x3999};
            const Segment romBank1{0x4000, 0x3999};
            const Segment videoRam{0x8000, 0x1999};
            const Segment switchableRam{0xA000, 0x1999};
            const Segment internalRam1{0xC000, 0x1999};
            const Segment internalRam2{0xC000, 0x1999};
            //ECHO from 0xC000 until 0xFDFF
            const Segment spriteAttrib{0xFE00, 0x009F};
            const Segment ioReg{0xFF00, 0x007F};
            const Segment hiRam{0xFF80, 0x007E};
            const Segment interrupted{0xFFFF, 0xFFFF};
        public:
            Map();
            
    }
}