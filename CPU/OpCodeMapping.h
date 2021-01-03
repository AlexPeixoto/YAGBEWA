#pragma once

#include <vector>
#include <functional>
#include <Memory/MemoryMap.h>
#include <OpStructure.h>

namespace CPU {
    class LR35902;
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

        //Flags checked from 0x0 to 7xf
        class Call{
            public:
                /*
                 * Instead of mapping it 1-1 based on the instructions table.
                 * The idea here is to map all the possible instructions and store the data on the OpStructure
                 * Have in mind that even if some instructions will have both registers as operands mapped, they might not be used
                 * to avoid the cost of de-reference it (even if the compiler might be able to optimize it), cases like XOR or AND that always operates
                 * on top of Register.A will still pass it via OpStructure, even if its not "called" via OpStructure.
                 */
                static void LD_REG16_REG16(char**, Memory::Map&, OpStructure&);
                static void LD_REG16_REG8(char**, Memory::Map&, OpStructure&);
                static void LD_REG8_REG16(char**, Memory::Map&, OpStructure&);
                static void LD_REG8_REG8(char**, Memory::Map&, OpStructure&);

                /* REGV, instead of taking the value itself this is treated as a pointer */
                static void LD_REG16V_REG8(char**, Memory::Map&, OpStructure&);
                static void LD_REG8_REG16V(char**, Memory::Map&, OpStructure&);

                static void LD_REG16_d16(char**, Memory::Map&, OpStructure&);
                static void LD_REG8_d8(char**, Memory::Map&, OpStructure&);
                static void LD_REGV_d16(char**, Memory::Map&, OpStructure&);
                static void LD_REG16V_d8(char**, Memory::Map&, OpStructure&);

                // Maps LD (HL+) A
                static void LD_HLI_REG(char**, Memory::Map&, OpStructure&);
                static void LD_HLD_REG(char**, Memory::Map&, OpStructure&);

                // Maps LD A (HL+)
                static void LD_REG_HLI(char**, Memory::Map&, OpStructure&);
                static void LD_REG_HLD(char**, Memory::Map&, OpStructure&);

                // SP specific LD instructions.
                static void LD_a16_SP(char**, Memory::Map&, OpStructure&);
                static void LD_HL_SP_r8(char**, Memory::Map&, OpStructure&);
                static void LD_SP_HL(char**, Memory::Map&, OpStructure&);

                // JUMP
                static void JR_r8(char**, Memory::Map&, OpStructure&);
                static void JR_C_r8(char**, Memory::Map&, OpStructure&);
                static void JR_NC_r8(char**, Memory::Map&, OpStructure&);
                static void JR_NZ_r8(char**, Memory::Map&, OpStructure&);
                static void JR_Z_r8(char**, Memory::Map&, OpStructure&);

                static void INC16(char**, Memory::Map&, OpStructure&);
                static void INC8(char**, Memory::Map&, OpStructure&);
                static void DEC16(char**, Memory::Map&, OpStructure&);
                static void DEC8(char**, Memory::Map&, OpStructure&);
                static void INC_REG16V(char**, Memory::Map&, OpStructure&);
                static void DEC_REG16V(char**, Memory::Map&, OpStructure&);

                static void ADD8(char**, Memory::Map&, OpStructure&);
                static void ADD8_REG16V(char**, Memory::Map&, OpStructure&);
                static void ADD16(char**, Memory::Map&, OpStructure&);
                static void ADC8(char**, Memory::Map&, OpStructure&);
                static void ADC8_REG16V(char**, Memory::Map&, OpStructure&);
                static void SUB8(char**, Memory::Map&, OpStructure&);
                static void SUB8_REG16V(char**, Memory::Map&, OpStructure&);
                static void SBC8(char**, Memory::Map&, OpStructure&);
                static void SBC8_REG16V(char**, Memory::Map&, OpStructure&);
                static void AND8(char**, Memory::Map&, OpStructure&);
                static void AND8_REG16V(char**, Memory::Map&, OpStructure&);
                static void XOR8(char**, Memory::Map&, OpStructure&);
                static void XOR8_REG16V(char**, Memory::Map&, OpStructure&);
                static void OR8(char**, Memory::Map&, OpStructure&);
                static void OR8_REG16V(char**, Memory::Map&, OpStructure&);
                static void CP8(char**, Memory::Map&, OpStructure&);
                static void CP8_REG16V(char**, Memory::Map&, OpStructure&);
                static void CPL(char**, Memory::Map&, OpStructure&);
                static void DAA(char**, Memory::Map&, OpStructure&);
                static void SCF(char**, Memory::Map&, OpStructure&);
                static void CCF(char**, Memory::Map&, OpStructure&);

                static void NOP(char**, Memory::Map&, OpStructure&);
                static void RLCA(char**, Memory::Map&, OpStructure&);
                static void RRCA(char**, Memory::Map&, OpStructure&);
                static void STOP(char**, Memory::Map&, OpStructure&);
                static void HALT(char**, Memory::Map&, OpStructure&);
                static void RLA(char**, Memory::Map&, OpStructure&);
                static void RRA(char**, Memory::Map&, OpStructure&);

                static void RET(char**, Memory::Map&, OpStructure&);

            private:
                //Internal push/pop instructions, those are not mapped to opcodes, but insteasd used
                static void _push8(Memory::Map&, uint8_t);
                static void _push16(Memory::Map&, uint16_t);
                static uint8_t _pop8(Memory::Map&);
                static uint16_t _pop16(Memory::Map&);
        };
    };
}