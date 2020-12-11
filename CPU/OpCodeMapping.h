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
                static void LD_REG16_REG16(char**, Memory::Map&, const OpStructure&);
                static void LD_REG16_REG8(char**, Memory::Map&, const OpStructure&);
                static void LD_REG8_REG16(char**, Memory::Map&, const OpStructure&);
                static void LD_REG8_REG8(char**, Memory::Map&, const OpStructure&);

                /* REGV, instead of taking the value itself this is treated as a pointer */
                static void LD_REGV_REG(char**, Memory::Map&, const OpStructure&);
                static void LD_REG_REGV(char**, Memory::Map&, const OpStructure&);

                static void LD_REG_d16(char**, Memory::Map&, const OpStructure&);
                static void LD_REGV_d16(char**, Memory::Map&, const OpStructure&);
                static void LD_REG_d8(char**, Memory::Map&, const OpStructure&);

                // Maps LD (HL+) A
                static void LD_HLP_REG(char**, Memory::Map&, const OpStructure&);
                static void LD_HLM_REG(char**, Memory::Map&, const OpStructure&);

                // Maps LD A (HL+)
                static void LD_REG_HLP(char**, Memory::Map&, const OpStructure&);
                static void LD_REG_HLM(char**, Memory::Map&, const OpStructure&);

                // SP specific LD instructions.
                static void LD_a16_SP(char**, Memory::Map&, const OpStructure&);
                static void LD_HL_SP_r8(char**, Memory::Map&, const OpStructure&);
                static void LD_SP_HL(char**, Memory::Map&, const OpStructure&);

                // JUMP
                static void JR_r8(char**, Memory::Map&, const OpStructure&);
                static void JR_NZ_r8(char**, Memory::Map&, const OpStructure&);
                static void JR_Z_r8(char**, Memory::Map&, const OpStructure&);

                static void INC(char**, Memory::Map&, const OpStructure&);
                static void DEC(char**, Memory::Map&, const OpStructure&);

                static void ADD(char**, Memory::Map&, const OpStructure&);
                static void ADC(char**, Memory::Map&, const OpStructure&);
                static void SUB(char**, Memory::Map&, const OpStructure&);
                static void SBC(char**, Memory::Map&, const OpStructure&);
                static void AND(char**, Memory::Map&, const OpStructure&);
                static void XOR(char**, Memory::Map&, const OpStructure&);
                static void OR(char**, Memory::Map&, const OpStructure&);
                static void CP(char**, Memory::Map&, const OpStructure&);
                static void CPL(char**, Memory::Map&, const OpStructure&);
                static void DDA(char**, Memory::Map&, const OpStructure&);

                static void NOP(char**, Memory::Map&, const OpStructure&);
                static void RLCA(char**, Memory::Map&, const OpStructure&);
                static void RRCA(char**, Memory::Map&, const OpStructure&);
                static void STOP(char**, Memory::Map&, const OpStructure&);
                static void RLA(char**, Memory::Map&, const OpStructure&);
                static void RRA(char**, Memory::Map&, const OpStructure&);


            // 0x[0..f]
            
        };
    };
}