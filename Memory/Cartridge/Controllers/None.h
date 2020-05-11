#include <header.h>
#include <Memory/MemoryMap.h>

namespace Memory {
	namespace Cartridge {
		namespace Controller {
			//Dumb class for cartridges without a controller
			class None {
			private:
				Memory::MemoryArray& mem;
			public:
				ControllerBase(Memory::MemoryArray& mem) : mem(mem) {};
				virtual ~ControllerBase();

				void loadCartridge() {

				}
				inline void executeBankSwitch(uint16_t bank) {
					std::runtime_error("No bank switching on this specific controller")
				}
			};
		}
	}
}