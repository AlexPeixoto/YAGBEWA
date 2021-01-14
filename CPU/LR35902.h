#pragma once

#include <Registers.h>
#include <OpCodeMapping.h>


class Bus;

namespace CPU{
	enum class HaltType{
		Normal,
		Revert,
		NoInterruption,
		None
	};
	class LR35902 {
	private:
		//Perhaps make it non-static and pass this as a parameter for OpCodeMapping
		static Registers registers;
		// Some instructions might have extra cycles depending on specific conditions
		static uint8_t extraCycles;
		// Maps to stop instruction (can be resumed by a button press).
		static bool stop;
		// To re-enable interruptions on the next loop
		static bool enableInterruptions;
		// Check if moved the PC to another address, to prevent PC increment
		static bool changedPC;
		//Manages halt mode and halt bug
		static HaltType haltType;

        Bus* bus;
		OpCodeMapping mapping;
		// Cycles contains the "used cycles by the instruction"
		uint8_t cycles = 0;
		// Interruption delay, needs to think about that or if that can even become a problem
		//uint8_t instructionDelay = 0;

		//OpCodeMapping needs access to the registers.
		friend class OpCodeMapping;
		friend class OpCodeMapping::Call;
	public:
		LR35902(Bus* bus);
		~LR35902();

		void initPC();
		uint16_t tick();

		//"Interface" so the BUS can perform interruptions and other operations
		void pushPC();
		void popPC();
		void setPC(uint16_t target);

		static bool stopped() { return stop; }
		static bool interruptionsEnabled() { return enableInterruptions; }
		static bool disableInterruptions() { return enableInterruptions = false; }
		static HaltType getHaltType() { return haltType; }
		static void resetHalt() { haltType = HaltType::None; }
		
	};
}
