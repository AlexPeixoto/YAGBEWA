#pragma once

#include <array>
#include <functional>
#include <string>

#include <iostream>

namespace Memory{
	using MemoryArray = std::array<uint8_t, 0xFFFF>;

	struct Segment {
		uint16_t position;
		uint16_t size;
	};

	//MemorySegments
	const Segment romBank0{ 0x0000, 0x3999 };
	const Segment romBank1{ 0x4000, 0x3999 };
	const Segment videoRam{ 0x8000, 0x1999 };
	const Segment switchableRam{ 0xA000, 0x1999 };
	const Segment internalRam1{ 0xC000, 0x1999 };
	const Segment internalRam2{ 0xC000, 0x1999 };
	//ECHO from 0xC000 until 0xFDFF
	const Segment spriteAttrib{ 0xFE00, 0x009F };
	const Segment ioReg{ 0xFF00, 0x007F };
	const Segment hiRam{ 0xFF80, 0x007E };
	const Segment interrupted{ 0xFFFF, 0xFFFF };


    //The whole memory map (As of now) is here
	//Maybe its worth breaking it up into video, work ram and cartridge ram
    class Map{
        private:
			MemoryArray memory;
        public:
			//This contains a list of each memory area that an be accesse.
			//This is used on fillWith to prevent OOB memory from being accessed.
			enum class MemArea{
				//Can only be changed by a cartridge call
				ROMBANK_0,
				ROMBANK_1,
				VIDEORAM,
				SWITCHABLERAM,
				INTERNALRAM_1,
				INTERNALRAM_2,
				SPRITEATTRIB,
				IOREG,
				HIRAM,
				INTERRUPTED,
				CPU //This is like a master value, which can change "anything"
			};
			Map() {
				//for(int x=0; x< 0xffff; x++)
				//	memory.at(x) = static_cast<uint8_t>(134);
				/* Powerup Sequence
				  	AF=$01B0
					BC=$0013
					DE=$00D8
					HL=$014D
					Stack Pointer=$FFFE
					[$FF05] = $00   ; TIMA
					[$FF06] = $00   ; TMA
					[$FF07] = $00   ; TAC
					[$FF10] = $80   ; NR10
					[$FF11] = $BF   ; NR11
					[$FF12] = $F3   ; NR12
					[$FF14] = $BF   ; NR14
					[$FF16] = $3F   ; NR21
					[$FF17] = $00   ; NR22
					[$FF19] = $BF   ; NR24
					[$FF1A] = $7F   ; NR30
					[$FF1B] = $FF   ; NR31
					[$FF1C] = $9F   ; NR32
					[$FF1E] = $BF   ; NR34
					[$FF20] = $FF   ; NR41
					[$FF21] = $00   ; NR42
					[$FF22] = $00   ; NR43
					[$FF23] = $BF   ; NR44
					[$FF24] = $77   ; NR50
					[$FF25] = $F3   ; NR51
					[$FF26] = $F1-GB, $F0-SGB ; NR52
					[$FF40] = $91   ; LCDC
					[$FF42] = $00   ; SCY
					[$FF43] = $00   ; SCX
					[$FF45] = $00   ; LYC
					[$FF47] = $FC   ; BGP
					[$FF48] = $FF   ; OBP0
					[$FF49] = $FF   ; OBP1
					[$FF4A] = $00   ; WY
					[$FF4B] = $00   ; WX
					[$FFFF] = $00   ; IE
					*/
				//Set FF00 as F and prevent any further writes to it until IO is done 
			};

			bool isValidWrite(std::size_t size, MemArea area) const {
				switch (area) {
					case MemArea::ROMBANK_0:
						return size <= romBank0.size;
					case MemArea::ROMBANK_1:
						return size <= romBank1.size;
					case MemArea::VIDEORAM:
						return size <= videoRam.size;
					case MemArea::SWITCHABLERAM:
						return size <= switchableRam.size;
					case MemArea::INTERNALRAM_1:
						return size <= internalRam1.size;
					case MemArea::INTERNALRAM_2:
						return size <= internalRam2.size;
					case MemArea::SPRITEATTRIB:
						return size <= spriteAttrib.size;
					case MemArea::IOREG:
						return size <= ioReg.size;
					case MemArea::HIRAM:
						return size <= hiRam.size;
					case MemArea::INTERRUPTED:
						return size <= interrupted.size;
					default: //CPU
						return true;
				}
			};

			void load(uint8_t* data, unsigned short pos, unsigned short size) {
				std::copy(data, data + size, memory.begin() + pos);
			}
			
			inline void write(uint8_t val, uint16_t addr) {
				memory[addr] = val;
			}

			inline uint8_t& read(uint16_t addr) {
				return memory[addr];
			}

			//Used to fill certain areas of the memory.
			//Mem area is used to prevent writing to a wrong memory space
			//Maybe I should change that to a single write
			template<typename T>
			void fillWith(const T& memArr, std::size_t size, MemArea area) {
				if (!isValidWrite(size, area))
					std::runtime_error("Invalid write for: " + std::to_string(static_cast<int>(area)));
				switch (area) {
				case MemArea::ROMBANK_0:
					
					break;
				case MemArea::ROMBANK_1:
					break;
				default:
					break;
				}
			}
			//Perform std::fill with 0
			void clearMemory();
			
			//Method that will be triggered once the interruption memory value is changed
			void registerInterruptionCallback(std::function<void()> func);
	};
}