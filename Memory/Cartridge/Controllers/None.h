#include <Memory/Cartridge/Header.h>
#include <Memory/MemoryMap.h>

namespace Memory::Cartridge::Controller {
	//Dumb class for cartridges without a controller
	class None : public ControllerBase {
	public:
		None() : ControllerBase() {};
		~None() {};

		void loadCartridge() {

		}
		inline void executeBankSwitch(uint16_t bank) {
			std::runtime_error("No bank switching on this specific controller");
		}
	};
}