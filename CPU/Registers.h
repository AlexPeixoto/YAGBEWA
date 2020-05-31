#pragma once

namespace CPU {
	struct Registers {
		uint8_t A;
		uint8_t B;
		uint8_t C;
		uint8_t D;
		uint8_t E;
		uint8_t H;
		uint8_t L;
		//Stack pointer
		uintptr_t SP;
		//Program counter
		uintptr_t PC;

		struct F {
			uint8_t Z : 1;
			uint8_t N : 1;
			uint8_t H : 1;
			uint8_t C : 1;
			uint8_t _NOTUSED : 4;
		};
	};
}