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
        //Ax[0..F]
        {/* Ax0 */ 4,  OP::AND8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]},  {/* Ax1 */ 4, OP::AND8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* Ax2 */ 4, OP::AND8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* Ax3 */ 4, OP::AND8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* Ax4 */ 4, OP::AND8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* Ax5 */ 4, OP::AND8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* Ax6 */ 8, OP::AND8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* Ax7 */ 4, OP::AND8, &LR35902::registers.A, &LR35902::registers.A}, {/* Ax8 */ 4, OP::XOR8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]}, {/* Ax9 */ 4, OP::XOR8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* AxA */ 4, OP::XOR8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* AxB */ 4, OP::XOR8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* AxC */ 4, OP::XOR8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* AxD */ 4, OP::XOR8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* AxE */ 8, OP::XOR8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* AxF */ 4, OP::XOR8, &LR35902::registers.A, &LR35902::registers.A},
        //Bx[0..F]
        {/* Bx0 */ 4,  OP::OR8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]},  {/* Bx1 */ 4,  OP::OR8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* Bx2 */ 4,  OP::OR8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* Bx3 */ 4,  OP::OR8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* Bx4 */ 4,  OP::OR8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* Bx5 */ 4,  OP::OR8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* Bx6 */ 8,  OP::OR8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* Bx7 */ 4,  OP::OR8, &LR35902::registers.A, &LR35902::registers.A}, {/* Bx8 */ 4,  OP::CP8, &LR35902::registers.A, &LR35902::registers.BC._reg[0]}, {/* Bx9 */ 4,  OP::CP8, &LR35902::registers.A, &LR35902::registers.BC._reg[1]}, {/* BxA */ 4,  OP::CP8, &LR35902::registers.A, &LR35902::registers.DE._reg[0]}, {/* BxB */ 4,  OP::CP8, &LR35902::registers.A, &LR35902::registers.DE._reg[1]}, {/* BxC */ 4,  OP::CP8, &LR35902::registers.A, &LR35902::registers.HL._reg[0]}, {/* BxD */ 4,  OP::CP8, &LR35902::registers.A, &LR35902::registers.HL._reg[1]}, {/* BxE */ 8,  OP::CP8_REG16V, &LR35902::registers.A, &LR35902::registers.HL._pair}, {/* BxF */ 4,  OP::CP8, &LR35902::registers.A, &LR35902::registers.A},
        //Cx[0..F]
        {/* Cx0 */ 8,  OP::RET_NZ}, {/* Cx1 */ 12,  OP::POP, &LR35902::registers.BC._pair}, {/* Cx2 */ 12,  OP::JP_NZ_a16}, {/* Cx2 */ 16,  OP::JP_a16},


    })
{}
void OpCodeMapping::Call::HALT(Memory::Map&, OpStructure&){
    LR35902::halt = true;
}

void OpCodeMapping::Call::STOP(Memory::Map&, OpStructure&){
    //Also known as STOP 0 instruction 10 00.
    *LR35902::registers.PC+=1;
    LR35902::stop = true;
}

void OpCodeMapping::Call::LD_REG8_REG8(Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = *(info.registers_8[1]);
}

void OpCodeMapping::Call::LD_REG8_d8(Memory::Map& memMap, OpStructure& info){
    *LR35902::registers.PC+=1;
    *(info.registers_8[0]) = **LR35902::registers.PC;
}

void OpCodeMapping::Call::LD_REG16_d16(Memory::Map& memMap, OpStructure& info){
    *LR35902::registers.PC+=1;
    *(info.registers_16[0]) = **LR35902::registers.PC;
    *LR35902::registers.PC+=1;
    *(info.registers_16[0]) |= **LR35902::registers.PC << 8;
}

// Store value in register REG8 into byte pointed to by register r16.
void OpCodeMapping::Call::LD_REG16V_REG8(Memory::Map& memMap, OpStructure& info){
    memMap.write(*(info.registers_8[0]), *(info.registers_16[0]));
}
//void OpCodeMapping::Call::LD_REG16_REG16(Memory::Map& memMap, OpStructure& info){}

// Load value in register REG8 from byte pointed to by register r16.
void OpCodeMapping::Call::LD_REG8_REG16V(Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(*(info.registers_16[0]));
}

void OpCodeMapping::Call::LD_REG16V_d8(Memory::Map& memMap, OpStructure& info){
    *LR35902::registers.PC+=1;
    memMap.write(
        **LR35902::registers.PC, //Write this value
        *(info.registers_16[0]) //At this location of the memory
    );
}

void OpCodeMapping::Call::LD_a16_SP(Memory::Map& memMap, OpStructure&){
    *LR35902::registers.PC+=1;
    uint16_t addr = **LR35902::registers.PC;
    *LR35902::registers.PC+=1;
    addr |= **LR35902::registers.PC << 8;
    //Store SP & $FF at address n16 and SP >> 8 at address n16 + 1.
    memMap.write(LR35902::registers.SP & 0XFF, addr);
    memMap.write(LR35902::registers.SP >> 8, addr+1);
}

void OpCodeMapping::Call::LD_HLI_REG(Memory::Map& memMap, OpStructure& info){
    memMap.write(*info.registers_8[0], LR35902::registers.HL._pair);
    LR35902::registers.HL._pair++; 
}

void OpCodeMapping::Call::LD_HLD_REG(Memory::Map& memMap, OpStructure& info){
    memMap.write(*info.registers_8[0], LR35902::registers.HL._pair);
    LR35902::registers.HL._pair--; 
}

void OpCodeMapping::Call::LD_REG_HLI(Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(LR35902::registers.HL._pair);
    LR35902::registers.HL._pair++; 
}

void OpCodeMapping::Call::LD_REG_HLD(Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(LR35902::registers.HL._pair);
    LR35902::registers.HL._pair--; 
}

void OpCodeMapping::Call::NOP(Memory::Map& memMap, OpStructure& info){}

void OpCodeMapping::Call::ADC8(Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = ((static_cast<uint32_t>(LR35902::registers.A) + val + LR35902::registers.F._C) > 0xFF);
    //Overflow from 4th (or 3rd starting from 0) bit (1111) = > 16
    LR35902::registers.F.H = ((static_cast<uint16_t>(LR35902::registers.A) + val + LR35902::registers.F._C) > 0xF);
    LR35902::registers.A += val + LR35902::registers.F._C;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::ADC8_REG16V(Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = ((static_cast<uint32_t>(LR35902::registers.A) + val + LR35902::registers.F._C) > 0xFF);
    //Overflow from 4th (or 3rd starting from 0) bit (1111) = > 16
    LR35902::registers.F.H = ((static_cast<uint32_t>(LR35902::registers.A) + val + LR35902::registers.F._C) > 0xF);
    LR35902::registers.A += val + LR35902::registers.F._C;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::SBC8(Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = ((static_cast<uint32_t>(LR35902::registers.A) - val - LR35902::registers.F._C) > 0xFF);
    //Overflow from 4th (or 3rd starting from 0) bit (1111) = > 16
    LR35902::registers.F.H = ((static_cast<uint32_t>(LR35902::registers.A) - val - LR35902::registers.F._C) > 0xF);
    LR35902::registers.A -= val - LR35902::registers.F._C;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::SBC8_REG16V(Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.H = ((static_cast<int8_t>(LR35902::registers.A & 0xF) - (val & 0xF) - LR35902::registers.F._C) < 0);
    LR35902::registers.F.C = ((static_cast<int16_t>(LR35902::registers.A) - val - LR35902::registers.F._C) < 0);
    LR35902::registers.A -= val - LR35902::registers.F._C;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::SUB8(Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    //alternative LR35902::registers.F.H = ((*(info.registers_8[0]) & 0xF) < (sub & 0xF));
    LR35902::registers.F.H = ((static_cast<int8_t>(LR35902::registers.A & 0xF) - (val & 0xF)) < 0);
    LR35902::registers.F.C = ((static_cast<int16_t>(LR35902::registers.A) - val) < 0);
    LR35902::registers.A -= val;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 1;
}

void OpCodeMapping::Call::SUB8_REG16V(Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    //alternative LR35902::registers.F.H = ((*(info.registers_8[0]) & 0xF) < (sub & 0xF));
    LR35902::registers.F.H = ((static_cast<int8_t>(LR35902::registers.A & 0xF) - (val & 0xF)) < 0);
    LR35902::registers.F.C = ((static_cast<int16_t>(LR35902::registers.A) - val) < 0);
    LR35902::registers.A -= val;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 1;
}

//Reg 0 is always A for ADD
void OpCodeMapping::Call::ADD8(Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    LR35902::registers.F.H = ((((LR35902::registers.A & 0xF) + (val & 0xF)) & 0x10) == 0x10);
    LR35902::registers.F.C = ((static_cast<uint16_t>(*(info.registers_8[0])) + val) > 0xFF);
    LR35902::registers.A += val;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::ADD8_d8(Memory::Map&, OpStructure& info){
    *LR35902::registers.PC+=1;
    const uint8_t val = **LR35902::registers.PC;
    LR35902::registers.F.H = ((((LR35902::registers.A & 0xF) + (val & 0xF)) & 0x10) == 0x10);
    LR35902::registers.F.C = ((static_cast<uint16_t>(*(info.registers_8[0])) + val) > 0xFF);
    LR35902::registers.A += val;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::ADD8_REG16V(Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    LR35902::registers.F.H = ((((LR35902::registers.A & 0xF) + (val & 0xF))  & 0x10) == 0x10);
    LR35902::registers.F.C = ((static_cast<uint16_t>(LR35902::registers.A) + val) > 0xFF);
    LR35902::registers.A += val;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::ADD16(Memory::Map&, OpStructure& info){
    LR35902::registers.F.H = (((static_cast<int32_t>(*(info.registers_16[0]) & 0xFF) + ((*(info.registers_16[1]) & 0xFF))) & 0x100) == 0x100);
    LR35902::registers.F.C = ((static_cast<uint32_t>(*(info.registers_16[0])) + *(info.registers_16[1])) > 0xFFFF);
    *(info.registers_16[0]) += *(info.registers_16[1]);
    LR35902::registers.F.N = 0;
    
}
void OpCodeMapping::Call::INC8(Memory::Map&, OpStructure& info){
    LR35902::registers.F.N = 0;
    // Trick to check half carry (https://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/)
                                //Get first 4 bits, add 1 and mask it with 0x10 (5th bit)
    LR35902::registers.F.H = ((((*(info.registers_8[0]) & 0xF) + 1)     & 0x10) == 0x10);
    (*(info.registers_8[0]))++;
    LR35902::registers.F.Z = ((*(info.registers_8[0])) == 0);
}
void OpCodeMapping::Call::DEC8(Memory::Map&, OpStructure& info){
    LR35902::registers.F.N = 1;
    //This raises the question if the values can be negative here.
    LR35902::registers.F.H = (((static_cast<int8_t>(*(info.registers_8[0]) & 0xF) - 1)) < 0);
    (*(info.registers_8[0]))--;
    LR35902::registers.F.Z = ((*(info.registers_8[0])) == 0);
}

//Different from the 8 bit registers, this version does not set any flags
void OpCodeMapping::Call::INC16(Memory::Map&, OpStructure& info){
    (*(info.registers_16[0]))++;
    LR35902::registers.F.N = 0;
}
void OpCodeMapping::Call::DEC16(Memory::Map&, OpStructure& info){
    (*(info.registers_16[0]))--;
    LR35902::registers.F.N = 1;
}

void OpCodeMapping::Call::AND8(Memory::Map&, OpStructure& info){
    //info.registers_8[0]
    LR35902::registers.A &= (*(info.registers_8[1]));
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
    LR35902::registers.F.H = 1;
    LR35902::registers.F.C = 0;
}
void OpCodeMapping::Call::AND8_REG16V(Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    //info.registers_8[0]
    LR35902::registers.A &= val;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
    LR35902::registers.F.H = 1;
    LR35902::registers.F.C = 0;
}

void OpCodeMapping::Call::XOR8(Memory::Map&, OpStructure& info){
    //info.registers_8[0]
    LR35902::registers.A |= (*(info.registers_8[1]));
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
    LR35902::registers.F.H = 0;
    LR35902::registers.F.C = 0;
}
void OpCodeMapping::Call::XOR8_REG16V(Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    //info.registers_8[0]
    LR35902::registers.A |= val;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
    LR35902::registers.F.H = 0;
    LR35902::registers.F.C = 0;
}

void OpCodeMapping::Call::OR8(Memory::Map&, OpStructure& info){
    //info.registers_8[0]
    LR35902::registers.A |= (*(info.registers_8[1]));
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
    LR35902::registers.F.H = 0;
    LR35902::registers.F.C = 0;
}
void OpCodeMapping::Call::OR8_REG16V(Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    //info.registers_8[0]
    LR35902::registers.A |= val;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.N = 0;
    LR35902::registers.F.H = 0;
    LR35902::registers.F.C = 0;
}

void OpCodeMapping::Call::CP8(Memory::Map&, OpStructure& info){
    //info.registers_8[0]
    const uint8_t val = *(info.registers_8[1]);
    uint8_t result = LR35902::registers.A - val;
    LR35902::registers.F.Z = (result == 0);
    LR35902::registers.F.N = 1;
    LR35902::registers.F.H = ((static_cast<int8_t>(LR35902::registers.A & 0xF) - (val & 0xF)) < 0);
    LR35902::registers.F.C = ((static_cast<int16_t>(LR35902::registers.A) - val) < 0);
}
void OpCodeMapping::Call::CP8_REG16V(Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    uint8_t result = LR35902::registers.A - val;
    LR35902::registers.F.Z = (result == 0);
    LR35902::registers.F.N = 1;
    LR35902::registers.F.H = ((static_cast<int8_t>(LR35902::registers.A & 0xF) - (val & 0xF)) < 0);
    LR35902::registers.F.C = ((static_cast<int16_t>(LR35902::registers.A) - val) < 0);
}
void OpCodeMapping::Call::INC_REG16V(Memory::Map& memMap, OpStructure& info){
    memMap.read(*(info.registers_16[0]))++;
}

void OpCodeMapping::Call::DEC_REG16V(Memory::Map& memMap, OpStructure& info){
    memMap.read(*(info.registers_16[0]))--;
}

void OpCodeMapping::Call::RET(Memory::Map& memMap, OpStructure& info){
    *LR35902::registers.PC = memMap.getMemoryAt(_pop16(memMap));
}

void OpCodeMapping::Call::RETI(Memory::Map& memMap, OpStructure& info){
    EL(memMap, info);
    *LR35902::registers.PC = memMap.getMemoryAt(_pop16(memMap));
}

void OpCodeMapping::Call::RET_NZ(Memory::Map& memMap, OpStructure&){
    if (!LR35902::registers.F.Z) {
        //The address is not 16 bits, so when I push/pop the current PC I will actually store the 
        //memory index
        *LR35902::registers.PC = memMap.getMemoryAt(_pop16(memMap));
        LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::RET_Z(Memory::Map& memMap, OpStructure&){
    if (LR35902::registers.F.Z) {
        //The address is not 16 bits, so when I push/pop the current PC I will actually store the 
        //memory index
        *LR35902::registers.PC = memMap.getMemoryAt(_pop16(memMap));
        LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::RET_NC(Memory::Map& memMap, OpStructure&){
    if (!LR35902::registers.F.C) {
        //The address is not 16 bits, so when I push/pop the current PC I will actually store the 
        //memory index
        *LR35902::registers.PC = memMap.getMemoryAt(_pop16(memMap));
        LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::RET_C(Memory::Map& memMap, OpStructure&){
    if (LR35902::registers.F.C) {
        //The address is not 16 bits, so when I push/pop the current PC I will actually store the 
        //memory index
        *LR35902::registers.PC = memMap.getMemoryAt(_pop16(memMap));
        LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::POP(Memory::Map& memMap, OpStructure& info){
    info.registers_16[0] = reinterpret_cast<uint16_t*>(_pop16(memMap));
}

// In some instances here the 0x1 is redundant, but its left to make the intentions clear.
void OpCodeMapping::Call::RLCA(Memory::Map&, OpStructure& info){
    LR35902::registers.F.C = (LR35902::registers.A >> 7) & 0x1;
    LR35902::registers.A = LR35902::registers.A << 1 | LR35902::registers.F.C & 0x1;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.H = LR35902::registers.F.N = 0;

}

void OpCodeMapping::Call::RLA(Memory::Map& memMap, OpStructure& info){
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = (LR35902::registers.A >> 7) & 0x1;
    LR35902::registers.A = LR35902::registers.A << 1 | LR35902::registers.F._C & 0x1;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::RRCA(Memory::Map& memMap, OpStructure& info){
    LR35902::registers.F.C = LR35902::registers.A & 0x1;
    LR35902::registers.A = LR35902::registers.A >> 1 | LR35902::registers.F.C << 7;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}


void OpCodeMapping::Call::RRA(Memory::Map& memMap, OpStructure& info){
    LR35902::registers.F._C = LR35902::registers.F.C;
    LR35902::registers.F.C = LR35902::registers.A & 0x1;
    LR35902::registers.A = LR35902::registers.A >> 1 | LR35902::registers.F._C << 7;
    LR35902::registers.F.Z = (LR35902::registers.A == 0);
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::CPL(Memory::Map&, OpStructure&){
    LR35902::registers.A = ~LR35902::registers.A;
    LR35902::registers.F.H = LR35902::registers.F.N = 1;
}

void OpCodeMapping::Call::SCF(Memory::Map&, OpStructure&){
    LR35902::registers.F.C = 1;
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::CCF(Memory::Map&, OpStructure&){
    LR35902::registers.F.C = ~LR35902::registers.F.C;
    LR35902::registers.F.H = LR35902::registers.F.N = 0;
}

void OpCodeMapping::Call::DAA(Memory::Map&, OpStructure&){
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

void OpCodeMapping::Call::JR_r8(Memory::Map& memMap, OpStructure& info){
    *LR35902::registers.PC+=*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
}

void OpCodeMapping::Call::JR_NZ_r8(Memory::Map& memMap, OpStructure& info){
    // jump if Z is not set
    if(!LR35902::registers.F.Z ) {
       *LR35902::registers.PC+=*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
       LR35902::extraCycles=1;
    }
}

void OpCodeMapping::Call::JR_Z_r8(Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if(LR35902::registers.F.Z ) {
       *LR35902::registers.PC+=*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
       LR35902::extraCycles=1;
    }
}

void OpCodeMapping::Call::JR_NC_r8(Memory::Map& memMap, OpStructure& info){
    // jump if C is not set
    if(!LR35902::registers.F.C ) {
       *LR35902::registers.PC+=*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
       LR35902::extraCycles=1;
    }
}

void OpCodeMapping::Call::JR_C_r8(Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if(LR35902::registers.F.C ) {
       *LR35902::registers.PC+=*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
       LR35902::extraCycles=1;
    }
}

//Absolute value, so we just assign it by using the value as the value stored as the position in the memory array
void OpCodeMapping::Call::JP_a16(Memory::Map& memMap, OpStructure& info){
    uint16_t pos = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
    pos |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;
    *LR35902::registers.PC=memMap.getMemoryAt(pos);
}

void OpCodeMapping::Call::JP_NZ_a16(Memory::Map& memMap, OpStructure& info) {
    // jump if Z is not set
    if(!LR35902::registers.F.Z ) {
       uint16_t pos = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
       pos |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;
       *LR35902::registers.PC=memMap.getMemoryAt(pos);
       LR35902::extraCycles=3;
    }
}

void OpCodeMapping::Call::JP_Z_a16(Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if(LR35902::registers.F.Z ) {
       uint16_t pos = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
       pos |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;
       *LR35902::registers.PC=memMap.getMemoryAt(pos);
       LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::JP_NC_a16(Memory::Map& memMap, OpStructure& info){
    // jump if C is not set
    if(!LR35902::registers.F.C ) {
       uint16_t pos = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
       pos |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;
       *LR35902::registers.PC=memMap.getMemoryAt(pos);
       LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::JP_C_a16(Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if(LR35902::registers.F.C ) {
       uint16_t pos = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
       pos |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;
       *LR35902::registers.PC=memMap.getMemoryAt(pos);
       LR35902::extraCycles=12;
    }
}

//Here we use the fact that the PC points to some address within the memory,
//So we subtract it from the memory start to get the current index (which is 16 bits)
void OpCodeMapping::Call::CALL_a16(Memory::Map& memMap, OpStructure& info){
    uint16_t target = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
    target |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;

    const ptrdiff_t index = (*LR35902::registers.PC - memMap.getRomStart());
    _push16(memMap, static_cast<uint16_t>(index));
    *LR35902::registers.PC=memMap.getMemoryAt(target);
}

void OpCodeMapping::Call::CALL_NZ_a16(Memory::Map& memMap, OpStructure& info) {
    // jump if Z is not set
    if(!LR35902::registers.F.Z ) {
        uint16_t target = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
        target |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;

        const ptrdiff_t index = (*LR35902::registers.PC - memMap.getRomStart());
        _push16(memMap, static_cast<uint16_t>(index));
        *LR35902::registers.PC=memMap.getMemoryAt(target);
        LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::CALL_Z_a16(Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if(LR35902::registers.F.Z ) {
       uint16_t target = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
        target |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;

        const ptrdiff_t index = (*LR35902::registers.PC - memMap.getRomStart());
        _push16(memMap, static_cast<uint16_t>(index));
        *LR35902::registers.PC=memMap.getMemoryAt(target);
        LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::CALL_NC_a16(Memory::Map& memMap, OpStructure& info){
    // jump if C is not set
    if(!LR35902::registers.F.C ) {
       uint16_t target = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
        target |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;

        const ptrdiff_t index = (*LR35902::registers.PC - memMap.getRomStart());
        _push16(memMap, static_cast<uint16_t>(index));
        *LR35902::registers.PC=memMap.getMemoryAt(target);
        LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::CALL_C_a16(Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if(LR35902::registers.F.C ) {
       uint16_t target = *reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++);
        target |=(*reinterpret_cast<uint8_t*>((*LR35902::registers.PC)++)) << 8;

        const ptrdiff_t index = (*LR35902::registers.PC - memMap.getRomStart());
        _push16(memMap, static_cast<uint16_t>(index));
        *LR35902::registers.PC=memMap.getMemoryAt(target);
        LR35902::extraCycles=12;
    }
}

void OpCodeMapping::Call::EL(Memory::Map&, OpStructure& ){
    LR35902::enableInterruptions = true;
}

void OpCodeMapping::Call::_push8(Memory::Map& memMap, uint8_t val){
    memMap.write(val, --LR35902::registers.SP);
}

void OpCodeMapping::Call::_push16(Memory::Map& memMap, uint16_t val){
    memMap.write(val & 0xFF, --LR35902::registers.SP);
    memMap.write(val >> 8, --LR35902::registers.SP);
}

uint8_t OpCodeMapping::Call::_pop8(Memory::Map& memMap){
    return memMap.read(LR35902::registers.SP++);
}

uint16_t OpCodeMapping::Call::_pop16(Memory::Map& memMap){
    int16_t val = memMap.read(LR35902::registers.SP++) << 8;
    val |= memMap.read(LR35902::registers.SP++);
    return val;
}
//void OpCodeMapping::Call::JR_Z_r8(Memory::Map& memMap, OpStructure& info){}

template<int N>
void bit(){
    int a = 1 << N;
}
/*
For Jump convert the memory address, not the value
reinterpret_cast should work as expected
void OpCodeMapping::Call::LD_REGV_d16(Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::LD_REG16_REG8(Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG16(Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG8_REG8(Memory::Map& memMap, OpStructure& info){}


 

void OpCodeMapping::Call::LD_REG_HLI(Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_REG_HLD(Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_HLI_REG(Memory::Map& memMap, OpStructure& info){}
void OpCodeMapping::Call::LD_HLD_REG(Memory::Map& memMap, OpStructure& info){}





void OpCodeMapping::Call::LD_HL_SP_r8(Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::LD_SP_HL(Memory::Map&, OpStructure&){}








void OpCodeMapping::Call::ADC(Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::SUB(Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::SBC(Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::AND(Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::XOR(Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::OR(Memory::Map&, OpStructure&){}
void OpCodeMapping::Call::CP(Memory::Map&, OpStructure&){}



void OpCodeMapping::Call::STOP(Memory::Map&, OpStructure&){}



*/