#pragma once

#include <vector>
#include <functional>
#include <Memory/MemoryMap.h>
#include <OpStructure.h>

class Bus;
namespace CPU {    
    // For a lack of a better name, this is a class that maps all the instruction executions
    class OpCodeMapping {
        private:
        // The instruction function is the one responsible for moving the PC.
        // Instead of having 1 method per instruction, we can have a lookup table with some arguments
        static std::vector<OpStructure> instructions;
        static std::vector<OpStructure> cbInstructions;

        public:
        OpCodeMapping();

        void setMapping();
        void setCbMapping();
        uint16_t executeNext(Bus& bus);

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
                static void LD_REG16_REG16(Bus&, OpStructure&);
                static void LD_REG16_REG8(Bus&, OpStructure&);
                static void LD_REG8_REG16(Bus&, OpStructure&);
                static void LD_REG8_REG8(Bus&, OpStructure&);

                /* REGV, instead of taking the value itself this is treated as a pointer */
                static void LD_REG16V_REG8(Bus&, OpStructure&);
                static void LD_REG8_REG16V(Bus&, OpStructure&);

                static void LD_REG16_d16(Bus&, OpStructure&);
                static void LD_REG8_d8(Bus&, OpStructure&);
                static void LD_REGV_d16(Bus&, OpStructure&);
                static void LD_REG16V_d8(Bus&, OpStructure&);

                // Maps LD (HL+) A/LD (HL-) A
                static void LD_HLI_REG(Bus&, OpStructure&);
                static void LD_HLD_REG(Bus&, OpStructure&);

                // Maps LD A (HL+)/LD A (HL-)
                static void LD_REG_HLI(Bus&, OpStructure&);
                static void LD_REG_HLD(Bus&, OpStructure&);

                // SP specific LD instructions.
                static void LD_a16_SP(Bus&, OpStructure&);
                static void LD_HL_SP_r8(Bus&, OpStructure&);
                static void LD_SP_HL(Bus&, OpStructure&);

                static void LDH_a8_A(Bus&, OpStructure&);
                static void LDH_A_a8(Bus&, OpStructure&);
                static void LD_C_A(Bus&, OpStructure&);
                static void LD_A_C(Bus&, OpStructure&);
                static void LD_a16_A(Bus&, OpStructure&);
                static void LD_A_a16(Bus&, OpStructure&);

                // JUMP relative, adds to the current address
                static void JR_r8(Bus&, OpStructure&);
                static void JR_NZ_r8(Bus&, OpStructure&);
                static void JR_Z_r8(Bus&, OpStructure&);
                static void JR_NC_r8(Bus&, OpStructure&);
                static void JR_C_r8(Bus&, OpStructure&);

                //JP
                static void JP_a16(Bus&, OpStructure&);
                static void JP_NZ_a16(Bus&, OpStructure&);
                static void JP_Z_a16(Bus&, OpStructure&);
                static void JP_NC_a16(Bus&, OpStructure&);
                static void JP_C_a16(Bus&, OpStructure&);
                static void JP_HL(Bus&, OpStructure&);
                
                //CALL
                static void CALL_a16(Bus&, OpStructure&);
                static void CALL_NZ_a16(Bus&, OpStructure&);
                static void CALL_Z_a16(Bus&, OpStructure&);
                static void CALL_NC_a16(Bus&, OpStructure&);
                static void CALL_C_a16(Bus&, OpStructure&);

                //RET
                static void RET_NZ(Bus&, OpStructure&);
                static void RET_Z(Bus&, OpStructure&);
                static void RET_NC(Bus&, OpStructure&);
                static void RET_C(Bus&, OpStructure&);
                static void RET(Bus&, OpStructure&);
                static void RETI(Bus&, OpStructure&);

                //INC/DEC
                static void INC16(Bus&, OpStructure&);
                static void INC8(Bus&, OpStructure&);
                static void DEC16(Bus&, OpStructure&);
                static void DEC8(Bus&, OpStructure&);
                static void INC_REG16V(Bus&, OpStructure&);
                static void DEC_REG16V(Bus&, OpStructure&);

                //ADD, ADC, SUB, SBC
                static void ADD8(Bus&, OpStructure&);
                static void ADD8_REG16V(Bus&, OpStructure&);
                static void ADD8_d8(Bus&, OpStructure&);
                static void ADD16(Bus&, OpStructure&);
                static void ADD_SP_r8(Bus&, OpStructure&);
                static void SUB8(Bus&, OpStructure&);
                static void SUB8_REG16V(Bus&, OpStructure&);
                static void SUB8_d8(Bus&, OpStructure&);
                static void ADC8(Bus&, OpStructure&);
                static void ADC8_REG16V(Bus&, OpStructure&);
                static void ADC8_d8(Bus&, OpStructure&);
                static void SBC8(Bus&, OpStructure&);
                static void SBC8_REG16V(Bus&, OpStructure&);
                static void SBC8_d8(Bus&, OpStructure&);

                //AND, XOR, OR, CP
                static void AND8(Bus&, OpStructure&);
                static void AND8_REG16V(Bus&, OpStructure&);
                static void AND8_d8(Bus&, OpStructure&);
                static void XOR8(Bus&, OpStructure&);
                static void XOR8_REG16V(Bus&, OpStructure&);
                static void XOR8_d8(Bus&, OpStructure&);
                static void OR8(Bus&, OpStructure&);
                static void OR8_REG16V(Bus&, OpStructure&);
                static void OR8_d8(Bus&, OpStructure&);
                static void CP8(Bus&, OpStructure&);
                static void CP8_REG16V(Bus&, OpStructure&);
                static void CP8_d8(Bus&, OpStructure&);

                //RR and RL
                static void RLC(Bus&, OpStructure&);
                static void RRC(Bus&, OpStructure&);
                static void RL(Bus&, OpStructure&);
                static void RR(Bus&, OpStructure&);

                //HL Variant
                static void RLC_HL(Bus&, OpStructure&);
                static void RRC_HL(Bus&, OpStructure&);
                static void RL_HL(Bus&, OpStructure&);
                static void RR_HL(Bus&, OpStructure&);

                //A variant of the above (no Z check)
                static void RLCA(Bus&, OpStructure&);
                static void RRCA(Bus&, OpStructure&);
                static void RLA(Bus&, OpStructure&);
                static void RRA(Bus&, OpStructure&);

                //Bit shift operations
                static void SLA(Bus&, OpStructure&);
                static void SLA_HL(Bus&, OpStructure&);
                static void SRA(Bus&, OpStructure&);
                static void SRA_HL(Bus&, OpStructure&);
                static void SRL(Bus&, OpStructure&);
                static void SRL_HL(Bus&, OpStructure&);

                static void SWAP(Bus&, OpStructure&);
                static void SWAP_HL(Bus&, OpStructure&);

                static void CPL(Bus&, OpStructure&);
                static void DAA(Bus&, OpStructure&);
                static void SCF(Bus&, OpStructure&);
                static void CCF(Bus&, OpStructure&);

                static void PUSH(Bus&, OpStructure&);
                static void PUSH_AF(Bus&, OpStructure&);
                static void POP(Bus&, OpStructure&);
                static void POP_AF(Bus&, OpStructure&);
                static void NOP(Bus&, OpStructure&);
                static void STOP(Bus&, OpStructure&);
                static void HALT(Bus&, OpStructure&);
                static void EI(Bus&, OpStructure&);
                static void DI(Bus&, OpStructure&);

                //Here I will read the next byte to figure out which cbInstruction I should call.
                static void CB_OPCODE(Bus&, OpStructure&);

                //Internal rst instruction
                template<int target>
                static void _rst(Bus&, OpStructure&);

                //Bit operations
                template<int N>
                static void _bit(Bus&, OpStructure&);
                template<int N>
                static void _bit_hl(Bus&, OpStructure&);
                template<int N>
                static void _res(Bus&, OpStructure&);
                template<int N>
                static void _res_hl(Bus&, OpStructure&);
                template<int N>
                static void _set(Bus&, OpStructure&);
                template<int N>
                static void _set_hl(Bus&, OpStructure&);

                //Maps invalid instructions
                static void ABORT(Bus&, OpStructure&);

            private:
                //Internal push/pop instructions, those are not mapped to opcodes, but insteasd used
                static void _push8(Bus&, uint8_t);
                static void _push16(Bus&, uint16_t);
                static uint8_t _pop8(Bus&);
                static uint16_t _pop16(Bus&);

                //Maps a more simple/generic ADC, SBC, ADD, SUB
                static void _adc(uint8_t);
                static void _sbc(uint8_t);
                static void _add(uint8_t);
                static void _sub(uint8_t);

                //Maps a more simple/generic AND, OR, XOR, CP
                static void _and(uint8_t);
                static void _or(uint8_t);
                static void _xor(uint8_t);
                static void _cp(uint8_t);

                //Maps a more simple/generic RL** and RR**
                static void _rr(OpStructure&, uint8_t, bool);
                static void _rl(OpStructure&, uint8_t, bool);

                
        };
    };
}