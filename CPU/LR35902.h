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
	enum class IMEType{
		OnNext,
		Enabled,
		None
	};
	enum class INTERRUPTIONS_TYPE{
		VBLANK = 0,
		LCDC,
		TIMER,
		SERIAL,
		JOYP
	};
	class LR35902 {
	private:
		//Perhaps make it non-static and pass this as a parameter for OpCodeMapping
		Registers registers;
		// Some instructions might have extra cycles depending on specific conditions
		uint8_t extraCycles = 0;
		// Maps to stop instruction (can be resumed by a button press).
		bool stop = false;
		// Check if moved the PC to another address, to prevent PC increment
		bool changedPC = false;
		// To re-enable interruptions on the next loop
		IMEType imeType = IMEType::None;
		//Manages halt mode and halt bug
		HaltType haltType = HaltType::None;

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

		void initPC(bool headless);
		uint16_t tick();

		//"Interface" so the BUS can perform interruptions and other operations
		void pushPC();
		void popPC();
		void setPC(uint16_t target);

		bool stopped() { return stop; }
		void resume() { stop = false; }
		bool interruptionsEnabled() { return imeType == IMEType::Enabled; }
		void disableInterruptions() { imeType = IMEType::None; }
		//Interruptions are enabled on next loop
		void enableInterruptionIfOnNext() { 
			if(imeType == IMEType::OnNext)
				imeType = IMEType::Enabled;
		}
		HaltType getHaltType() { return haltType; }
		void resetHalt() { haltType = HaltType::None; }
		void setInterruptFlag(CPU::INTERRUPTIONS_TYPE type);

		bool isInterruptionPending();
		void performInterruption();
	};
}
