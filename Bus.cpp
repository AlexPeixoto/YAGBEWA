#include <Bus.h>

Bus::Bus() : cpu(this), cartridge(this) {
}
Bus::~Bus () {}



void Bus::runCycle() {
	//first ensure that we point to the correct address
	cpu.initPC();
	uint32_t clock = 0;
	while (true) {
		cpu.tick();
		/*if (clock == 0) {	

		}
		--clock;*/
		clock++;
	}
}