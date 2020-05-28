#include <Memory/Cartridge/Header.h>
#include <Memory/MemoryMap.h>

//As the bank management is done by the cartridge controller, I am just  using this class to manage the load of the data
namespace Memory::Cartridge::Controller {
	//Pure virtual class, will be used as a base to implement each one of the possible controllers
	class ControllerBase {
	private:
		Memory::Map& mem;
	public:
		ControllerBase(Memory::Map& mem) : mem(mem) {};
		virtual ~ControllerBase() {};

		virtual void loadCartridge() = 0;
		virtual void executeBankSwitch(uint16_t bank) = 0;
	};
}