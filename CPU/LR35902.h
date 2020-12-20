#pragma once

#include <Registers.h>
#include <OpCodeMapping.h>


class Bus;

namespace CPU{
	class LR35902 {
	private:		
		static Registers registers;
		// Some instructions might have extra cycles depending on specific conditions
		static uint8_t extraCycles;
		// Maps to stop instruction (can be resumed by a button press).
		static bool stop;
		// Maps to halt instruction.
		static bool halt;
        Bus* bus;
		OpCodeMapping mapping;
		// Cycles contains the "used cycles by the instruction"
		uint8_t cycles = 0;

		//OpCodeMapping needs access to the registers.
		friend class OpCodeMapping;
		friend class OpCodeMapping::Call;
	public:
		LR35902(Bus* bus);
		~LR35902();

		void clock();
	};
}
