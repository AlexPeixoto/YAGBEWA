#include <OpCodeMapping.h>
#include <OpCodeMapping.h>
#include <LR35902.h>

using namespace CPU;
using OP = OpCodeMapping::Call;
OpCodeMapping::OpCodeMapping() :
    instructions({
        //0x[0..F]
        {/* 0x0 */ 4, OP::NOP}, {/* 0x1 */ 12, OP::LD_REG16_d16, &LR35902::registers.BC._pair}, {/* 0x2 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.BC._pair, &LR35902::registers.A}, {/* 0x3 */ 8, OP::INC16, &LR35902::registers.BC._pair}, {/* 0x4 */ 4, OP::INC8, &LR35902::registers.BC._reg[0]}, {/* 0x5 */ 4, OP::DEC8, &LR35902::registers.BC._reg[0]}, {/* 0x6 */ 8, OP::LD_REG8_d8, &LR35902::registers.BC._reg[0]}, {/* 0x7 */ 4, OP::RLCA}, {/* 0x8 */ 20, OP::LD_a16_SP}, {/* 0x9 */ 8, OP::ADD16, &LR35902::registers.HL._pair, &LR35902::registers.BC._pair}, {/* 0xA */ 8, OP::LD_REG8_REG16V, &LR35902::registers.A, &LR35902::registers.BC._pair}, {/* 0xB */ 8, OP::DEC16, &LR35902::registers.BC._pair}, {/* 0xC */ 4, OP::INC8, &LR35902::registers.BC._reg[1]}, {/* 0xD */ 4, OP::DEC8, &LR35902::registers.BC._reg[1]}, {/* 0xE */ 8, OP::LD_REG8_d8, &LR35902::registers.BC._reg[1]}, {/* 0xF */ 4, OP::RRCA},
        //1x[0..F]
        {/* 1x0 */ 4, OP::STOP}, {/* 1x1 */ 12, OP::LD_REG16_d16, &LR35902::registers.DE._pair}, {/* 1x2 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.DE._pair, &LR35902::registers.A}, {/* 1x3 */ 8, OP::INC16, &LR35902::registers.DE._pair}, {/* 1x4 */ 4, OP::INC8, &LR35902::registers.DE._reg[0]}, {/* 1x5 */ 4, OP::DEC8, &LR35902::registers.DE._reg[0]}, {/* 1x6 */ 8, OP::LD_REG8_d8, &LR35902::registers.DE._reg[0]}, {/* 1x7 */ 4, OP::RLA}, {/* 1x8 */ 12, OP::JR_r8}, {/* 1x9 */ 8, OP::ADD16, &LR35902::registers.HL._pair, &LR35902::registers.DE._pair}, {/* 1xA */ 8, OP::LD_REG8_REG16V, &LR35902::registers.A, &LR35902::registers.DE._pair}, {/* 1xB */ 8, OP::DEC16, &LR35902::registers.BC._pair}, {/* 1xC */ 4, OP::INC8, &LR35902::registers.DE._reg[1]}, {/* 1xD */ 4, OP::DEC8, &LR35902::registers.DE._reg[1]}, {/* 1xE */ 8, OP::LD_REG8_d8, &LR35902::registers.DE._reg[1]}, {/* 1xF */ 4, OP::RRA},
        //2x[0..F]
        {/* 2x0 */ 8, OP::JR_NZ_r8}, {/* 2x1 */ 12, OP::LD_REG16_d16, &LR35902::registers.HL._pair}, {/* 2x2 */ 8, OP::LD_HLI_REG, &LR35902::registers.A}, {/* 2x3 */ 8, OP::INC16, &LR35902::registers.HL._pair}, {/* 2x4 */ 4, OP::INC8, &LR35902::registers.HL._reg[0]}, {/* 2x5 */ 4, OP::DEC8, &LR35902::registers.HL._reg[0]}, {/* 2x6 */ 8, OP::LD_REG8_d8, &LR35902::registers.HL._reg[0]}, {/* 2x7 */ 4, OP::DAA}, {/* 2x8 */ 8, OP::JR_Z_r8}, {/* 2x9 */ 8, OP::ADD16, &LR35902::registers.HL._pair, &LR35902::registers.HL._pair}, {/* 2xA */ 8, OP::LD_REG_HLI, &LR35902::registers.A}, {/* 2xB */ 8, OP::DEC16, &LR35902::registers.HL._pair}, {/* 2xC */ 4, OP::INC8, &LR35902::registers.HL._reg[1]}, {/* 2xD */ 4, OP::DEC8, &LR35902::registers.HL._reg[1]}, {/* 2xE */ 8, OP::LD_REG8_d8, &LR35902::registers.HL._reg[1]}, {/* 1xF */ 4, OP::CPL},
        //3x[0..F]
        {/* 3x0 */ 8, OP::JR_NC_r8}, {/* 3x1 */ 12, OP::LD_REG16_d16, &LR35902::registers.HL._pair}, {/* 3x2 */ 8, OP::LD_HLD_REG, &LR35902::registers.A}, {/* 3x3 */ 8, OP::INC16, &LR35902::registers.SP}, {/* 3x4 */ 12, OP::INC_REG16V, &LR35902::registers.HL._pair}, {/* 3x5 */ 12, OP::DEC_REG16V, &LR35902::registers.HL._pair}, {/* 3x6 */ 12, OP::LD_REG16V_d8, &LR35902::registers.HL._pair}, {/* 3x7 */ 4, OP::SCF}, {/* 3x8 */ 8, OP::JR_C_r8}, {/* 3x9 */ 8, OP::ADD16, &LR35902::registers.HL._pair, &LR35902::registers.SP}, {/* 3xA */ 8, OP::LD_REG_HLD, &LR35902::registers.A}, {/* 3xB */ 8, OP::DEC16, &LR35902::registers.SP}, {/* 3xC */ 4, OP::INC8, &LR35902::registers.A}, {/* 3xD */ 4, OP::DEC8, &LR35902::registers.A}, {/* 3xE */ 8, OP::LD_REG8_d8, &LR35902::registers.A}, {/* 3xF */ 4, OP::CCF},
        //4x[0..F]
        //Some instructions that are used for consistency (like LD B, B.. LD C, C are being marked as a NOP)
        {/* 4x0 */ 4,  OP::LD_REG8_REG8, &LR35902::registers.BC._reg[0], &LR35902::registers.BC._reg[0]},  {/* 4x1 */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[0], &LR35902::registers.BC._reg[1]}, {/* 4x2 */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[0], &LR35902::registers.DE._reg[0]}, {/* 4x3 */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[0], &LR35902::registers.DE._reg[1]}, {/* 4x4 */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[0], &LR35902::registers.HL._reg[0]}, {/* 4x5 */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[0], &LR35902::registers.HL._reg[1]}, {/* 4x6 */ 8, OP::LD_REG8_REG16V, &LR35902::registers.BC._reg[0], &LR35902::registers.HL._pair}, {/* 4x7 */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[0], &LR35902::registers.A}, {/* 4x8 */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[1], &LR35902::registers.BC._reg[0]}, {/* 4x9 */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[1], &LR35902::registers.BC._reg[1]}, {/* 4xA */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[1], &LR35902::registers.DE._reg[0]}, {/* 4xB */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[1], &LR35902::registers.DE._reg[1]}, {/* 4xC */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[1], &LR35902::registers.HL._reg[0]}, {/* 4xD */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[1], &LR35902::registers.HL._reg[1]}, {/* 4xE */ 8, OP::LD_REG8_REG16V, &LR35902::registers.BC._reg[1], &LR35902::registers.HL._pair}, {/* 4xF */ 4, OP::LD_REG8_REG8, &LR35902::registers.BC._reg[1], &LR35902::registers.A},
        //5x[0..F]
        {/* 5x0 */ 4,  OP::LD_REG8_REG8, &LR35902::registers.DE._reg[0], &LR35902::registers.BC._reg[0]},  {/* 5x1 */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[0], &LR35902::registers.BC._reg[1]}, {/* 5x2 */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[0], &LR35902::registers.DE._reg[0]}, {/* 5x3 */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[0], &LR35902::registers.DE._reg[1]}, {/* 5x4 */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[0], &LR35902::registers.HL._reg[0]}, {/* 5x5 */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[0], &LR35902::registers.HL._reg[1]}, {/* 5x6 */ 8, OP::LD_REG8_REG16V, &LR35902::registers.DE._reg[0], &LR35902::registers.HL._pair}, {/* 5x7 */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[0], &LR35902::registers.A}, {/* 5x8 */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[1], &LR35902::registers.BC._reg[0]}, {/* 5x9 */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[1], &LR35902::registers.BC._reg[1]}, {/* 5xA */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[1], &LR35902::registers.DE._reg[0]}, {/* 5xB */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[1], &LR35902::registers.DE._reg[1]}, {/* 5xC */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[1], &LR35902::registers.HL._reg[0]}, {/* 5xD */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[1], &LR35902::registers.HL._reg[1]}, {/* 5xE */ 8, OP::LD_REG8_REG16V, &LR35902::registers.DE._reg[1], &LR35902::registers.HL._pair}, {/* 5xF */ 4, OP::LD_REG8_REG8, &LR35902::registers.DE._reg[1], &LR35902::registers.A},
        //6x[0..F]
        {/* 6x0 */ 4,  OP::LD_REG8_REG8, &LR35902::registers.HL._reg[0], &LR35902::registers.BC._reg[0]},  {/* 6x1 */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[0], &LR35902::registers.BC._reg[1]}, {/* 6x2 */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[0], &LR35902::registers.DE._reg[0]}, {/* 6x3 */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[0], &LR35902::registers.DE._reg[1]}, {/* 6x4 */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[0], &LR35902::registers.HL._reg[0]}, {/* 6x5 */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[0], &LR35902::registers.HL._reg[1]}, {/* 6x6 */ 8, OP::LD_REG8_REG16V, &LR35902::registers.HL._reg[0], &LR35902::registers.HL._pair}, {/* 6x7 */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[0], &LR35902::registers.A}, {/* 6x8 */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[1], &LR35902::registers.BC._reg[0]}, {/* 6x9 */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[1], &LR35902::registers.BC._reg[1]}, {/* 6xA */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[1], &LR35902::registers.DE._reg[0]}, {/* 6xB */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[1], &LR35902::registers.DE._reg[1]}, {/* 6xC */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[1], &LR35902::registers.HL._reg[0]}, {/* 6xD */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[1], &LR35902::registers.HL._reg[1]}, {/* 6xE */ 8, OP::LD_REG8_REG16V, &LR35902::registers.HL._reg[1], &LR35902::registers.HL._pair}, {/* 6xF */ 4, OP::LD_REG8_REG8, &LR35902::registers.HL._reg[1], &LR35902::registers.A},
        //7x[0..F]
        {/* 7x0 */ 8,  OP::LD_REG16V_REG8, &LR35902::registers.HL._pair, &LR35902::registers.BC._reg[0]},  {/* 7x1 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.HL._pair, &LR35902::registers.BC._reg[1]}, {/* 7x2 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.HL._pair, &LR35902::registers.DE._reg[0]}, {/* 7x3 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.HL._pair, &LR35902::registers.DE._reg[1]}, {/* 7x4 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.HL._pair, &LR35902::registers.HL._reg[0]}, {/* 7x5 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.HL._pair, &LR35902::registers.HL._reg[1]}, {/* 7x6 */ 4, OP::HALT}, {/* 7x7 */ 8, OP::LD_REG16V_REG8, &LR35902::registers.HL._pair, &LR35902::registers.A}, {/* 7x8 */ 4, OP::LD_REG8_REG8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]}, {/* 7x9 */ 4, OP::LD_REG8_REG8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* 7xA */ 4, OP::LD_REG8_REG8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* 7xB */ 4, OP::LD_REG8_REG8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* 7xC */ 4, OP::LD_REG8_REG8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* 7xD */ 4, OP::LD_REG8_REG8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* 7xE */ 8, OP::LD_REG8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* 7xF */ 8, OP::LD_REG8_REG8, &LR35902::registers.A, &LR35902::registers.A},
        //8x[0..F]
        {/* 8x0 */ 4,  OP::ADD8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]},  {/* 8x1 */ 4, OP::ADD8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* 8x2 */ 4, OP::ADD8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* 8x3 */ 4, OP::ADD8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* 8x4 */ 4, OP::ADD8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* 8x5 */ 4, OP::ADD8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* 8x6 */ 8, OP::ADD8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* 8x7 */ 4, OP::ADD8, &LR35902::registers.A, &LR35902::registers.A}, {/* 8x8 */ 4, OP::ADC8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]}, {/* 8x9 */ 4, OP::ADC8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* 8xA */ 4, OP::ADC8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* 8xB */ 4, OP::ADC8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* 8xC */ 4, OP::ADC8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* 8xD */ 4, OP::ADC8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* 8xE */ 8, OP::ADC8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* 8xF */ 4, OP::ADC8, &LR35902::registers.A, &LR35902::registers.A},
        //9x[0..F]
        {/* 9x0 */ 4,  OP::SUB8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]},  {/* 9x1 */ 4, OP::SUB8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* 9x2 */ 4, OP::SUB8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* 9x3 */ 4, OP::SUB8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* 9x4 */ 4, OP::SUB8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* 9x5 */ 4, OP::SUB8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* 9x6 */ 8, OP::SUB8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* 9x7 */ 4, OP::SUB8, &LR35902::registers.A, &LR35902::registers.A}, {/* 9x8 */ 4, OP::SBC8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]}, {/* 9x9 */ 4, OP::SBC8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* 9xA */ 4, OP::SBC8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* 9xB */ 4, OP::SBC8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* 9xC */ 4, OP::SBC8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* 9xD */ 4, OP::SBC8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* 9xE */ 8, OP::SBC8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* 9xF */ 4, OP::SBC8, &LR35902::registers.A, &LR35902::registers.A},

    })
{}
void OpCodeMapping::Call::HALT(char** pc, Memory::Map&, OpStructure&){
    LR35902::halt = true;
}

void OpCodeMapping::Call::STOP(char** pc, Memory::Map&, OpStructure&){
    //Also known as STOP 0 instruction 10 00.
    *pc+=1;
    LR35902::stop = true;
}

void OpCodeMapping::Call::LD_REG8_REG8(char** pc, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = *(info.registers_8[1]);
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

void OpCodeMapping::Call::LD_REG16V_d8(char** pc, Memory::Map& memMap, OpStructure& info){
    *pc+=1;
    memMap.write(
        **pc, //Write this value
        *(info.registers_16[0]) //At this location of the memory
    );
}

void OpCodeMapping::Call::LD_a16_SP(char** pc, Memory::Map& memMap, OpStructure&){
    *pc+=1;
    uint16_t addr = **pc;
    *pc+=1;
    addr |= **pc << 8;
    memMap.write(LR35902::registers.SP & 0XFF, addr);
    memMap.write(LR35902::registers.SP >> 8, addr+1);
    
}

void OpCodeMapping::Call::LD_HLI_REG(char** pc, Memory::Map& memMap, OpStructure& info){
    memMap.write(*info.registers_8[0], LR35902::registers.HL._pair);
    LR35902::registers.HL._pair++; 
}

void OpCodeMapping::Call::LD_HLD_REG(char** pc, Memory::Map& memMap, OpStructure& info){
    memMap.write(*info.registers_8[0], LR35902::registers.HL._pair);
    LR35902::registers.HL._pair--; 
}

void OpCodeMapping::Call::LD_REG_HLI(char** pc, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(LR35902::registers.HL._pair);
    LR35902::registers.HL._pair++; 
}

void OpCodeMapping::Call::LD_REG_HLD(char** pc, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(LR35902::registers.HL._pair);
    LR35902::registers.HL._pair--; 
}

void OpCodeMapping::Call::NOP(char** pc, Memory::Map& memMap, OpStructure& info){}

void OpCodeMapping::Call::ADC8(char**, Memory::Map&, OpStructure& info){
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = ((static_cast<uint32_t>(LR35902::registers.A) + *(info.registers_8[0]) + LR35902::registers.F._C) > 0xFF);
    //Overflow from 4th (or 3rd starting from 0) bit (1111) = > 16
    LR35902::registers.F.H = ((static_cast<uint32_t>(LR35902::registers.A) + *(info.registers_8[0]) + LR35902::registers.F._C) > 0xF);;
    LR35902::registers.A += *(info.registers_8[0]) + LR35902::registers.F._C;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::ADC8_REG16V(char**, Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = ((static_cast<uint32_t>(LR35902::registers.A) + val + LR35902::registers.F._C) > 0xFF);
    //Overflow from 4th (or 3rd starting from 0) bit (1111) = > 16
    LR35902::registers.F.H = ((static_cast<uint32_t>(LR35902::registers.A) + val + LR35902::registers.F._C) > 0xF);;
    LR35902::registers.A += val + LR35902::registers.F._C;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::SUB8(char**, Memory::Map&, OpStructure& info){
    //alternative LR35902::registers.F.H = ((*(info.registers_8[0]) & 0xF) < (sub & 0xF));
    LR35902::registers.F.H = ((( static_cast<int8_t>(*(info.registers_8[0]) & 0xF) - ((*(info.registers_8[1])& 0xF)))) < 0);
    LR35902::registers.F.C = ((static_cast<int16_t>(*(info.registers_8[0])) - *(info.registers_8[1])) < 0);
    *(info.registers_8[0]) -= *(info.registers_8[1]);
    LR35902::registers.F.Z = (*(info.registers_8[0]) == 0);
    LR35902::registers.F.N = 1;
}

void OpCodeMapping::Call::SUB8_REG16V(char**, Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    //alternative LR35902::registers.F.H = ((*(info.registers_8[0]) & 0xF) < (sub & 0xF));
    LR35902::registers.F.H = ((( static_cast<int8_t>(*(info.registers_8[0]) & 0xF) - ((val & 0xF)))) < 0);
    LR35902::registers.F.C = ((static_cast<int16_t>(*(info.registers_8[0])) - val) < 0);
    *(info.registers_8[0]) -= val;
    LR35902::registers.F.Z = (val == 0);
    LR35902::registers.F.N = 1;
}

void OpCodeMapping::Call::ADD8(char**, Memory::Map&, OpStructure& info){
    LR35902::registers.F.H = ((((*(info.registers_8[0]) & 0xF) + ((*(info.registers_8[1])& 0xF)))  & 0x10) == 0x10);
    LR35902::registers.F.C = ((static_cast<uint16_t>(*(info.registers_8[0])) + *(info.registers_8[1])) > 0xFF);
    *(info.registers_8[0]) += *(info.registers_8[1]);
    LR35902::registers.F.Z = (*(info.registers_8[0]) == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::ADD8_REG16V(char**, Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    LR35902::registers.F.H = ((((*(info.registers_8[0]) & 0xF) + ((val & 0xF)))  & 0x10) == 0x10);
    LR35902::registers.F.C = ((static_cast<uint16_t>(*(info.registers_8[0])) + val) > 0xFF);
    *(info.registers_8[0]) += val;
    LR35902::registers.F.Z = (*(info.registers_8[0]) == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::ADD16(char**, Memory::Map&, OpStructure& info){
    LR35902::registers.F.H = (((static_cast<int32_t>(*(info.registers_16[0]) & 0xFF) + ((*(info.registers_16[1]) & 0xFF))) & 0x100) == 0x100);
    LR35902::registers.F.C = ((static_cast<uint32_t>(*(info.registers_16[0])) + *(info.registers_16[1])) > 0xFFFF);
    *(info.registers_16[0]) += *(info.registers_16[1]);
    LR35902::registers.F.N = 0;
    
}
void OpCodeMapping::Call::INC8(char**, Memory::Map&, OpStructure& info){
    LR35902::registers.F.N = 0;
    // Trick to check half carry (https://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/)
                                //Get first 4 bits, add 1 and mask it with 0x10 (5th bit)
    LR35902::registers.F.H = ( ( ((*(info.registers_8[0]) & 0xF) + 1)     & 0x10) == 0x10);

    (*(info.registers_8[0]))++;
    LR35902::registers.F.Z = ((*(info.registers_8[0])) == 0);
}
void OpCodeMapping::Call::DEC8(char**, Memory::Map&, OpStructure& info){
    LR35902::registers.F.N = 1;
    //This raises the question if the values can be negative here.
    LR35902::registers.F.H = ( ( (static_cast<int8_t>(*(info.registers_8[0]) & 0xF) - 1)) < 0);
    (*(info.registers_8[0]))--;

    LR35902::registers.F.Z = ((*(info.registers_8[0])) == 0);
}

//Different from the 8 bit registers, this version does not set any flags
void OpCodeMapping::Call::INC16(char**, Memory::Map&, OpStructure& info){
    (*(info.registers_16[0]))++;
    LR35902::registers.F.N = 0;
}
void OpCodeMapping::Call::DEC16(char**, Memory::Map&, OpStructure& info){
    (*(info.registers_16[0]))--;
    LR35902::registers.F.N = 1;
}

void OpCodeMapping::Call::INC_REG16V(char**, Memory::Map& memMap, OpStructure& info){
    memMap.read(*(info.registers_16[0]))++;
}
void OpCodeMapping::Call::DEC_REG16V(char**, Memory::Map& memMap, OpStructure& info){
    memMap.read(*(info.registers_16[0]))--;
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

void OpCodeMapping::Call::CPL(char**, Memory::Map&, OpStructure&){
    LR35902::registers.A = ~LR35902::registers.A;
    LR35902::registers.F.H = LR35902::registers.F.N = 1;
}

void OpCodeMapping::Call::SCF(char**, Memory::Map&, OpStructure&){
    LR35902::registers.F.C = 1;
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::CCF(char**, Memory::Map&, OpStructure&){
    LR35902::registers.F.C = ~LR35902::registers.F.C;
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::DAA(char**, Memory::Map&, OpStructure&){
    uint8_t& a = LR35902::registers.A;

    // From https://forums.nesdev.com/viewtopic.php?t=15944.
    if (!LR35902::registers.F.N) {  
        // after an addition, adjust if (half-)carry occurred or if result is out of bounds
        if (LR35902::registers.F.C || a > 0x9F) { a += 0x60; LR35902::registers.F.C = 1; }
        if (LR35902::registers.F.H || (a & 0xF) > 9) { a += 0x6; }
        
    } else {  
        // after a subtraction, only adjust if (half-)carry occurred
        if (LR35902::registers.F.C) { a -= 0x60; }
        if (LR35902::registers.F.H) { a -= 0x6; }
    }
    // these flags are always updated
    LR35902::registers.F.Z = (a == 0); // the usual z flag
    LR35902::registers.F.H = 0; // h flag is always cleared
    LR35902::registers.A = a;
}

void OpCodeMapping::Call::JR_r8(char** pc, Memory::Map& memMap, OpStructure& info){
    *pc+=*(info.registers_8[0]);
}

void OpCodeMapping::Call::JR_Z_r8(char** pc, Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if( LR35902::registers.F.Z ) {
       *pc+= (*(info.registers_8[0]));
       LR35902::extraCycles=1;
    }
}

void OpCodeMapping::Call::JR_C_r8(char** pc, Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if( LR35902::registers.F.C ) {
       *pc+= (*(info.registers_8[0]));
       LR35902::extraCycles=1;
    }
}


void OpCodeMapping::Call::JR_NZ_r8(char** pc, Memory::Map& memMap, OpStructure& info){
    // jump if Z is not set
    if( !LR35902::registers.F.Z ) {
       *pc+= (*(info.registers_8[0]));
       LR35902::extraCycles=1;
    }
}

void OpCodeMapping::Call::JR_NC_r8(char** pc, Memory::Map& memMap, OpStructure& info){
    // jump if C is not set
    if( !LR35902::registers.F.C ) {
       *pc+= (*(info.registers_8[0]));
       LR35902::extraCycles=1;
    }
}
//void OpCodeMapping::Call::JR_Z_r8(char** pc, Memory::Map& memMap, OpStructure& info){}



template<int N>
void bit(){
    int a = 1 << N;
}
/*
void OpCodeMapping::Call::LD_REGV_d16(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::LD_REG16_REG8(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG16(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG8(char** pc, Memory::Map& memMap, OpStructure& info){}


 

void OpCodeMapping::Call::LD_REG_HLI(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG_HLD(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_HLI_REG(char** pc, Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_HLD_REG(char** pc, Memory::Map& memMap, OpStructure& info){}





void OpCodeMapping::Call::LD_HL_SP_r8(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::LD_SP_HL(char**, Memory::Map&, OpStructure&){}








void OpCodeMapping::Call::ADC(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::SUB(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::SBC(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::AND(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::XOR(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::OR(char**, Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::CP(char**, Memory::Map&, OpStructure&){}



void OpCodeMapping::Call::STOP(char**, Memory::Map&, OpStructure&){}



*/