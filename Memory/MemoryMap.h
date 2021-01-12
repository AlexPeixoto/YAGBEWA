#pragma once

#include <array>
#include <functional>
#include <string>

#include <iostream>

namespace Memory{
	// 0xFFFF + 1.... (interrupted segment)
	using MemoryArray = std::array<uint8_t, 0x10000>;

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
				// Power up sequence
				memory.at(0xFF05) = 0x00; //TIMA
				memory.at(0xFF06) = 0x00; //TMA
				memory.at(0xFF07) = 0x00; //TAC
				memory.at(0xFF10) = 0x80; //NR10
				memory.at(0xFF11) = 0xBF; //NR11
				memory.at(0xFF12) = 0xF3; //NR12
				memory.at(0xFF14) = 0xBF; //NR14
				memory.at(0xFF16) = 0x3F; //NR21
				memory.at(0xFF17) = 0x00; //NR22
				memory.at(0xFF19) = 0xBF; //NR24
				memory.at(0xFF1A) = 0x7F; //NR30
				memory.at(0xFF1B) = 0xFF; //NR31
				memory.at(0xFF1C) = 0x9F; //NR32
				memory.at(0xFF1E) = 0xBF; //NR34
				memory.at(0xFF20) = 0xFF; //NR41
				memory.at(0xFF21) = 0x00; //NR42
				memory.at(0xFF22) = 0x00; //NR43
				memory.at(0xFF23) = 0xBF; //NR44
				memory.at(0xFF24) = 0x77; //NR50
				memory.at(0xFF25) = 0xF3; //NR51
				memory.at(0xFF26) = 0x00; //TODO: Check this later... F1; //-GB, $F0-SGB ; NR52
				memory.at(0xFF40) = 0x91; //LCDC
				memory.at(0xFF42) = 0x00; //SCY
				memory.at(0xFF43) = 0x00; //SCX
				memory.at(0xFF45) = 0x00; //LYC
				memory.at(0xFF47) = 0xFC; //BGP
				memory.at(0xFF48) = 0xFF; //OBP0
				memory.at(0xFF49) = 0xFF; //OBP1
				memory.at(0xFF4A) = 0x00; //WY
				memory.at(0xFF4B) = 0x00; //WX
				memory.at(0xFFFF) = 0x00; //IE
				//Set FF00 as F and prevent any further writes to it until IO is done 
			};

			uint8_t* getRomStart() {
				return &memory.at(0x00);
			}

			uint8_t* getMemoryAt(uint16_t pos) {
				return &memory.at(pos);
			}

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
				if(addr < videoRam.position)
					return;
				memory[addr] = val;
			}

			inline void writeBank(uint8_t val, uint16_t addr) {
				if(addr >= videoRam.position)
					return;
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