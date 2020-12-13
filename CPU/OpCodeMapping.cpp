#include <OpCodeMapping.h>
#include <OpCodeMapping.h>
#include <LR35902.h>

using namespace CPU;
using OP = OpCodeMapping::Call;
OpCodeMapping::OpCodeMapping() :
    instructions({
        //0x[0..F]
        {/* 0x0 */ 4, OP::NOP}, {/* 0x1 */ 12, OP::LD_REG16_d16, &LR35902::registers.BC._pair}, {/* 0x2 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.BC._pair, &LR35902::registers.A}, {/* 0x3 */ 8, OP::INC16, &LR35902::registers.BC._pair}, {/* 0x4 */ 4, OP::INC8, &LR35902::registers.BC._reg[0]}, {/* 0x5 */ 4, OP::DEC8, &LR35902::registers.BC._reg[0]}, {/* 0x6 */ 8, OP::LD_REG8_d8, &LR35902::registers.BC._reg[0]}, {/* 0x7 */ 4, OP::RLCA}, {/* 0x8 */ 20, OP::LD_a16_SP}, {/* 0x9 */ 8, OP::ADD8, &LR35902::registers.HL._pair, &LR35902::registers.BC._pair}, {/* 0xA */ 8, OP::LD_REG8_REG16V, &LR35902::registers.A, &LR35902::registers.BC._pair}, {/* 0xB */ 8, OP::DEC16, &LR35902::registers.BC._pair}, {/* 0xC */ 4, OP::INC8, &LR35902::registers.BC._reg[1]}, {/* 0xD */ 4, OP::DEC8, &LR35902::registers.BC._reg[1]}, {/* 0xE */ 8, OP::LD_REG8_d8, &LR35902::registers.BC._reg[1]}, {/* 0xF */ 4, OP::RRCA},
        //1x[0..F]
        {/* 1x0 */ 4, OP::STOP}, {/* 1x1 */ 12, OP::LD_REG16_d16, &LR35902::registers.DE._pair}, {/* 1x2 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.DE._pair, &LR35902::registers.A}, {/* 1x3 */ 8, OP::INC16, &LR35902::registers.DE._pair}, {/* 1x4 */ 4, OP::INC8, &LR35902::registers.DE._reg[0]}, {/* 1x5 */ 4, OP::DEC8, &LR35902::registers.DE._reg[0]}, {/* 1x6 */ 8, OP::LD_REG8_d8, &LR35902::registers.DE._reg[0]}, {/* 1x7 */ 4, OP::RLA}, {/* 1x8 */ 12, OP::JR_r8}, {/* 1x9 */ 8, OP::ADD8, &LR35902::registers.HL._pair, &LR35902::registers.DE._pair}, {/* 1xA */ 8, OP::LD_REG8_REG16V, &LR35902::registers.A, &LR35902::registers.DE._pair}, {/* 1xB */ 8, OP::DEC16, &LR35902::registers.BC._pair}, {/* 1xC */ 4, OP::INC8, &LR35902::registers.DE._reg[1]}, {/* 1xD */ 4, OP::DEC8, &LR35902::registers.DE._reg[1]}, {/* 1xE */ 8, OP::LD_REG8_d8, &LR35902::registers.DE._reg[1]}, {/* 1xF */ 4, OP::RRA},
        //2x[0..F]
        //{/* 2x0 */ 2, OP::JR_NZ_r8}, {/* 2x1 */ 3, OP::LD_REG16_d16, &LR35902::registers.HL._pair}, {/* 2x2 */ 1, OP::LD_HLP_REG, &LR35902::registers.A}, {/* 2x3 */ 1, OP::INC, &LR35902::registers.HL._pair}, {/* 2x4 */ 1, OP::INC, &LR35902::registers.HL._reg[0]}, {/* 2x5 */ 1, OP::DEC, &LR35902::registers.HL._reg[0]}, {/* 2x6 */ 2, OP::LD_REG_d8, &LR35902::registers.HL._reg[0]}, {/* 2x7 */ 1, OP::DDA}, {/* 2x8 */ 2, OP::JR_Z_r8}, {/* 2x9 */ 1, OP::ADD8, &LR35902::registers.HL._pair, &LR35902::registers.HL._pair}, {/* 2xA */ 1, OP::LD_REG_HLP, &LR35902::registers.A}, {/* 2xB */ 1, OP::DEC, &LR35902::registers.HL._pair}, {/* 2xC */ 1, OP::INC, &LR35902::registers.HL._reg[1]}, {/* 2xD */ 1, OP::DEC, &LR35902::registers.HL._reg[1]}, {/* 1xE */ 1, OP::LD_REG_d8, &LR35902::registers.HL._reg[1]}, {/* 1xF */ 1, OP::CPL}

    })
{}
void OpCodeMapping::Call::STOP(char** pc, Memory::Map&, OpStructure&){
    //Also known as STOP 0 instruction 10 00.
    *pc+=1;
    LR35902::stop = true;
}

void OpCodeMapping::Call::LD_REG8_d8(char** pc, Memory::Map& memMap, OpStructure& info){
    *pc+=1;
    *(info.registers_8[0]) = **pc;
}
void OpCodeMapping::Call::LD_REG16_d16(char** pc, Memory::Map& memMap, OpStructure& info){
    *pc+=1;
    *(info.registers_16[0]) = **pc;
    *pc+=1;
    *(info.registers_16[0]) |= **pc << 8;
}

// Store value in register REG8 into byte pointed to by register r16.
void OpCodeMapping::Call::LD_REG16V_REG8(char** pc, Memory::Map& memMap, OpStructure& info){
    memMap.write(*(info.registers_8[0]), *(info.registers_16[0]));
}
//void OpCodeMapping::Call::LD_REG16_REG16(char** pc, Memory::Map& memMap, OpStructure& info){}

// Load value in register REG8 from byte pointed to by register r16.
void OpCodeMapping::Call::LD_REG8_REG16V(char** pc, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(*(info.registers_16[0]));
}

void OpCodeMapping::Call::LD_a16_SP(char** pc, Memory::Map&, OpStructure&){
    //This loads data on the stack pointer.
    //Here it is just pointing the SP to that specific address
    *pc+=1;
    LR35902::registers.SP = **pc;
    *pc+=1;
    LR35902::registers.SP |= **pc << 8;
}

void OpCodeMapping::Call::NOP(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::ADD8(char**, Memory::Map&, OpStructure& info){
    *(info.registers_8[1]) += *(info.registers_8[0]);
}
void OpCodeMapping::Call::INC8(char**, Memory::Map&, OpStructure& info){
    (*(info.registers_8[0]))++;
}
void OpCodeMapping::Call::DEC8(char**, Memory::Map&, OpStructure& info){
    (*(info.registers_8[0]))--;
}
void OpCodeMapping::Call::INC16(char**, Memory::Map&, OpStructure& info){
    (*(info.registers_16[0]))++;
}
void OpCodeMapping::Call::DEC16(char**, Memory::Map&, OpStructure& info){
    (*(info.registers_16[0]))--;
}

// In some instances here the 0x1 is redundant, but its left to make the intentions clear.
void OpCodeMapping::Call::RLCA(char**, Memory::Map&, OpStructure& info){
    LR35902::registers.F.C = (LR35902::registers.A >> 7) & 0x1;
    LR35902::registers.A = LR35902::registers.A << 1 | LR35902::registers.F.C & 0x1;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.H = LR35902::registers.F.N = 0;

}

void OpCodeMapping::Call::RLA(char** pc, Memory::Map& memMap, OpStructure& info){
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = (LR35902::registers.A >> 7) & 0x1;
    LR35902::registers.A = LR35902::registers.A << 1 | LR35902::registers.F._C & 0x1;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::RRCA(char** pc, Memory::Map& memMap, OpStructure& info){
    LR35902::registers.F.C = LR35902::registers.A & 0x1;
    LR35902::registers.A = LR35902::registers.A >> 1 | LR35902::registers.F.C << 7;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}


void OpCodeMapping::Call::RRA(char** pc, Memory::Map& memMap, OpStructure& info){
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = LR35902::registers.A & 0x1;
    LR35902::registers.A = LR35902::registers.A >> 1 | LR35902::registers.F._C << 7;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::JR_r8(char** pc, Memory::Map& memMap, OpStructure& info){
    *pc+=*(info.registers_8[0]);
}
//void OpCodeMapping::Call::JR_Z_r8(char** pc, Memory::Map& memMap, OpStructure& info){}
//void OpCodeMapping::Call::JR_NZ_r8(char** pc, Memory::Map& memMap, OpStructure& info){}

/*
void OpCodeMapping::Call::LD_REGV_d16(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::LD_REG16_REG8(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG16(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG8(char** pc, Memory::Map& memMap, OpStructure& info){}


 

void OpCodeMapping::Call::LD_REG_HLP(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG_HLM(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_HLP_REG(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_HLM_REG(char** pc, Memory::Map& memMap, OpStructure& info){}





void OpCodeMapping::Call::LD_HL_SP_r8(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::LD_SP_HL(char**, Memory::Map&, OpStructure&){}








void OpCodeMapping::Call::ADC(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::SUB(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::SBC(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::AND(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::XOR(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::OR(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::CP(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::CPL(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::DDA(char**, Memory::Map&, OpStructure&){}


void OpCodeMapping::Call::STOP(char**, Memory::Map&, OpStructure&){}



*/