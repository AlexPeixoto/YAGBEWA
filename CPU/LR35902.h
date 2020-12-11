#pragma once

#include <Registers.h>
#include <OpCodeMapping.h>


class Bus;

namespace CPU{
	class LR35902 {
	private:		
		static Registers registers;
        Bus* bus;
		OpCodeMapping mapping;
		// Cycles contains the "used cycles by the instruction"
		uint16_t cycles = 0;

		//OpCodeMapping needs access to the registers.
		friend class OpCodeMapping;
	public:LR35902(Bus* bus);
		~LR35902();

		void clock();
	};
}
