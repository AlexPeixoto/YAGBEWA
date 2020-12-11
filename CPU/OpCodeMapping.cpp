#include <OpCodeMapping.h>
#include <OpCodeMapping.h>
#include <LR35902.h>

using namespace CPU;
using OP = OpCodeMapping::Call;
OpCodeMapping::OpCodeMapping() :
    instructions({
        //0x[0..F]
        {/* 0x0 */ 1, OP::NOP}, {/* 0x1 */ 3, OP::LD_REG_d16, &LR35902::registers.BC._pair}, {/* 0x2 */ 1, OP::LD_REGV_REG, &LR35902::registers.BC._pair, &LR35902::registers.A}, {/* 0x3 */ 1, OP::INC, &LR35902::registers.BC._pair}, {/* 0x4 */ 1, OP::INC, &LR35902::registers.BC._reg[0]}, {/* 0x5 */ 1, OP::DEC, &LR35902::registers.BC._reg[0]}, {/* 0x6 */ 2, OP::LD_REG_d8, &LR35902::registers.BC._reg[0]}, {/* 0x7 */ 1, OP::RLCA}, {/* 0x8 */ 3, OP::LD_a16_SP}, {/* 0x9 */ 1, OP::ADD, &LR35902::registers.HL._pair, &LR35902::registers.BC._pair}, {/* 0xA */ 1, OP::LD_REG_REGV, &LR35902::registers.A, &LR35902::registers.BC._pair}, {/* 0xB */ 1, OP::DEC, &LR35902::registers.BC._pair}, {/* 0xC */ 1, OP::INC, &LR35902::registers.BC._reg[1]}, {/* 0xD */ 1, OP::DEC, &LR35902::registers.BC._reg[1]}, {/* 0xE */ 1, OP::LD_REG_d8, &LR35902::registers.BC._reg[1]}, {/* 0xF */ 1, OP::RRCA},
        //1x[0..F]
        {/* 1x0 */ 1, OP::STOP}, {/* 1x1 */ 3, OP::LD_REG_d16, &LR35902::registers.DE._pair}, {/* 1x2 */ 1, OP::LD_REGV_REG, &LR35902::registers.DE._pair, &LR35902::registers.A}, {/* 1x3 */ 1, OP::INC, &LR35902::registers.DE._pair}, {/* 1x4 */ 1, OP::INC, &LR35902::registers.DE._reg[0]}, {/* 1x5 */ 1, OP::DEC, &LR35902::registers.DE._reg[0]}, {/* 1x6 */ 2, OP::LD_REG_d8, &LR35902::registers.DE._reg[0]}, {/* 1x7 */ 1, OP::RLA}, {/* 1x8 */ 2, OP::JR_r8}, {/* 1x9 */ 1, OP::ADD, &LR35902::registers.HL._pair, &LR35902::registers.DE._pair}, {/* 1xA */ 1, OP::LD_REG_REGV, &LR35902::registers.A, &LR35902::registers.DE._pair}, {/* 1xB */ 1, OP::DEC, &LR35902::registers.BC._pair}, {/* 1xC */ 1, OP::INC, &LR35902::registers.DE._reg[1]}, {/* 1xD */ 1, OP::DEC, &LR35902::registers.DE._reg[1]}, {/* 1xE */ 1, OP::LD_REG_d8, &LR35902::registers.DE._reg[1]}, {/* 1xF */ 1, OP::RRA},
        //2x[0..F]
        {/* 2x0 */ 2, OP::JR_NZ_r8}, {/* 2x1 */ 3, OP::LD_REG_d16, &LR35902::registers.HL._pair}, {/* 2x2 */ 1, OP::LD_HLP_REG, &LR35902::registers.A}, {/* 2x3 */ 1, OP::INC, &LR35902::registers.HL._pair}, {/* 2x4 */ 1, OP::INC, &LR35902::registers.HL._reg[0]}, {/* 2x5 */ 1, OP::DEC, &LR35902::registers.HL._reg[0]}, {/* 2x6 */ 2, OP::LD_REG_d8, &LR35902::registers.HL._reg[0]}, {/* 2x7 */ 1, OP::DDA}, {/* 2x8 */ 2, OP::JR_Z_r8}, {/* 2x9 */ 1, OP::ADD, &LR35902::registers.HL._pair, &LR35902::registers.HL._pair}, {/* 2xA */ 1, OP::LD_REG_HLP, &LR35902::registers.A}, {/* 2xB */ 1, OP::DEC, &LR35902::registers.HL._pair}, {/* 2xC */ 1, OP::INC, &LR35902::registers.HL._reg[1]}, {/* 2xD */ 1, OP::DEC, &LR35902::registers.HL._reg[1]}, {/* 1xE */ 1, OP::LD_REG_d8, &LR35902::registers.HL._reg[1]}, {/* 1xF */ 1, OP::CPL}

    })
{}



void OpCodeMapping::Call::LD_REG_d16(char** pc, Memory::Map& memMap, const OpStructure& info){}

void OpCodeMapping::Call::LD_REG16_REG16(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG16_REG8(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG16(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG8(char** pc, Memory::Map& memMap, const OpStructure& info){}

void OpCodeMapping::Call::LD_REGV_REG(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG_REGV(char** pc, Memory::Map& memMap, const OpStructure& info){} 

void OpCodeMapping::Call::LD_REG_HLP(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG_HLM(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_HLP_REG(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_HLM_REG(char** pc, Memory::Map& memMap, const OpStructure& info){}

void OpCodeMapping::Call::LD_REGV_d16(char**, Memory::Map&, const OpStructure&){}

void OpCodeMapping::Call::LD_REG_d8(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_a16_SP(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::LD_HL_SP_r8(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::LD_SP_HL(char**, Memory::Map&, const OpStructure&){}

void OpCodeMapping::Call::JR_r8(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::JR_Z_r8(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::JR_NZ_r8(char** pc, Memory::Map& memMap, const OpStructure& info){}


void OpCodeMapping::Call::INC(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::DEC(char**, Memory::Map&, const OpStructure&){}

void OpCodeMapping::Call::ADD(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::ADC(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::SUB(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::SBC(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::AND(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::XOR(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::OR(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::CP(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::CPL(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::DDA(char**, Memory::Map&, const OpStructure&){}

void OpCodeMapping::Call::RLCA(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::STOP(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::NOP(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::RLA(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::RRA(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::RRCA(char** pc, Memory::Map& memMap, const OpStructure& info){}
