#pragma once

#include <array>
#include <functional>
#include <string>

#include <iostream>

class Bus;
namespace Memory{
	// 0xFFFF + 1.... (interruptions segment)
	using MemoryArray = std::array<uint8_t, 0x10000>;

	struct Segment {
		uint16_t position;
		uint16_t size;
	};

	//MemorySegments
	const Segment romBank0{ 0x0000, 0x3FFF };
	const Segment romBank1{ 0x4000, 0x3FFF };
	const Segment videoRam{ 0x8000, 0x1FFF };
	const Segment switchableRam{ 0xA000, 0x1FFF };
	const Segment internalRam1{ 0xC000, 0x1FFF };
	const Segment internalRam2{ 0xD000, 0x1FFF };
	//ECHO from 0xE000 until 0xFDFF
	const Segment spriteAttrib{ 0xFE00, 0x009F };
	/* From pandoc
	FF00	FF02	DMG	Port/Mode
	FF04	FF07	DMG	Port/Mode
	FF10	FF26	DMG	Sound
	FF30	FF3F	DMG	Waveform RAM
	FF40	FF4B	DMG	LCD
	FF4F		    CGB	VRAM Bank Select
	FF50		    DMG	Set to non-zero to disable boot ROM
	FF51	FF55	CGB	HDMA
	FF68	FF69	CGB	BCP/OCP
	FF70		    CGB	WRAM Bank Select
	*/
	const Segment ioReg{ 0xFF00, 0x007F };
	const Segment hiRam{ 0xFF80, 0x007E };
	const Segment interruptions{ 0xFFFF, 0xFFFF };


    //Maps the memory, dont see this as a RAM module, but more as an orchestrator for memory access.
	//This also works as a translator when a memory segment is accessed that is not "memory per se",
	//but more like a memory map controller.
    class Map{
        private:
			MemoryArray memory;
			Bus* bus;

			//Some very rare occasions (like DMA) creates a cycle cost
			uint16_t memoryOpCost = 0;
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
				INTERRUPTION,
				CPU //This is like a master value, which can change "anything"
			};
			//Mainly used for UT
			Map(){}

			uint16_t getAndTick4(){
				if(memoryOpCost<=0)
					return 0;
				uint16_t tmp = memoryOpCost;
				memoryOpCost -= 4;
				return tmp;
			}

			Map(Bus* bus) : bus(bus) {
				for(int x=0; x< 0xffff; x++)
					memory.at(x) = static_cast<uint8_t>(0);
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
				memory.at(0xFF48) = 0xff; //OBP0
				memory.at(0xFF49) = 0xff; //OBP1
				memory.at(0xFF4A) = 0x00; //WY
				memory.at(0xFF4B) = 0x00; //WX
				memory.at(0xFFFF) = 0x00; //IE
				memory.at(0xFF00) = 0xff; //JOYP
				
				//Set FF00 as F and prevent any further writes to it until IO is done 
			};

			void loadNintendoLogo(){
				#if 1
				memory.at(0x100) = 0x00; 
				memory.at(0x101) = 0xc3;
				memory.at(0x102) = 0x50;
				memory.at(0x103) = 0x01;
				memory.at(0x104) = 0xce;
				memory.at(0x105) = 0xed;
				memory.at(0x106) = 0x66;
				memory.at(0x107) = 0x66;
				memory.at(0x108) = 0xcc;
				memory.at(0x109) = 0x0d;
				memory.at(0x10A) = 0x00;
				memory.at(0x10B) = 0x0b;
				memory.at(0x10C) = 0x03;
				memory.at(0x10D) = 0x73;
				memory.at(0x10E) = 0x00;
				memory.at(0x10F) = 0x83;

				memory.at(0x110) = 0x00; 
				memory.at(0x111) = 0x0c;
				memory.at(0x112) = 0x00;
				memory.at(0x113) = 0x0d;
				memory.at(0x114) = 0x00;
				memory.at(0x115) = 0x08;
				memory.at(0x116) = 0x11;
				memory.at(0x117) = 0x1f;
				memory.at(0x118) = 0x88;
				memory.at(0x119) = 0x89;
				memory.at(0x11A) = 0x00;
				memory.at(0x11B) = 0x0e;
				memory.at(0x11C) = 0xdc;
				memory.at(0x11D) = 0xcc;
				memory.at(0x11E) = 0x6e;
				memory.at(0x11F) = 0xe6;

				memory.at(0x120) = 0xdd; 
				memory.at(0x121) = 0xdd;
				memory.at(0x122) = 0xd9;
				memory.at(0x123) = 0x99;
				memory.at(0x124) = 0xbb;
				memory.at(0x125) = 0xbb;
				memory.at(0x126) = 0x67;
				memory.at(0x127) = 0x63;
				memory.at(0x128) = 0x6e;
				memory.at(0x129) = 0x0e;
				memory.at(0x12A) = 0xec;
				memory.at(0x12B) = 0xcc;
				memory.at(0x12C) = 0xdd;
				memory.at(0x12D) = 0xdc;
				memory.at(0x12E) = 0x99;
				memory.at(0x12F) = 0xef;

				memory.at(0x130) = 0xbb; 
				memory.at(0x131) = 0xb9;
				memory.at(0x132) = 0x33;
				memory.at(0x133) = 0x3e;
				memory.at(0x134) = 0x54;
				memory.at(0x135) = 0x45;
				memory.at(0x136) = 0x54;
				memory.at(0x137) = 0x52;
				memory.at(0x138) = 0x49;
				memory.at(0x139) = 0x53;

				memory.at(0x14B) = 0x01; 
				memory.at(0x14C) = 0x01;
				memory.at(0x14D) = 0x0a;
				memory.at(0x14E) = 0x16;
				memory.at(0x14F) = 0xbf;
				#endif
			}
			uint8_t& operator[](std::size_t index) { return memory.at(index); }

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
					case MemArea::INTERRUPTION:
						return size <= interruptions.size;
					default: //CPU
						return true;
				}
			};

			void load(uint8_t* data, ptrdiff_t pos, ptrdiff_t size) {
				//Add 1, this is because I need to stop on the next byte
				std::copy(data, data + size + 1, memory.begin() + pos);
			}
			
			//Write here does not allow (for now), to write on vram
			inline void write(uint8_t val, uint16_t addr) { 
				//Tetris testing JOYP hack
				//if(addr == 0xFF00){
				//	std::cout << "Attempt to write at ff00" << std::endl;
				//	return;
				//}
				
				if(addr < videoRam.position)
					return;
				// || 
				//	//Prohibited areas
				//	addr >= 0xE000 && addr <= 0xFDFF)
				//	return;
				//Block CPU writes on mode 2 or 3 to the VRAM memory
				/*
				 * When the LCD controller is reading a particular part of video memory, that memory is inaccessible to the CPU.

				 * During modes 2 and 3, the CPU cannot access OAM (FE00h-FE9Fh).
				 * During mode 3, the CPU cannot access VRAM or CGB Palette Data (FF69,FF6B).
				 */
				if(addr == 0xFF41){
					//7th bit (last one) is always 1
					val |= 0b10000000;
				}
				switch(memory[0xFF41] & 0x3){
					case 2:
						//NO OAM ACCESS
						if(addr >= 0xF300 && addr <= 0xFE9F)
							return;
					case 3:
						//NO OAM
						if(addr >= 0xF300 && addr <= 0xFE9F)
							return;
						if(addr == 0xFF69 || addr == 0xFF6B)
							return;
						//No VRAM access for you
						if(addr >= 0x8000 && addr <= 0x9FF)
							return;
				}
				//if(addr >= 0xc000 && addr <= 0xc09f){
					
					//abort();
				//}
				//Special write handling
				switch(addr){
					
					case 0xFF00:
						memory[addr] = val;
						//Here I fake set all THE LOW 4 BITS.
						//Have in mind that depending which bit is set we either read as a button (A, B, START, SELECT) or direction
						/*Bit 5 - P15 Select Button Keys      (0=Select)
						Bit 4 - P14 Select Direction Keys   (0=Select)
						Bit 3 - P13 Input Down  or Start    (0=Pressed) (Read Only)
						Bit 2 - P12 Input Up    or Select   (0=Pressed) (Read Only)
						Bit 1 - P11 Input Left  or Button B (0=Pressed) (Read Only)
						Bit 0 - P10 Input Right or Button A (0=Pressed) (Read Only)*/
						memory[addr] |= 0xCF;
						return;

					//Reset 0xFF04 on attempts to write to it (Timer).
					case 0xFF04:
						memory[addr] = 0;
						return;

					case 0xFF46:
						//PPU DMA TRANSFER
						uint16_t startAddress = 0;
						startAddress |= val << 8;
						//std::cout << "DMA TO: " << std::hex << static_cast<uint32_t>(startAddress) << std::endl;
						//Source:      XX00-XX9F   ;XX in range from 00-F1h
						//Destination: FE00-FE9F
						//costs 160 cycles (but not mapped yet).
						std::copy(memory.begin() + startAddress, memory.begin() + startAddress + 0x009F, memory.begin() + 0xFE00);
						//DMA costs 160 CPU cycles
						memoryOpCost = 160;
						return;
				}
				if(addr == 0xFF0F)
					std::cout << "UPDATING IF TO: " << static_cast<uint32_t>(val) << std::endl;

				if(addr == 0xFFFF)
					std::cout << "UPDATING IE TO: " << static_cast<uint32_t>(val) << std::endl;
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