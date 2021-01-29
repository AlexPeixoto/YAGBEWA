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

			uint16_t getAndResetCost(){
				uint16_t tmp = memoryOpCost;
				memoryOpCost = 0;
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
				memory.at(0xFF48) = 0xFF; //OBP0
				memory.at(0xFF49) = 0xFF; //OBP1
				memory.at(0xFF4A) = 0x00; //WY
				memory.at(0xFF4B) = 0x00; //WX
				memory.at(0xFFFF) = 0x00; //IE
				memory.at(0xFF00) = 0xff; //JOYP
				
				//Set FF00 as F and prevent any further writes to it until IO is done 
			};

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
				//if(addr == 0xFF47){
				//	std::cout << "Attempt to write to palette memory" << std::endl;
				//}
				//Tetris testing JOYP hack
				if(addr == 0xFF00)
					return;
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
				switch(memory[0xFF41] & 0x3){
					case 0x10:
						if(addr >= 0xF300 && addr <= 0xFE9F)
							return;
					case 0x11:
						if(addr >= 0xF300 && addr <= 0xFE9F)
							return;
						if(addr == 0xFF69 || addr == 0xFF6B)
							return;
						//No VRAM access for you
						if(addr >= 0x8000 || addr <= 0x9FF)
							return;
				}
				if(addr >= 0xc000 && addr <= 0xc09f){
					std::cout << "Aborting write to: " << std::hex << addr << std::endl;
					abort();
				}
				//Special write handling
				switch(addr){
					//Reset 0xFF04 on attempts to write to it (Timer).
					case 0xFF04:
						memory[addr] = 0;
						return;
					//This is not IME, but the vector with list of enavled interrupts
					//case 0xFFFF:
					//	std::cout << "Updating interrupt value" << std::endl;
					//	return;
					case 0xFF46:
						std::cout << "DMA THIS SHIT" << std::endl;
						std::cout << std::hex << static_cast<uint32_t>(val) << std::endl;
						
						//PPU DMA TRANSFER
						uint16_t startAddress = 0;
						startAddress |= val << 8;
						std::cout << "With real start at: " << std::hex << static_cast<uint32_t>(startAddress) << std::endl;
						std::cout << "With real end at: " << std::hex << static_cast<uint32_t>(startAddress + 0x009F) << std::endl;
						for(uint16_t addrStart = startAddress; addrStart < (startAddress + 0x009F); addrStart++)
							std::cout << "OG - Addr: " << std::hex << static_cast<uint32_t>(addrStart) << " value is: " << std::hex << static_cast<uint32_t>(*getMemoryAt(addrStart)) << std::endl;
						std::cout << "Now for the copy" << std::endl;
						//Source:      XX00-XX9F   ;XX in range from 00-F1h
						//Destination: FE00-FE9F
						//costs 160 cycles (but not mapped yet).
						std::copy(memory.begin() + startAddress, memory.begin() + startAddress + 0x009F, memory.begin() + 0xFE00);
						for(uint16_t addrStart = 0xFE00; addrStart < (0xFE00 + 0x009F); addrStart++)
							std::cout << "Addr: " << std::hex << static_cast<uint32_t>(addrStart) << " value is: " << std::hex << static_cast<uint32_t>(*getMemoryAt(addrStart)) << std::endl;
						//DMA costs 160 CPU cycles
						memoryOpCost = 160;
						abort();
						return;
				}
				//if(addr == 0xFF47){
				//	std::cout << "Written to palette memory" << std::endl;
				//}
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