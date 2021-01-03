#pragma once

#include <cstdint>

namespace CPU {
	struct Registers {
		uint8_t A;
		union BC {
			uint16_t _pair;
			uint8_t _reg[2];
		} BC;
		union DE {
			uint16_t _pair;
			uint8_t _reg[2];
		} DE;
		union HL {
			uint16_t _pair;
			uint8_t _reg[2];
		} HL;
		//Stack pointer
		uint16_t SP;
		//Program counter
		uint8_t  **PC;

		struct F {
			uint8_t Z : 1;
			uint8_t N : 1;
			uint8_t H : 1;
			uint8_t C : 1;
			uint8_t _C : 1; //This is used so in instructions like RLCA we can use as a temp for C.
			uint8_t _NOTUSED : 3;
		} F;
	};
}