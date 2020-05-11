#include <array>
#include <function>

namespace Memory{
	using MemoryArray = std::array<uint8_t, 0xFFF>;
    //The whole memory map (As of now) is here
	//Also this is now made as a static "class", this might change in the future, but as of now a single memory
	//Instance might be the easiest one to work with.
    class Map{
        private:
			struct Segment {
				uint16_t position;
				uint16_t size;
			};

			MemoryArray memory;
            
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
			//This contains a list of each memory area that an be accesse.
			//This is used on fillWith to prevent OOB memory from being accessed.
			enum class MemArea{
				//Can only be changed by a cartridge call
				ROMBANK_0,
				ROMBANK_1,
				VIDEORAM,
				SWITCHABLERAM.
				INTERNALRAM_1,
				INTERNALRAM_2,
				SPRITEATTRIB,
				IOREG,
				HIRAM,
				INTERRUPTED,
				CPU //This is like a master value, which can change "anything"
			};
			Map();

			//Used to fill certain areas of the memory.
			//Mem area is used to prevent writing to a wrong memory space
			template<typename T>
			void fillWith(const T& memArr, std::size_t size, MemArea area);
			//Perform std::fill with 0
			void clearMemory();
			
			//Method that will be triggered once the interruption memory value is changed
			void registerInterruptionCallback(std::function<void()> func);
    }
}