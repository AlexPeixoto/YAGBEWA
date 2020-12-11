#pragma once

#include <vector>
#include <functional>
#include <Memory/MemoryMap.h>
#include <OpStructure.h>

namespace CPU {
    // For a lack of a better name, this is a class that maps all the instruction executions
    class OpCodeMapping {
        private:
        // The instruction function is the one responsible for moving the PC.
        // Instead of having 1 method per instruction, we can have a lookup table with some arguments
        std::vector<OpStructure> instructions;
        std::vector<OpStructure> cbInstructions;

        public:
        OpCodeMapping();

        void setMapping();
        void setCbMapping();

        class Call{
            public:
                static void NOP(char**, Memory::Map&, const OpStructure&);

                static void LD_REG_REG(char**, Memory::Map&, const OpStructure&);
                static void LD_REGV_REG(char**, Memory::Map&, const OpStructure&);

                static void LD_REG_d16(char**, Memory::Map&, const OpStructure&);
                static void LD_REGV_d16(char**, Memory::Map&, const OpStructure&);
                static void LD_REG_d8(char**, Memory::Map&, const OpStructure&);

                static void LD_a16_REG(char**, Memory::Map&, const OpStructure&);

                static void INC(char**, Memory::Map&, const OpStructure&);
                static void DEC(char**, Memory::Map&, const OpStructure&);
            // 0x[0..f]
            
        };
    };
}