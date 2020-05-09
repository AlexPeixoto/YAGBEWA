#include <header.h>
#include <Memory/memory.h>

namespace Memory {
	namespace Cartridge {
		//Pure virtual class, will be used as a base to implement each one of the possible controllers
		class ControllerBase {
		private:
		public:
			ControllerBase(Memory::MemoryArray& bank1Location, Memory::MemoryArray& bank2Location);
			virtual ~ControllerBase();

			virtual void loadCartridge();
			virtual void executeBankSwitch(uint8_t bank);
		};
	}
}