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
        OpCodeMapping(LR35902& cpu);

        void setMapping();
        void setCbMapping();
        uint16_t executeNext(LR35902&, Memory::Map& memMap);

        //Used for 
        void push16(LR35902& cpu, Memory::Map& memMap, uint16_t val) { Call::_push16(cpu, memMap, val); }
        uint16_t pop16(LR35902& cpu, Memory::Map& memMap) { return Call::_pop16(cpu, memMap); }
        
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
                static void LD_REG16_REG16(LR35902&, Memory::Map&, OpStructure&);
                static void LD_REG16_REG8(LR35902&, Memory::Map&, OpStructure&);
                static void LD_REG8_REG16(LR35902&, Memory::Map&, OpStructure&);
                static void LD_REG8_REG8(LR35902&, Memory::Map&, OpStructure&);

                /* REGV, instead of taking the value itself this is treated as a pointer */
                static void LD_REG16V_REG8(LR35902&, Memory::Map&, OpStructure&);
                static void LD_REG8_REG16V(LR35902&, Memory::Map&, OpStructure&);

                static void LD_REG16_d16(LR35902&, Memory::Map&, OpStructure&);
                static void LD_REG8_d8(LR35902&, Memory::Map&, OpStructure&);
                static void LD_REGV_d16(LR35902&, Memory::Map&, OpStructure&);
                static void LD_REG16V_d8(LR35902&, Memory::Map&, OpStructure&);

                // Maps LD (HL+) A/LD (HL-) A
                static void LD_HLI_REG(LR35902&, Memory::Map&, OpStructure&);
                static void LD_HLD_REG(LR35902&, Memory::Map&, OpStructure&);

                // Maps LD A (HL+)/LD A (HL-)
                static void LD_REG_HLI(LR35902&, Memory::Map&, OpStructure&);
                static void LD_REG_HLD(LR35902&, Memory::Map&, OpStructure&);

                // SP specific LD instructions.
                static void LD_a16_SP(LR35902&, Memory::Map&, OpStructure&);
                static void LD_HL_SP_r8(LR35902&, Memory::Map&, OpStructure&);
                static void LD_SP_HL(LR35902&, Memory::Map&, OpStructure&);

                static void LDH_a8_A(LR35902&, Memory::Map&, OpStructure&);
                static void LDH_A_a8(LR35902&, Memory::Map&, OpStructure&);
                static void LD_C_A(LR35902&, Memory::Map&, OpStructure&);
                static void LD_A_C(LR35902&, Memory::Map&, OpStructure&);
                static void LD_a16_A(LR35902&, Memory::Map&, OpStructure&);
                static void LD_A_a16(LR35902&, Memory::Map&, OpStructure&);

                // JUMP relative, adds to the current address
                static void JR_r8(LR35902&, Memory::Map&, OpStructure&);
                static void JR_NZ_r8(LR35902&, Memory::Map&, OpStructure&);
                static void JR_Z_r8(LR35902&, Memory::Map&, OpStructure&);
                static void JR_NC_r8(LR35902&, Memory::Map&, OpStructure&);
                static void JR_C_r8(LR35902&, Memory::Map&, OpStructure&);

                //JP
                static void JP_a16(LR35902&, Memory::Map&, OpStructure&);
                static void JP_NZ_a16(LR35902&, Memory::Map&, OpStructure&);
                static void JP_Z_a16(LR35902&, Memory::Map&, OpStructure&);
                static void JP_NC_a16(LR35902&, Memory::Map&, OpStructure&);
                static void JP_C_a16(LR35902&, Memory::Map&, OpStructure&);
                static void JP_HL(LR35902&, Memory::Map&, OpStructure&);
                
                //CALL
                static void CALL_a16(LR35902&, Memory::Map&, OpStructure&);
                static void CALL_NZ_a16(LR35902&, Memory::Map&, OpStructure&);
                static void CALL_Z_a16(LR35902&, Memory::Map&, OpStructure&);
                static void CALL_NC_a16(LR35902&, Memory::Map&, OpStructure&);
                static void CALL_C_a16(LR35902&, Memory::Map&, OpStructure&);

                //RET
                static void RET_NZ(LR35902&, Memory::Map&, OpStructure&);
                static void RET_Z(LR35902&, Memory::Map&, OpStructure&);
                static void RET_NC(LR35902&, Memory::Map&, OpStructure&);
                static void RET_C(LR35902&, Memory::Map&, OpStructure&);
                static void RET(LR35902&, Memory::Map&, OpStructure&);
                static void RETI(LR35902&, Memory::Map&, OpStructure&);

                //INC/DEC
                static void INC16(LR35902&, Memory::Map&, OpStructure&);
                static void INC8(LR35902&, Memory::Map&, OpStructure&);
                static void DEC16(LR35902&, Memory::Map&, OpStructure&);
                static void DEC8(LR35902&, Memory::Map&, OpStructure&);
                static void INC_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void DEC_REG16V(LR35902&, Memory::Map&, OpStructure&);

                //ADD, ADC, SUB, SBC
                static void ADD8(LR35902&, Memory::Map&, OpStructure&);
                static void ADD8_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void ADD8_d8(LR35902&, Memory::Map&, OpStructure&);
                static void ADD16(LR35902&, Memory::Map&, OpStructure&);
                static void ADD_SP_r8(LR35902&, Memory::Map&, OpStructure&);
                static void SUB8(LR35902&, Memory::Map&, OpStructure&);
                static void SUB8_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void SUB8_d8(LR35902&, Memory::Map&, OpStructure&);
                static void ADC8(LR35902&, Memory::Map&, OpStructure&);
                static void ADC8_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void ADC8_d8(LR35902&, Memory::Map&, OpStructure&);
                static void SBC8(LR35902&, Memory::Map&, OpStructure&);
                static void SBC8_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void SBC8_d8(LR35902&, Memory::Map&, OpStructure&);

                //AND, XOR, OR, CP
                static void AND8(LR35902&, Memory::Map&, OpStructure&);
                static void AND8_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void AND8_d8(LR35902&, Memory::Map&, OpStructure&);
                static void XOR8(LR35902&, Memory::Map&, OpStructure&);
                static void XOR8_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void XOR8_d8(LR35902&, Memory::Map&, OpStructure&);
                static void OR8(LR35902&, Memory::Map&, OpStructure&);
                static void OR8_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void OR8_d8(LR35902&, Memory::Map&, OpStructure&);
                static void CP8(LR35902&, Memory::Map&, OpStructure&);
                static void CP8_REG16V(LR35902&, Memory::Map&, OpStructure&);
                static void CP8_d8(LR35902&, Memory::Map&, OpStructure&);

                //RR and RL
                static void RLC(LR35902&, Memory::Map&, OpStructure&);
                static void RRC(LR35902&, Memory::Map&, OpStructure&);
                static void RL(LR35902&, Memory::Map&, OpStructure&);
                static void RR(LR35902&, Memory::Map&, OpStructure&);

                //HL Variant
                static void RLC_HL(LR35902&, Memory::Map&, OpStructure&);
                static void RRC_HL(LR35902&, Memory::Map&, OpStructure&);
                static void RL_HL(LR35902&, Memory::Map&, OpStructure&);
                static void RR_HL(LR35902&, Memory::Map&, OpStructure&);

                //A variant of the above (no Z check)
                static void RLCA(LR35902&, Memory::Map&, OpStructure&);
                static void RRCA(LR35902&, Memory::Map&, OpStructure&);
                static void RLA(LR35902&, Memory::Map&, OpStructure&);
                static void RRA(LR35902&, Memory::Map&, OpStructure&);

                //Bit shift operations
                static void SLA(LR35902&, Memory::Map&, OpStructure&);
                static void SLA_HL(LR35902&, Memory::Map&, OpStructure&);
                static void SRA(LR35902&, Memory::Map&, OpStructure&);
                static void SRA_HL(LR35902&, Memory::Map&, OpStructure&);
                static void SRL(LR35902&, Memory::Map&, OpStructure&);
                static void SRL_HL(LR35902&, Memory::Map&, OpStructure&);

                static void SWAP(LR35902&, Memory::Map&, OpStructure&);
                static void SWAP_HL(LR35902&, Memory::Map&, OpStructure&);

                static void CPL(LR35902&, Memory::Map&, OpStructure&);
                static void DAA(LR35902&, Memory::Map&, OpStructure&);
                static void SCF(LR35902&, Memory::Map&, OpStructure&);
                static void CCF(LR35902&, Memory::Map&, OpStructure&);

                static void PUSH(LR35902&, Memory::Map&, OpStructure&);
                static void PUSH_AF(LR35902&, Memory::Map&, OpStructure&);
                static void POP(LR35902&, Memory::Map&, OpStructure&);
                static void POP_AF(LR35902&, Memory::Map&, OpStructure&);
                static void NOP(LR35902&, Memory::Map&, OpStructure&);
                static void STOP(LR35902&, Memory::Map&, OpStructure&);
                static void HALT(LR35902&, Memory::Map&, OpStructure&);
                static void EI(LR35902&, Memory::Map&, OpStructure&);
                static void DI(LR35902&, Memory::Map&, OpStructure&);

                //Here I will read the next byte to figure out which cbInstruction I should call.
                static void CB_OPCODE(LR35902&, Memory::Map&, OpStructure&);

                //Internal rst instruction
                template<int target>
                static void _rst(LR35902&, Memory::Map&, OpStructure&);

                //Bit operations
                template<int N>
                static void _bit(LR35902&, Memory::Map&, OpStructure&);
                template<int N>
                static void _bit_hl(LR35902&, Memory::Map&, OpStructure&);
                template<int N>
                static void _res(LR35902&, Memory::Map&, OpStructure&);
                template<int N>
                static void _res_hl(LR35902&, Memory::Map&, OpStructure&);
                template<int N>
                static void _set(LR35902&, Memory::Map&, OpStructure&);
                template<int N>
                static void _set_hl(LR35902&, Memory::Map&, OpStructure&);

                //Maps invalid instructions
                static void ABORT(LR35902&, Memory::Map&, OpStructure&);

                //Used for interruption handling
                static void _push16(LR35902&, Memory::Map&, uint16_t);
                static uint16_t _pop16(LR35902&, Memory::Map&);

            private:
                //Internal push/pop instructions, those are not mapped to opcodes, but insteasd used
                static void _push8(LR35902&, Memory::Map&, uint8_t);
                static uint8_t _pop8(LR35902&, Memory::Map&);

                //Maps a more simple/generic ADC, SBC, ADD, SUB
                static void _adc(LR35902&, uint8_t);
                static void _sbc(LR35902&, uint8_t);
                static void _add(LR35902&, uint8_t);
                static void _sub(LR35902&, uint8_t);

                //Maps a more simple/generic AND, OR, XOR, CP
                static void _and(LR35902&, uint8_t);
                static void _or(LR35902&, uint8_t);
                static void _xor(LR35902&, uint8_t);
                static void _cp(LR35902&, uint8_t);

                //Maps a more simple/generic RL** and RR**
                static void _rr(LR35902&, OpStructure&, uint8_t, bool);
                static void _rl(LR35902&, OpStructure&, uint8_t, bool);

                
        };
        Call c;
    };
}