#include <header.h>
#include <Memory/MemoryMap.h>

namespace Memory {
	namespace Cartridge {
		namespace Controller {
			//Pure virtual class, will be used as a base to implement each one of the possible controllers
			class ControllerBase {
			private:
			public:
				ControllerBase(Memory::MemoryArray& mem);
				virtual ~ControllerBase() {};

				virtual void loadCartridge() = 0;
				virtual void executeBankSwitch(uint16_t bank) = 0;
			};
		}
	}
}