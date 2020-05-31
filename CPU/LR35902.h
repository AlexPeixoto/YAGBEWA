#pragma once

#include <Decoder.h>
#include <Registers.h>


class Bus;

namespace CPU{
	class LR35902 {
	private:
		Decoder decoder;
		Registers registers;
        Bus* bus;
	public:
        LR35902(Bus* bus);
		~LR35902();
	};
}
