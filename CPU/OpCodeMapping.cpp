#include <OpCodeMapping.h>
#include <LR35902.h>

using namespace CPU;
using OP = OpCodeMapping::Call;
OpCodeMapping::OpCodeMapping() :
    instructions({
        //
        {/* 0x0 */ 1, OP::NOP}, {/* 0x1 */ 3, OP::LD_REG_d16, &LR35902::registers.BC._pair}, {/* 0x2 */ 1, OP::LD_REGV_REG, &LR35902::registers.BC._pair, &LR35902::registers.A}, {/* 0x3 */ 1, OP::INC, &LR35902::registers.BC._pair}, {/* 0x4 */ 1, OP::INC, &LR35902::registers.BC._reg[0]}, {/* 0x5 */ 1, OP::DEC, &LR35902::registers.BC._reg[0]}, {/* 0x6 */ 2, OP::LD_REG_d8, &LR35902::registers.BC._reg[0]}, {/* 0x7 */ 1, OP::RLCA}, {/* 0x8 */ 3, OP::LD_a16_SP}, {/* 0x9 */ 1, OP::ADD, &LR35902::registers.HL._pair, &LR35902::registers.BC._pair}, {/* 0xA */ 1, OP::LD_REG_REGV, &LR35902::registers.A, &LR35902::registers.BC._pair}, {/* 0xB */ 1, OP::DEC, &LR35902::registers.BC._pair}, {/* 0xC */ 1, OP::INC, &LR35902::registers.BC._reg[1]}, {/* 0xD */ 1, OP::DEC, &LR35902::registers.BC._reg[1]}
    })
{}

void OpCodeMapping::Call::NOP(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG_d16(char** pc, Memory::Map& memMap, const OpStructure& info){


}

void OpCodeMapping::Call::LD_REG16_REG16(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG16_REG8(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG16(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG8(char** pc, Memory::Map& memMap, const OpStructure& info){}

void OpCodeMapping::Call::LD_REGV_REG(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG_REGV(char** pc, Memory::Map& memMap, const OpStructure& info){} 


void OpCodeMapping::Call::LD_REGV_d16(char**, Memory::Map&, const OpStructure&){}

void OpCodeMapping::Call::LD_REG_d8(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_a16_SP(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::LD_HL_SP_r8(char**, Memory::Map&, const OpStructure&){}
void OpCodeMapping::Call::LD_SP_HL(char**, Memory::Map&, const OpStructure&){}


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

void OpCodeMapping::Call::RLCA(char**, Memory::Map&, const OpStructure&){}