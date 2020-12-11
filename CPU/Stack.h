#include <stack>

namespace CPU {
	struct StackElement {
		//Pointer containing the program counter
		uint16_t ptr;
		
	};
	//Used to push/pop registers
	std::stack<uint16_t> registers;
	//Stores the call stack, used to go back to previous states when ret is reached
	std::stack<StackElement> callStack;
}