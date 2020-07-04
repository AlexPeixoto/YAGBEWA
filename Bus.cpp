#include <Bus.h>

Bus::Bus() : cpu(this), cartridge(this) {
}
Bus::~Bus () {}



void Bus::tick() {
	uint32_t clock = 0;
	while (true) {
		if (clock == 0) {	
		}
		--clock;
	}
}