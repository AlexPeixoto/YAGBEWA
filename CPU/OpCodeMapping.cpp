#include <OpCodeMapping.h>
#include <OpCodeMapping.h>
#include <LR35902.h>
#include <functional>

using namespace CPU;
using OP = OpCodeMapping::Call;


OpCodeMapping::OpCodeMapping(LR35902& cpu) : instructions{
    //0x[0..F]
    {/* 0x0 */ 4, OP::NOP}, {/* 0x1 */ 12, OP::LD_REG16_d16, &cpu.registers.BC._pair}, {/* 0x2 */ 8, OP::LD_REG16V_REG8, &cpu.registers.BC._pair, &cpu.registers.A}, {/* 0x3 */ 8, OP::INC16, &cpu.registers.BC._pair}, {/* 0x4 */ 4, OP::INC8, &cpu.registers.BC._reg[0]}, {/* 0x5 */ 4, OP::DEC8, &cpu.registers.BC._reg[0]}, {/* 0x6 */ 8, OP::LD_REG8_d8, &cpu.registers.BC._reg[0]}, {/* 0x7 */ 4, OP::RLCA, &cpu.registers.A}, {/* 0x8 */ 20, OP::LD_a16_SP}, {/* 0x9 */ 8, OP::ADD16, &cpu.registers.HL._pair, &cpu.registers.BC._pair}, {/* 0xA */ 8, OP::LD_REG8_REG16V, &cpu.registers.A, &cpu.registers.BC._pair}, {/* 0xB */ 8, OP::DEC16, &cpu.registers.BC._pair}, {/* 0xC */ 4, OP::INC8, &cpu.registers.BC._reg[1]}, {/* 0xD */ 4, OP::DEC8, &cpu.registers.BC._reg[1]}, {/* 0xE */ 8, OP::LD_REG8_d8, &cpu.registers.BC._reg[1]}, {/* 0xF */ 4, OP::RRCA, &cpu.registers.A},
    //1x[0..F]
    {/* 1x0 */ 4, OP::STOP}, {/* 1x1 */ 12, OP::LD_REG16_d16, &cpu.registers.DE._pair}, {/* 1x2 */ 8, OP::LD_REG16V_REG8, &cpu.registers.DE._pair, &cpu.registers.A}, {/* 1x3 */ 8, OP::INC16, &cpu.registers.DE._pair}, {/* 1x4 */ 4, OP::INC8, &cpu.registers.DE._reg[0]}, {/* 1x5 */ 4, OP::DEC8, &cpu.registers.DE._reg[0]}, {/* 1x6 */ 8, OP::LD_REG8_d8, &cpu.registers.DE._reg[0]}, {/* 1x7 */ 4, OP::RLA, &cpu.registers.A}, {/* 1x8 */ 12, OP::JR_r8}, {/* 1x9 */ 8, OP::ADD16, &cpu.registers.HL._pair, &cpu.registers.DE._pair}, {/* 1xA */ 8, OP::LD_REG8_REG16V, &cpu.registers.A, &cpu.registers.DE._pair}, {/* 1xB */ 8, OP::DEC16, &cpu.registers.BC._pair}, {/* 1xC */ 4, OP::INC8, &cpu.registers.DE._reg[1]}, {/* 1xD */ 4, OP::DEC8, &cpu.registers.DE._reg[1]}, {/* 1xE */ 8, OP::LD_REG8_d8, &cpu.registers.DE._reg[1]}, {/* 1xF */ 4, OP::RRA, &cpu.registers.A},
    //2x[0..F]
    {/* 2x0 */ 8, OP::JR_NZ_r8}, {/* 2x1 */ 12, OP::LD_REG16_d16, &cpu.registers.HL._pair}, {/* 2x2 */ 8, OP::LD_HLI_REG, &cpu.registers.A}, {/* 2x3 */ 8, OP::INC16, &cpu.registers.HL._pair}, {/* 2x4 */ 4, OP::INC8, &cpu.registers.HL._reg[0]}, {/* 2x5 */ 4, OP::DEC8, &cpu.registers.HL._reg[0]}, {/* 2x6 */ 8, OP::LD_REG8_d8, &cpu.registers.HL._reg[0]}, {/* 2x7 */ 4, OP::DAA}, {/* 2x8 */ 8, OP::JR_Z_r8}, {/* 2x9 */ 8, OP::ADD16, &cpu.registers.HL._pair, &cpu.registers.HL._pair}, {/* 2xA */ 8, OP::LD_REG_HLI, &cpu.registers.A}, {/* 2xB */ 8, OP::DEC16, &cpu.registers.HL._pair}, {/* 2xC */ 4, OP::INC8, &cpu.registers.HL._reg[1]}, {/* 2xD */ 4, OP::DEC8, &cpu.registers.HL._reg[1]}, {/* 2xE */ 8, OP::LD_REG8_d8, &cpu.registers.HL._reg[1]}, {/* 1xF */ 4, OP::CPL},
    //3x[0..F]
    {/* 3x0 */ 8, OP::JR_NC_r8}, {/* 3x1 */ 12, OP::LD_REG16_d16, &cpu.registers.HL._pair}, {/* 3x2 */ 8, OP::LD_HLD_REG, &cpu.registers.A}, {/* 3x3 */ 8, OP::INC16, &cpu.registers.SP}, {/* 3x4 */ 12, OP::INC_REG16V, &cpu.registers.HL._pair}, {/* 3x5 */ 12, OP::DEC_REG16V, &cpu.registers.HL._pair}, {/* 3x6 */ 12, OP::LD_REG16V_d8, &cpu.registers.HL._pair}, {/* 3x7 */ 4, OP::SCF}, {/* 3x8 */ 8, OP::JR_C_r8}, {/* 3x9 */ 8, OP::ADD16, &cpu.registers.HL._pair, &cpu.registers.SP}, {/* 3xA */ 8, OP::LD_REG_HLD, &cpu.registers.A}, {/* 3xB */ 8, OP::DEC16, &cpu.registers.SP}, {/* 3xC */ 4, OP::INC8, &cpu.registers.A}, {/* 3xD */ 4, OP::DEC8, &cpu.registers.A}, {/* 3xE */ 8, OP::LD_REG8_d8, &cpu.registers.A}, {/* 3xF */ 4, OP::CCF},
    //4x[0..F]
    //Some instructions that are used for consistency (like LD B, B.. LD C, C are being marked as a NOP)
    {/* 4x0 */ 4,  OP::LD_REG8_REG8, &cpu.registers.BC._reg[0], &cpu.registers.BC._reg[0]},  {/* 4x1 */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[0], &cpu.registers.BC._reg[1]}, {/* 4x2 */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[0], &cpu.registers.DE._reg[0]}, {/* 4x3 */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[0], &cpu.registers.DE._reg[1]}, {/* 4x4 */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[0], &cpu.registers.HL._reg[0]}, {/* 4x5 */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[0], &cpu.registers.HL._reg[1]}, {/* 4x6 */ 8, OP::LD_REG8_REG16V, &cpu.registers.BC._reg[0], &cpu.registers.HL._pair}, {/* 4x7 */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[0], &cpu.registers.A}, {/* 4x8 */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[1], &cpu.registers.BC._reg[0]}, {/* 4x9 */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[1], &cpu.registers.BC._reg[1]}, {/* 4xA */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[1], &cpu.registers.DE._reg[0]}, {/* 4xB */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[1], &cpu.registers.DE._reg[1]}, {/* 4xC */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[1], &cpu.registers.HL._reg[0]}, {/* 4xD */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[1], &cpu.registers.HL._reg[1]}, {/* 4xE */ 8, OP::LD_REG8_REG16V, &cpu.registers.BC._reg[1], &cpu.registers.HL._pair}, {/* 4xF */ 4, OP::LD_REG8_REG8, &cpu.registers.BC._reg[1], &cpu.registers.A},
    //5x[0..F]
    {/* 5x0 */ 4,  OP::LD_REG8_REG8, &cpu.registers.DE._reg[0], &cpu.registers.BC._reg[0]},  {/* 5x1 */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[0], &cpu.registers.BC._reg[1]}, {/* 5x2 */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[0], &cpu.registers.DE._reg[0]}, {/* 5x3 */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[0], &cpu.registers.DE._reg[1]}, {/* 5x4 */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[0], &cpu.registers.HL._reg[0]}, {/* 5x5 */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[0], &cpu.registers.HL._reg[1]}, {/* 5x6 */ 8, OP::LD_REG8_REG16V, &cpu.registers.DE._reg[0], &cpu.registers.HL._pair}, {/* 5x7 */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[0], &cpu.registers.A}, {/* 5x8 */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[1], &cpu.registers.BC._reg[0]}, {/* 5x9 */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[1], &cpu.registers.BC._reg[1]}, {/* 5xA */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[1], &cpu.registers.DE._reg[0]}, {/* 5xB */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[1], &cpu.registers.DE._reg[1]}, {/* 5xC */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[1], &cpu.registers.HL._reg[0]}, {/* 5xD */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[1], &cpu.registers.HL._reg[1]}, {/* 5xE */ 8, OP::LD_REG8_REG16V, &cpu.registers.DE._reg[1], &cpu.registers.HL._pair}, {/* 5xF */ 4, OP::LD_REG8_REG8, &cpu.registers.DE._reg[1], &cpu.registers.A},
    //6x[0..F]
    {/* 6x0 */ 4,  OP::LD_REG8_REG8, &cpu.registers.HL._reg[0], &cpu.registers.BC._reg[0]},  {/* 6x1 */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[0], &cpu.registers.BC._reg[1]}, {/* 6x2 */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[0], &cpu.registers.DE._reg[0]}, {/* 6x3 */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[0], &cpu.registers.DE._reg[1]}, {/* 6x4 */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[0], &cpu.registers.HL._reg[0]}, {/* 6x5 */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[0], &cpu.registers.HL._reg[1]}, {/* 6x6 */ 8, OP::LD_REG8_REG16V, &cpu.registers.HL._reg[0], &cpu.registers.HL._pair}, {/* 6x7 */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[0], &cpu.registers.A}, {/* 6x8 */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[1], &cpu.registers.BC._reg[0]}, {/* 6x9 */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[1], &cpu.registers.BC._reg[1]}, {/* 6xA */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[1], &cpu.registers.DE._reg[0]}, {/* 6xB */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[1], &cpu.registers.DE._reg[1]}, {/* 6xC */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[1], &cpu.registers.HL._reg[0]}, {/* 6xD */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[1], &cpu.registers.HL._reg[1]}, {/* 6xE */ 8, OP::LD_REG8_REG16V, &cpu.registers.HL._reg[1], &cpu.registers.HL._pair}, {/* 6xF */ 4, OP::LD_REG8_REG8, &cpu.registers.HL._reg[1], &cpu.registers.A},
    //7x[0..F]
    {/* 7x0 */ 8,  OP::LD_REG16V_REG8, &cpu.registers.HL._pair, &cpu.registers.BC._reg[0]},  {/* 7x1 */ 8, OP::LD_REG16V_REG8, &cpu.registers.HL._pair, &cpu.registers.BC._reg[1]}, {/* 7x2 */ 8, OP::LD_REG16V_REG8, &cpu.registers.HL._pair, &cpu.registers.DE._reg[0]}, {/* 7x3 */ 8, OP::LD_REG16V_REG8, &cpu.registers.HL._pair, &cpu.registers.DE._reg[1]}, {/* 7x4 */ 8, OP::LD_REG16V_REG8, &cpu.registers.HL._pair, &cpu.registers.HL._reg[0]}, {/* 7x5 */ 8, OP::LD_REG16V_REG8, &cpu.registers.HL._pair, &cpu.registers.HL._reg[1]}, {/* 7x6 */ 4, OP::HALT}, {/* 7x7 */ 8, OP::LD_REG16V_REG8, &cpu.registers.HL._pair, &cpu.registers.A}, {/* 7x8 */ 4, OP::LD_REG8_REG8, &cpu.registers.A, &cpu.registers.BC._reg[0]}, {/* 7x9 */ 4, OP::LD_REG8_REG8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* 7xA */ 4, OP::LD_REG8_REG8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* 7xB */ 4, OP::LD_REG8_REG8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* 7xC */ 4, OP::LD_REG8_REG8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* 7xD */ 4, OP::LD_REG8_REG8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* 7xE */ 8, OP::LD_REG8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* 7xF */ 8, OP::LD_REG8_REG8, &cpu.registers.A, &cpu.registers.A},
    //8x[0..F]
    {/* 8x0 */ 4,  OP::ADD8, &cpu.registers.A, &cpu.registers.BC._reg[0]},  {/* 8x1 */ 4, OP::ADD8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* 8x2 */ 4, OP::ADD8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* 8x3 */ 4, OP::ADD8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* 8x4 */ 4, OP::ADD8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* 8x5 */ 4, OP::ADD8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* 8x6 */ 8, OP::ADD8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* 8x7 */ 4, OP::ADD8, &cpu.registers.A, &cpu.registers.A}, {/* 8x8 */ 4, OP::ADC8, &cpu.registers.A, &cpu.registers.BC._reg[0]}, {/* 8x9 */ 4, OP::ADC8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* 8xA */ 4, OP::ADC8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* 8xB */ 4, OP::ADC8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* 8xC */ 4, OP::ADC8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* 8xD */ 4, OP::ADC8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* 8xE */ 8, OP::ADC8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* 8xF */ 4, OP::ADC8, &cpu.registers.A, &cpu.registers.A},
    //9x[0..F]
    {/* 9x0 */ 4,  OP::SUB8, &cpu.registers.A, &cpu.registers.BC._reg[0]},  {/* 9x1 */ 4, OP::SUB8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* 9x2 */ 4, OP::SUB8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* 9x3 */ 4, OP::SUB8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* 9x4 */ 4, OP::SUB8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* 9x5 */ 4, OP::SUB8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* 9x6 */ 8, OP::SUB8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* 9x7 */ 4, OP::SUB8, &cpu.registers.A, &cpu.registers.A}, {/* 9x8 */ 4, OP::SBC8, &cpu.registers.A, &cpu.registers.BC._reg[0]}, {/* 9x9 */ 4, OP::SBC8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* 9xA */ 4, OP::SBC8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* 9xB */ 4, OP::SBC8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* 9xC */ 4, OP::SBC8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* 9xD */ 4, OP::SBC8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* 9xE */ 8, OP::SBC8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* 9xF */ 4, OP::SBC8, &cpu.registers.A, &cpu.registers.A},
    //Ax[0..F]
    {/* Ax0 */ 4,  OP::AND8, &cpu.registers.A, &cpu.registers.BC._reg[0]},  {/* Ax1 */ 4, OP::AND8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* Ax2 */ 4, OP::AND8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* Ax3 */ 4, OP::AND8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* Ax4 */ 4, OP::AND8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* Ax5 */ 4, OP::AND8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* Ax6 */ 8, OP::AND8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* Ax7 */ 4, OP::AND8, &cpu.registers.A, &cpu.registers.A}, {/* Ax8 */ 4, OP::XOR8, &cpu.registers.A, &cpu.registers.BC._reg[0]}, {/* Ax9 */ 4, OP::XOR8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* AxA */ 4, OP::XOR8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* AxB */ 4, OP::XOR8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* AxC */ 4, OP::XOR8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* AxD */ 4, OP::XOR8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* AxE */ 8, OP::XOR8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* AxF */ 4, OP::XOR8, &cpu.registers.A, &cpu.registers.A},
    //Bx[0..F]
    {/* Bx0 */ 4,  OP::OR8, &cpu.registers.A, &cpu.registers.BC._reg[0]},  {/* Bx1 */ 4,  OP::OR8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* Bx2 */ 4,  OP::OR8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* Bx3 */ 4,  OP::OR8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* Bx4 */ 4,  OP::OR8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* Bx5 */ 4,  OP::OR8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* Bx6 */ 8,  OP::OR8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* Bx7 */ 4,  OP::OR8, &cpu.registers.A, &cpu.registers.A}, {/* Bx8 */ 4,  OP::CP8, &cpu.registers.A, &cpu.registers.BC._reg[0]}, {/* Bx9 */ 4,  OP::CP8, &cpu.registers.A, &cpu.registers.BC._reg[1]}, {/* BxA */ 4,  OP::CP8, &cpu.registers.A, &cpu.registers.DE._reg[0]}, {/* BxB */ 4,  OP::CP8, &cpu.registers.A, &cpu.registers.DE._reg[1]}, {/* BxC */ 4,  OP::CP8, &cpu.registers.A, &cpu.registers.HL._reg[0]}, {/* BxD */ 4,  OP::CP8, &cpu.registers.A, &cpu.registers.HL._reg[1]}, {/* BxE */ 8,  OP::CP8_REG16V, &cpu.registers.A, &cpu.registers.HL._pair}, {/* BxF */ 4,  OP::CP8, &cpu.registers.A, &cpu.registers.A},
    //Cx[0..F]
    {/* Cx0 */ 8,  OP::RET_NZ}, {/* Cx1 */ 12,  OP::POP, &cpu.registers.BC._pair}, {/* Cx2 */ 12,  OP::JP_NZ_a16}, {/* Cx3 */ 16,  OP::JP_a16}, {/* Cx4 */ 12,  OP::CALL_NZ_a16}, {/* Cx5 */ 16,  OP::PUSH, &cpu.registers.BC._pair},  {/* Cx6 */ 8,  OP::ADD8_d8, &cpu.registers.A}, {/* Cx7 */ 16, OP::_rst<0x0>}, {/* Cx8 */ 8, OP::RET_Z}, {/* Cx9 */ 16, OP::RET}, {/* CxA */ 12, OP::JP_Z_a16}, {/* CxB */ 4, OP::CB_OPCODE}, {/* CxC */ 12, OP::CALL_Z_a16}, {/* CxD */ 12, OP::CALL_a16}, {/* CxE */ 12, OP::ADC8_d8, &cpu.registers.A}, {/* CxF */ 16, OP::_rst<0x8>},
    //Dx[0..F]
    {/* Dx0 */ 8,  OP::RET_NC}, {/* Dx1 */ 12,  OP::POP, &cpu.registers.DE._pair}, {/* Dx2 */ 12,  OP::JP_NC_a16}, {/* Dx3 */ 1,  OP::ABORT}, {/* Dx4 */ 12,  OP::CALL_NC_a16}, {/* Dx5 */ 16,  OP::PUSH, &cpu.registers.DE._pair},  {/* Dx6 */ 8,  OP::SUB8_d8}, {/* Dx7 */ 16, OP::_rst<0x10>}, {/* Dx8 */ 8, OP::RET_C}, {/* Dx9 */ 16, OP::RETI}, {/* DxA */ 12, OP::JP_C_a16}, {/* DxB */ 1, OP::ABORT}, {/* DxC */ 12, OP::CALL_C_a16}, {/* DxD */ 12, OP::ABORT}, {/* DxE */ 12, OP::SBC8_d8, &cpu.registers.A}, {/* DxF */ 16, OP::_rst<0x18>},
    //Ex[0..F]
    {/* Ex0 */ 12,  OP::LDH_a8_A}, {/* Ex1 */ 12,  OP::POP, &cpu.registers.HL._pair}, {/* Ex2 */ 8,  OP::LD_C_A}, {/* Ex3 */ 1,  OP::ABORT}, {/* Ex4 */ 1,  OP::ABORT}, {/* Ex5 */ 16,  OP::PUSH, &cpu.registers.HL._pair},  {/* Ex6 */ 8,  OP::AND8_d8}, {/* Ex7 */ 16, OP::_rst<0x20>}, {/* Ex8 */ 16, OP::ADD_SP_r8}, {/* Ex9 */ 4, OP::JP_HL}, {/* ExA */ 16, OP::LD_a16_A}, {/* ExB */ 1, OP::ABORT}, {/* ExC */ 1, OP::ABORT}, {/* ExD */ 12, OP::ABORT}, {/* ExE */ 12, OP::XOR8_d8, &cpu.registers.A}, {/* CxF */ 16, OP::_rst<0x28>},
    //Fx[0..F]
    {/* Fx0 */ 12,  OP::LDH_A_a8}, {/* Fx1 */ 12,  OP::POP_AF}, {/* Fx2 */ 8,  OP::LD_A_C}, {/* Fx3 */ 4,  OP::DI}, {/* Fx4 */ 1,  OP::ABORT}, {/* Fx5 */ 16,  OP::PUSH_AF},  {/* Fx6 */ 8,  OP::OR8_d8}, {/* Fx7 */ 16, OP::_rst<0x30>}, {/* Fx8 */ 12, OP::LD_HL_SP_r8}, {/* Fx9 */ 8, OP::LD_SP_HL}, {/* FxA */ 4, OP::LD_A_a16}, {/* FxB */ 1, OP::EI}, {/* FxC */ 1, OP::ABORT}, {/* FxD */ 12, OP::ABORT}, {/* FxE */ 12, OP::CP8_d8, &cpu.registers.A}, {/* FxF */ 16, OP::_rst<0x38>},

},
cbInstructions{
    //0x[0..F]
    {/* 0x0 */ 4, OP::RLC, &cpu.registers.BC._reg[0]}, {/* 0x1 */ 4, OP::RLC, &cpu.registers.BC._reg[1]}, {/* 0x2 */ 4, OP::RLC, &cpu.registers.DE._reg[0]}, {/* 0x3 */ 4, OP::RLC, &cpu.registers.DE._reg[1]}, {/* 0x4 */ 4, OP::RLC, &cpu.registers.HL._reg[0]}, {/* 0x5 */ 4, OP::RLC, &cpu.registers.HL._reg[1]}, {/* 0x6 */ 12, OP::RLC_HL}, {/* 0x7 */ 4, OP::RLC, &cpu.registers.A},{/* 0x8 */ 4, OP::RRC, &cpu.registers.BC._reg[0]}, {/* 0x9 */ 4, OP::RRC, &cpu.registers.BC._reg[1]}, {/* 0xA */ 4, OP::RRC, &cpu.registers.DE._reg[0]}, {/* 0xB */ 4, OP::RRC, &cpu.registers.DE._reg[1]}, {/* 0xC */ 4, OP::RRC, &cpu.registers.HL._reg[0]}, {/* 0xD */ 4, OP::RRC, &cpu.registers.HL._reg[1]}, {/* 0xE */ 12, OP::RRC_HL}, {/* 0xF */ 4, OP::RRC, &cpu.registers.A},
    //1x[0..F]
    {/* 1x0 */ 4, OP::RL, &cpu.registers.BC._reg[0]}, {/* 1x1 */ 4, OP::RL, &cpu.registers.BC._reg[1]}, {/* 1x2 */ 4, OP::RL, &cpu.registers.DE._reg[0]}, {/* 1x3 */ 4, OP::RL, &cpu.registers.DE._reg[1]}, {/* 1x4 */ 4, OP::RL, &cpu.registers.HL._reg[0]}, {/* 1x5 */ 4, OP::RL, &cpu.registers.HL._reg[1]}, {/* 1x6 */ 12, OP::RL_HL}, {/* 1x7 */ 4, OP::RL, &cpu.registers.A},{/* 1x8 */ 4, OP::RR, &cpu.registers.BC._reg[0]}, {/* 1x9 */ 4, OP::RR, &cpu.registers.BC._reg[1]}, {/* 1xA */ 4, OP::RR, &cpu.registers.DE._reg[0]}, {/* 1xB */ 4, OP::RR, &cpu.registers.DE._reg[1]}, {/* 1xC */ 4, OP::RR, &cpu.registers.HL._reg[0]}, {/* 1xD */ 4, OP::RR, &cpu.registers.HL._reg[1]}, {/* 1xE */ 12, OP::RR_HL}, {/* 1xF */ 4, OP::RR, &cpu.registers.A},
    //2x[0..F]
    {/* 2x0 */ 4, OP::SLA, &cpu.registers.BC._reg[0]}, {/* 2x1 */ 4, OP::SLA, &cpu.registers.BC._reg[1]}, {/* 2x2 */ 4, OP::SLA, &cpu.registers.DE._reg[0]}, {/* 2x3 */ 4, OP::SLA, &cpu.registers.DE._reg[1]}, {/* 2x4 */ 4, OP::SLA, &cpu.registers.HL._reg[0]}, {/* 2x5 */ 4, OP::SLA, &cpu.registers.HL._reg[1]}, {/* 2x6 */ 12, OP::SLA_HL}, {/* 2x7 */ 4, OP::SLA, &cpu.registers.A},{/* 2x8 */ 4, OP::SRA, &cpu.registers.BC._reg[0]}, {/* 2x9 */ 4, OP::SRA, &cpu.registers.BC._reg[1]}, {/* 2xA */ 4, OP::SRA, &cpu.registers.DE._reg[0]}, {/* 2xB */ 4, OP::SRA, &cpu.registers.DE._reg[1]}, {/* 2xC */ 4, OP::SRA, &cpu.registers.HL._reg[0]}, {/* 2xD */ 4, OP::SRA, &cpu.registers.HL._reg[1]}, {/* 2xE */ 12, OP::SRA_HL}, {/* 2xF */ 4, OP::SRA, &cpu.registers.A},
    //3x[0..F]
    {/* 3x0 */ 4, OP::SWAP, &cpu.registers.BC._reg[0]}, {/* 3x1 */ 4, OP::SWAP, &cpu.registers.BC._reg[1]}, {/* 3x2 */ 4, OP::SWAP, &cpu.registers.DE._reg[0]}, {/* 3x3 */ 4, OP::SWAP, &cpu.registers.DE._reg[1]}, {/* 3x4 */ 4, OP::SWAP, &cpu.registers.HL._reg[0]}, {/* 3x5 */ 4, OP::SWAP, &cpu.registers.HL._reg[1]}, {/* 3x6 */ 12, OP::SWAP_HL}, {/* 3x7 */ 4, OP::SWAP, &cpu.registers.A},{/* 3x8 */ 4, OP::SRL, &cpu.registers.BC._reg[0]}, {/* 3x9 */ 4, OP::SRL, &cpu.registers.BC._reg[1]}, {/* 3xA */ 4, OP::SRL, &cpu.registers.DE._reg[0]}, {/* 3xB */ 4, OP::SRL, &cpu.registers.DE._reg[1]}, {/* 3xC */ 4, OP::SRL, &cpu.registers.HL._reg[0]}, {/* 3xD */ 4, OP::SRL, &cpu.registers.HL._reg[1]}, {/* 3xE */ 12, OP::SRL_HL}, {/* 3xF */ 4, OP::SRL, &cpu.registers.A},
    //4x[0..F]
    {/* 4x0 */ 4, OP::_bit<0>, &cpu.registers.BC._reg[0]}, {/* 4x1 */ 4, OP::_bit<0>, &cpu.registers.BC._reg[1]}, {/* 4x2 */ 4, OP::_bit<0>, &cpu.registers.DE._reg[0]}, {/* 4x3 */ 4, OP::_bit<0>, &cpu.registers.DE._reg[1]}, {/* 4x4 */ 4, OP::_bit<0>, &cpu.registers.HL._reg[0]}, {/* 4x5 */ 4, OP::_bit<0>, &cpu.registers.HL._reg[1]}, {/* 4x6 */ 12, OP::_bit_hl<0>}, {/* 4x7 */ 4, OP::_bit<0>, &cpu.registers.A},{/* 4x8 */ 4, OP::_bit<1>, &cpu.registers.BC._reg[0]}, {/* 4x9 */ 4, OP::_bit<1>, &cpu.registers.BC._reg[1]}, {/* 4xA */ 4, OP::_bit<1>, &cpu.registers.DE._reg[0]}, {/* 4xB */ 4, OP::_bit<1>, &cpu.registers.DE._reg[1]}, {/* 4xC */ 4, OP::_bit<1>, &cpu.registers.HL._reg[0]}, {/* 4xD */ 4, OP::_bit<1>, &cpu.registers.HL._reg[1]}, {/* 4xE */ 12, OP::_bit_hl<1>}, {/* 4xF */ 4, OP::_bit<1>, &cpu.registers.A},
    //5x[0..F]
    {/* 5x0 */ 4, OP::_bit<2>, &cpu.registers.BC._reg[0]}, {/* 5x1 */ 4, OP::_bit<2>, &cpu.registers.BC._reg[1]}, {/* 5x2 */ 4, OP::_bit<2>, &cpu.registers.DE._reg[0]}, {/* 5x3 */ 4, OP::_bit<2>, &cpu.registers.DE._reg[1]}, {/* 5x4 */ 4, OP::_bit<2>, &cpu.registers.HL._reg[0]}, {/* 5x5 */ 4, OP::_bit<2>, &cpu.registers.HL._reg[1]}, {/* 5x6 */ 12, OP::_bit_hl<2>}, {/* 5x7 */ 4, OP::_bit<2>, &cpu.registers.A},{/* 5x8 */ 4, OP::_bit<3>, &cpu.registers.BC._reg[0]}, {/* 5x9 */ 4, OP::_bit<3>, &cpu.registers.BC._reg[1]}, {/* 5xA */ 4, OP::_bit<3>, &cpu.registers.DE._reg[0]}, {/* 5xB */ 4, OP::_bit<3>, &cpu.registers.DE._reg[1]}, {/* 5xC */ 4, OP::_bit<3>, &cpu.registers.HL._reg[0]}, {/* 5xD */ 4, OP::_bit<3>, &cpu.registers.HL._reg[1]}, {/* 5xE */ 12, OP::_bit_hl<3>}, {/* 5xF */ 4, OP::_bit<3>, &cpu.registers.A},
    //6x[0..F]
    {/* 6x0 */ 4, OP::_bit<4>, &cpu.registers.BC._reg[0]}, {/* 6x1 */ 4, OP::_bit<4>, &cpu.registers.BC._reg[1]}, {/* 6x2 */ 4, OP::_bit<4>, &cpu.registers.DE._reg[0]}, {/* 6x3 */ 4, OP::_bit<4>, &cpu.registers.DE._reg[1]}, {/* 6x4 */ 4, OP::_bit<4>, &cpu.registers.HL._reg[0]}, {/* 6x5 */ 4, OP::_bit<4>, &cpu.registers.HL._reg[1]}, {/* 6x6 */ 12, OP::_bit_hl<4>}, {/* 6x7 */ 4, OP::_bit<4>, &cpu.registers.A},{/* 6x8 */ 4, OP::_bit<5>, &cpu.registers.BC._reg[0]}, {/* 6x9 */ 4, OP::_bit<5>, &cpu.registers.BC._reg[1]}, {/* 6xA */ 4, OP::_bit<5>, &cpu.registers.DE._reg[0]}, {/* 6xB */ 4, OP::_bit<5>, &cpu.registers.DE._reg[1]}, {/* 6xC */ 4, OP::_bit<5>, &cpu.registers.HL._reg[0]}, {/* 6xD */ 4, OP::_bit<5>, &cpu.registers.HL._reg[1]}, {/* §E */ 12, OP::_bit_hl<5>}, {/* 6xF */ 4, OP::_bit<5>, &cpu.registers.A},
    //7x[0..F]
    {/* 7x0 */ 4, OP::_bit<6>, &cpu.registers.BC._reg[0]}, {/* 7x1 */ 4, OP::_bit<6>, &cpu.registers.BC._reg[1]}, {/* 7x2 */ 4, OP::_bit<6>, &cpu.registers.DE._reg[0]}, {/* 7x3 */ 4, OP::_bit<6>, &cpu.registers.DE._reg[1]}, {/* 7x4 */ 4, OP::_bit<6>, &cpu.registers.HL._reg[0]}, {/* 7x5 */ 4, OP::_bit<6>, &cpu.registers.HL._reg[1]}, {/* 7x6 */ 12, OP::_bit_hl<6>}, {/* 7x7 */ 4, OP::_bit<6>, &cpu.registers.A},{/* 7x8 */ 4, OP::_bit<6>, &cpu.registers.BC._reg[0]}, {/* 7x9 */ 4, OP::_bit<6>, &cpu.registers.BC._reg[1]}, {/* 7xA */ 4, OP::_bit<6>, &cpu.registers.DE._reg[0]}, {/* 7xB */ 4, OP::_bit<6>, &cpu.registers.DE._reg[1]}, {/* 7xC */ 4, OP::_bit<6>, &cpu.registers.HL._reg[0]}, {/* 7xD */ 4, OP::_bit<6>, &cpu.registers.HL._reg[1]}, {/* §E */ 12, OP::_bit_hl<6>}, {/* 7xF */ 4, OP::_bit<6>, &cpu.registers.A},
    //8x[0..F]
    {/* 8x0 */ 4, OP::_res<0>, &cpu.registers.BC._reg[0]}, {/* 8x1 */ 4, OP::_res<0>, &cpu.registers.BC._reg[1]}, {/* 8x2 */ 4, OP::_res<0>, &cpu.registers.DE._reg[0]}, {/* 8x3 */ 4, OP::_res<0>, &cpu.registers.DE._reg[1]}, {/* 8x4 */ 4, OP::_res<0>, &cpu.registers.HL._reg[0]}, {/* 8x5 */ 4, OP::_res<0>, &cpu.registers.HL._reg[1]}, {/* 8x6 */ 12, OP::_res_hl<0>}, {/* 8x7 */ 4, OP::_res<0>, &cpu.registers.A},{/* 8x8 */ 4, OP::_res<1>, &cpu.registers.BC._reg[0]}, {/* 8x9 */ 4, OP::_res<1>, &cpu.registers.BC._reg[1]}, {/* 8xA */ 4, OP::_res<1>, &cpu.registers.DE._reg[0]}, {/* 8xB */ 4, OP::_res<1>, &cpu.registers.DE._reg[1]}, {/* 8xC */ 4, OP::_res<1>, &cpu.registers.HL._reg[0]}, {/* 8xD */ 4, OP::_res<1>, &cpu.registers.HL._reg[1]}, {/* 8xE */ 12, OP::_res_hl<1>}, {/* 8xF */ 4, OP::_res<1>, &cpu.registers.A},
    //9x[0..F]
    {/* 9x0 */ 4, OP::_res<2>, &cpu.registers.BC._reg[0]}, {/* 9x1 */ 4, OP::_res<2>, &cpu.registers.BC._reg[1]}, {/* 9x2 */ 4, OP::_res<2>, &cpu.registers.DE._reg[0]}, {/* 9x3 */ 4, OP::_res<2>, &cpu.registers.DE._reg[1]}, {/* 9x4 */ 4, OP::_res<2>, &cpu.registers.HL._reg[0]}, {/* 9x5 */ 4, OP::_res<2>, &cpu.registers.HL._reg[1]}, {/* 9x6 */ 12, OP::_res_hl<2>}, {/* 9x7 */ 4, OP::_res<2>, &cpu.registers.A},{/* 9x8 */ 4, OP::_res<3>, &cpu.registers.BC._reg[0]}, {/* 9x9 */ 4, OP::_res<3>, &cpu.registers.BC._reg[1]}, {/* 9xA */ 4, OP::_res<3>, &cpu.registers.DE._reg[0]}, {/* 9xB */ 4, OP::_res<3>, &cpu.registers.DE._reg[1]}, {/* 9xC */ 4, OP::_res<3>, &cpu.registers.HL._reg[0]}, {/* 9xD */ 4, OP::_res<3>, &cpu.registers.HL._reg[1]}, {/* 9xE */ 12, OP::_res_hl<3>}, {/* 9xF */ 4, OP::_res<3>, &cpu.registers.A},
    //Ax[0..F]
    {/* Ax0 */ 4, OP::_res<4>, &cpu.registers.BC._reg[0]}, {/* Ax1 */ 4, OP::_res<4>, &cpu.registers.BC._reg[1]}, {/* Ax2 */ 4, OP::_res<4>, &cpu.registers.DE._reg[0]}, {/* Ax3 */ 4, OP::_res<4>, &cpu.registers.DE._reg[1]}, {/* Ax4 */ 4, OP::_res<4>, &cpu.registers.HL._reg[0]}, {/* Ax5 */ 4, OP::_res<4>, &cpu.registers.HL._reg[1]}, {/* Ax6 */ 12, OP::_res_hl<4>}, {/* Ax7 */ 4, OP::_res<4>, &cpu.registers.A},{/* Ax8 */ 4, OP::_res<5>, &cpu.registers.BC._reg[0]}, {/* Ax9 */ 4, OP::_res<5>, &cpu.registers.BC._reg[1]}, {/* AxA */ 4, OP::_res<5>, &cpu.registers.DE._reg[0]}, {/* AxB */ 4, OP::_res<5>, &cpu.registers.DE._reg[1]}, {/* AxC */ 4, OP::_res<5>, &cpu.registers.HL._reg[0]}, {/* AxD */ 4, OP::_res<5>, &cpu.registers.HL._reg[1]}, {/* §E */ 12, OP::_res_hl<5>}, {/* AxF */ 4, OP::_res<5>, &cpu.registers.A},
    //Bx[0..F]
    {/* Bx0 */ 4, OP::_res<6>, &cpu.registers.BC._reg[0]}, {/* Bx1 */ 4, OP::_res<6>, &cpu.registers.BC._reg[1]}, {/* Bx2 */ 4, OP::_res<6>, &cpu.registers.DE._reg[0]}, {/* Bx3 */ 4, OP::_res<6>, &cpu.registers.DE._reg[1]}, {/* Bx4 */ 4, OP::_res<6>, &cpu.registers.HL._reg[0]}, {/* Bx5 */ 4, OP::_res<6>, &cpu.registers.HL._reg[1]}, {/* Bx6 */ 12, OP::_res_hl<6>}, {/* Bx7 */ 4, OP::_res<6>, &cpu.registers.A},{/* Bx8 */ 4, OP::_res<6>, &cpu.registers.BC._reg[0]}, {/* Bx9 */ 4, OP::_res<6>, &cpu.registers.BC._reg[1]}, {/* BxA */ 4, OP::_res<6>, &cpu.registers.DE._reg[0]}, {/* BxB */ 4, OP::_res<6>, &cpu.registers.DE._reg[1]}, {/* BxC */ 4, OP::_res<6>, &cpu.registers.HL._reg[0]}, {/* BxD */ 4, OP::_res<6>, &cpu.registers.HL._reg[1]}, {/* §E */ 12, OP::_res_hl<6>}, {/* BxF */ 4, OP::_res<6>, &cpu.registers.A},
    //Cx[0..F]
    {/* Cx0 */ 4, OP::_set<0>, &cpu.registers.BC._reg[0]}, {/* Cx1 */ 4, OP::_set<0>, &cpu.registers.BC._reg[1]}, {/* Cx2 */ 4, OP::_set<0>, &cpu.registers.DE._reg[0]}, {/* Cx3 */ 4, OP::_set<0>, &cpu.registers.DE._reg[1]}, {/* Cx4 */ 4, OP::_set<0>, &cpu.registers.HL._reg[0]}, {/* Cx5 */ 4, OP::_set<0>, &cpu.registers.HL._reg[1]}, {/* Cx6 */ 12, OP::_set_hl<0>}, {/* Cx7 */ 4, OP::_set<0>, &cpu.registers.A},{/* Cx8 */ 4, OP::_set<1>, &cpu.registers.BC._reg[0]}, {/* Cx9 */ 4, OP::_set<1>, &cpu.registers.BC._reg[1]}, {/* CxA */ 4, OP::_set<1>, &cpu.registers.DE._reg[0]}, {/* CxB */ 4, OP::_set<1>, &cpu.registers.DE._reg[1]}, {/* CxC */ 4, OP::_set<1>, &cpu.registers.HL._reg[0]}, {/* CxD */ 4, OP::_set<1>, &cpu.registers.HL._reg[1]}, {/* CxE */ 12, OP::_set_hl<1>}, {/* CxF */ 4, OP::_set<1>, &cpu.registers.A},
    //Dx[0..F]
    {/* Dx0 */ 4, OP::_set<2>, &cpu.registers.BC._reg[0]}, {/* Dx1 */ 4, OP::_set<2>, &cpu.registers.BC._reg[1]}, {/* Dx2 */ 4, OP::_set<2>, &cpu.registers.DE._reg[0]}, {/* Dx3 */ 4, OP::_set<2>, &cpu.registers.DE._reg[1]}, {/* Dx4 */ 4, OP::_set<2>, &cpu.registers.HL._reg[0]}, {/* Dx5 */ 4, OP::_set<2>, &cpu.registers.HL._reg[1]}, {/* Dx6 */ 12, OP::_set_hl<2>}, {/* Dx7 */ 4, OP::_set<2>, &cpu.registers.A},{/* Dx8 */ 4, OP::_set<3>, &cpu.registers.BC._reg[0]}, {/* Dx9 */ 4, OP::_set<3>, &cpu.registers.BC._reg[1]}, {/* DxA */ 4, OP::_set<3>, &cpu.registers.DE._reg[0]}, {/* DxB */ 4, OP::_set<3>, &cpu.registers.DE._reg[1]}, {/* DxC */ 4, OP::_set<3>, &cpu.registers.HL._reg[0]}, {/* DxD */ 4, OP::_set<3>, &cpu.registers.HL._reg[1]}, {/* DxE */ 12, OP::_set_hl<3>}, {/* DxF */ 4, OP::_set<3>, &cpu.registers.A},
    //Ex[0..F]
    {/* Ex0 */ 4, OP::_set<4>, &cpu.registers.BC._reg[0]}, {/* Ex1 */ 4, OP::_set<4>, &cpu.registers.BC._reg[1]}, {/* Ex2 */ 4, OP::_set<4>, &cpu.registers.DE._reg[0]}, {/* Ex3 */ 4, OP::_set<4>, &cpu.registers.DE._reg[1]}, {/* Ex4 */ 4, OP::_set<4>, &cpu.registers.HL._reg[0]}, {/* Ex5 */ 4, OP::_set<4>, &cpu.registers.HL._reg[1]}, {/* Ex6 */ 12, OP::_set_hl<4>}, {/* Ex7 */ 4, OP::_set<4>, &cpu.registers.A},{/* Ex8 */ 4, OP::_set<5>, &cpu.registers.BC._reg[0]}, {/* Ex9 */ 4, OP::_set<5>, &cpu.registers.BC._reg[1]}, {/* ExA */ 4, OP::_set<5>, &cpu.registers.DE._reg[0]}, {/* ExB */ 4, OP::_set<5>, &cpu.registers.DE._reg[1]}, {/* ExC */ 4, OP::_set<5>, &cpu.registers.HL._reg[0]}, {/* ExD */ 4, OP::_set<5>, &cpu.registers.HL._reg[1]}, {/* §E */ 12, OP::_set_hl<5>}, {/* ExF */ 4, OP::_set<5>, &cpu.registers.A},
    //Fx[0..F]
    {/* Fx0 */ 4, OP::_set<6>, &cpu.registers.BC._reg[0]}, {/* Fx1 */ 4, OP::_set<6>, &cpu.registers.BC._reg[1]}, {/* Fx2 */ 4, OP::_set<6>, &cpu.registers.DE._reg[0]}, {/* Fx3 */ 4, OP::_set<6>, &cpu.registers.DE._reg[1]}, {/* Fx4 */ 4, OP::_set<6>, &cpu.registers.HL._reg[0]}, {/* Fx5 */ 4, OP::_set<6>, &cpu.registers.HL._reg[1]}, {/* Fx6 */ 12, OP::_set_hl<6>}, {/* Fx7 */ 4, OP::_set<6>, &cpu.registers.A},{/* Fx8 */ 4, OP::_set<6>, &cpu.registers.BC._reg[0]}, {/* Fx9 */ 4, OP::_set<6>, &cpu.registers.BC._reg[1]}, {/* FxA */ 4, OP::_set<6>, &cpu.registers.DE._reg[0]}, {/* FxB */ 4, OP::_set<6>, &cpu.registers.DE._reg[1]}, {/* FxC */ 4, OP::_set<6>, &cpu.registers.HL._reg[0]}, {/* FxD */ 4, OP::_set<6>, &cpu.registers.HL._reg[1]}, {/* §E */ 12, OP::_set_hl<6>}, {/* FxF */ 4, OP::_set<6>, &cpu.registers.A}
}
{
    

}

uint16_t OpCodeMapping::executeNext(LR35902& cpu, Memory::Map& memMap){
    cpu.extraCycles = 0;
    //std::cout << std::hex << static_cast<uint32_t>(*(cpu.registers.PC)) << std::endl;
    auto &op = instructions.at(*cpu.registers.PC);
    //Go back one instruction, this should not cause problems as no instruction
    //Reads again the same byte.
    //Its important to do here due to 2 byte instructions.
    //The reason for that is that $3E $14 should be executed as $3E $3E $14
    if(cpu.haltType == HaltType::Revert){
        cpu.registers.PC--;
        cpu.haltType = HaltType::None;
    }
    op.call(cpu, memMap, op);
    return op.cycleCount + cpu.extraCycles;
}

void OpCodeMapping::Call::ABORT(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    abort();
}

void OpCodeMapping::Call::CB_OPCODE(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    //Also known as STOP 0 instruction 10 00.
    cpu.registers.PC+=1;
    OpStructure& cbInfo = cpu.mapping.cbInstructions.at(*cpu.registers.PC);
    cbInfo.call(cpu, memMap, cbInfo);
}

void OpCodeMapping::Call::HALT(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    if(cpu.imeType == IMEType::Enabled){
        if((memMap[0xFFFF] & memMap[0xFF0F] & 0x1F) != 0){
            cpu.haltType = HaltType::Revert;
        }
        else if((memMap[0xFFFF] & memMap[0xFF0F] & 0x1F) != 0){
            cpu.haltType = HaltType::NoInterruption;
        }
    }

    cpu.haltType = HaltType::Normal;
}

void OpCodeMapping::Call::STOP(LR35902& cpu, Memory::Map&, OpStructure&){
    //Also known as STOP 0 instruction 10 00.
    cpu.registers.PC+=1;
    cpu.stop = true;
}

void OpCodeMapping::Call::LD_REG8_REG8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = *(info.registers_8[1]);
}

void OpCodeMapping::Call::LD_REG8_d8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    *(info.registers_8[0]) = *cpu.registers.PC;
}

void OpCodeMapping::Call::LD_REG16_d16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    *(info.registers_16[0]) = *cpu.registers.PC;
    cpu.registers.PC+=1;
    *(info.registers_16[0]) |= *cpu.registers.PC << 8;
}

// Store value in register REG8 into byte pointed to by register r16.
void OpCodeMapping::Call::LD_REG16V_REG8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    memMap.write(*(info.registers_8[0]), *(info.registers_16[0]));
}

// Load value in register REG8 from byte pointed to by register r16.
void OpCodeMapping::Call::LD_REG8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(*(info.registers_16[0]));
}

void OpCodeMapping::Call::LD_REG16V_d8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    memMap.write(
        *cpu.registers.PC, //Write this value
        *(info.registers_16[0]) //At this location of the memory
    );
}

void OpCodeMapping::Call::LD_a16_SP(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    cpu.registers.PC+=1;
    uint16_t addr = *reinterpret_cast<uint8_t*>(++cpu.registers.PC);
    addr |=(*reinterpret_cast<uint8_t*>(++cpu.registers.PC)) << 8;
    //Store SP & $FF at address n16 and SP >> 8 at address n16 + 1.
    memMap.write(cpu.registers.SP & 0XFF, addr);
    memMap.write(cpu.registers.SP >> 8, addr+1);
}

void OpCodeMapping::Call::LD_HLI_REG(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    memMap.write(*info.registers_8[0], cpu.registers.HL._pair);
    cpu.registers.HL._pair++; 
}

void OpCodeMapping::Call::LD_HLD_REG(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    memMap.write(*info.registers_8[0], cpu.registers.HL._pair);
    cpu.registers.HL._pair--; 
}

void OpCodeMapping::Call::LD_REG_HLI(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(cpu.registers.HL._pair);
    cpu.registers.HL._pair++; 
}

void OpCodeMapping::Call::LD_REG_HLD(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = memMap.read(cpu.registers.HL._pair);
    cpu.registers.HL._pair--; 
}

void OpCodeMapping::Call::LDH_a8_A(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    memMap.write(cpu.registers.A, 0xFF00 + *cpu.registers.PC);
}

void OpCodeMapping::Call::LDH_A_a8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    cpu.registers.A = memMap.read(0xFF00 + *cpu.registers.PC);
}

void OpCodeMapping::Call::LD_a16_A(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint16_t pos = *reinterpret_cast<uint8_t*>(++cpu.registers.PC);
    pos |=(*reinterpret_cast<uint8_t*>(++cpu.registers.PC)) << 8;
    memMap.write(cpu.registers.A, pos);
}

void OpCodeMapping::Call::LD_A_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint16_t pos = *reinterpret_cast<uint8_t*>(++cpu.registers.PC);
    pos |=(*reinterpret_cast<uint8_t*>(++cpu.registers.PC)) << 8;
    cpu.registers.A = memMap.read(pos);
}

void OpCodeMapping::Call::LD_C_A(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    memMap.write(cpu.registers.A, 0xFF00 + cpu.registers.BC._reg[1]);
}

void OpCodeMapping::Call::LD_A_C(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.A = memMap.read(0xFF00 + cpu.registers.BC._reg[1]);
}

void OpCodeMapping::Call::LD_HL_SP_r8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    const int8_t val = *reinterpret_cast<int8_t*>(cpu.registers.PC);
    cpu.registers.F.Z = 0;
    cpu.registers.F.N = 0;
    cpu.registers.F.C = ((static_cast<uint32_t>(cpu.registers.SP) + val) > 0xFF);
    //Overflow from 4th (or 3rd starting from 0) bit (1111) = > 16
    cpu.registers.F.H = ((static_cast<uint16_t>(cpu.registers.SP) + val) > 0xF);

    cpu.registers.HL._pair = cpu.registers.SP + val;
}

void OpCodeMapping::Call::LD_SP_HL(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.SP = cpu.registers.HL._pair;
}

void OpCodeMapping::Call::NOP(LR35902& cpu, Memory::Map& memMap, OpStructure& info){}

void OpCodeMapping::Call::_adc(LR35902& cpu, uint8_t val) {
    cpu.registers.F._C = cpu.registers.F.C;
    cpu.registers.F.C = ((static_cast<uint32_t>(cpu.registers.A) + val + cpu.registers.F._C) > 0xFF);
    //Overflow from 4th (or 3rd starting from 0) bit (1111) = > 16
    cpu.registers.F.H = ((static_cast<uint16_t>(cpu.registers.A) + val + cpu.registers.F._C) > 0xF);
    cpu.registers.A += val + cpu.registers.F._C;
    cpu.registers.F.Z = (cpu.registers.A == 0);
    cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::ADC8(LR35902& cpu, Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    _adc(cpu, val);
}

void OpCodeMapping::Call::ADC8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    _adc(cpu, val);
}

void OpCodeMapping::Call::ADC8_d8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    const uint8_t val = *cpu.registers.PC;
    _adc(cpu, val);
}

void OpCodeMapping::Call::_sbc(LR35902& cpu, uint8_t val) {
    cpu.registers.F._C = cpu.registers.F.C;
    cpu.registers.F.H = ((static_cast<int8_t>(cpu.registers.A & 0xF) - (val & 0xF) - cpu.registers.F._C) < 0);
    cpu.registers.F.C = ((static_cast<int16_t>(cpu.registers.A) - val - cpu.registers.F._C) < 0);
    cpu.registers.A -= val - cpu.registers.F._C;
    cpu.registers.F.Z = (cpu.registers.A == 0);
    cpu.registers.F.N = 0;
}
void OpCodeMapping::Call::SBC8(LR35902& cpu, Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    _sbc(cpu, val);
}

void OpCodeMapping::Call::SBC8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    _sbc(cpu, val);
}

void OpCodeMapping::Call::SBC8_d8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    const uint8_t val = *cpu.registers.PC;
    _sbc(cpu, val);
}

//Reg 0 is always A for ADD
void OpCodeMapping::Call::_add(LR35902& cpu,  uint8_t val){
    cpu.registers.F.H = ((((cpu.registers.A & 0xF) + (val & 0xF)) & 0x10) == 0x10);
    cpu.registers.F.C = ((static_cast<uint16_t>(cpu.registers.A) + val) > 0xFF);
    cpu.registers.A += val;
    cpu.registers.F.Z = (cpu.registers.A == 0);
    cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::ADD_SP_r8(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.PC+=1;
    const int8_t val = *reinterpret_cast<int8_t*>(cpu.registers.PC);
    cpu.registers.F.H = ((((cpu.registers.SP & 0xF) + (val & 0xF)) & 0x10) == 0x10);
    cpu.registers.F.C = ((static_cast<uint16_t>(cpu.registers.SP) + val) > 0xFF);
    cpu.registers.SP += val;
    cpu.registers.F.Z = 0;
    cpu.registers.F.N = 0;
}


void OpCodeMapping::Call::ADD8(LR35902& cpu, Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    _add(cpu, val);
}

void OpCodeMapping::Call::ADD8_d8(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.PC+=1;
    const uint8_t val = *cpu.registers.PC;
    _add(cpu, val);
}

void OpCodeMapping::Call::ADD8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    _add(cpu, val);
}

void OpCodeMapping::Call::ADD16(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.H = (((static_cast<int32_t>(*(info.registers_16[0]) & 0xFF) + ((*(info.registers_16[1]) & 0xFF))) & 0x100) == 0x100);
    cpu.registers.F.C = ((static_cast<uint32_t>(*(info.registers_16[0])) + *(info.registers_16[1])) > 0xFFFF);
    *(info.registers_16[0]) += *(info.registers_16[1]);
    cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::_sub(LR35902& cpu,uint8_t val){
    //alternative cpu.registers.F.H = ((*(info.registers_8[0]) & 0xF) < (sub & 0xF));
    cpu.registers.F.H = ((static_cast<int8_t>(cpu.registers.A & 0xF) - (val & 0xF)) < 0);
    cpu.registers.F.C = ((static_cast<int16_t>(cpu.registers.A) - val) < 0);
    cpu.registers.A -= val;
    cpu.registers.F.Z = (cpu.registers.A == 0);
    cpu.registers.F.N = 1;
}

void OpCodeMapping::Call::SUB8(LR35902& cpu, Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    _sub(cpu, val);
}

void OpCodeMapping::Call::SUB8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=1;
    const uint8_t val = *cpu.registers.PC;
    _sub(cpu, val);
}

void OpCodeMapping::Call::SUB8_d8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    _sub(cpu, val);
}

void OpCodeMapping::Call::INC8(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.N = 0;
    // Trick to check half carry (https://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/)
                                //Get first 4 bits, add 1 and mask it with 0x10 (5th bit)
    cpu.registers.F.H = ((((*(info.registers_8[0]) & 0xF) + 1)     & 0x10) == 0x10);
    (*(info.registers_8[0]))++;
    cpu.registers.F.Z = ((*(info.registers_8[0])) == 0);
}
void OpCodeMapping::Call::DEC8(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.N = 1;
    //This raises the question if the values can be negative here.
    cpu.registers.F.H = (((static_cast<int8_t>(*(info.registers_8[0]) & 0xF) - 1)) < 0);
    (*(info.registers_8[0]))--;
    cpu.registers.F.Z = ((*(info.registers_8[0])) == 0);
}

//Different from the 8 bit registers, this version does not set any flags
void OpCodeMapping::Call::INC16(LR35902& cpu, Memory::Map&, OpStructure& info){
    (*(info.registers_16[0]))++;
    cpu.registers.F.N = 0;
}
void OpCodeMapping::Call::DEC16(LR35902& cpu, Memory::Map&, OpStructure& info){
    (*(info.registers_16[0]))--;
    cpu.registers.F.N = 1;
}

void OpCodeMapping::Call::_and(LR35902& cpu,uint8_t val){
    cpu.registers.A &= val;
    cpu.registers.F.Z = (cpu.registers.A == 0);
    cpu.registers.F.N = 0;
    cpu.registers.F.H = 1;
    cpu.registers.F.C = 0;
}

void OpCodeMapping::Call::AND8(LR35902& cpu, Memory::Map&, OpStructure& info){
    const uint8_t val = *(info.registers_8[1]);
    _and(cpu, val);
}
void OpCodeMapping::Call::AND8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    const uint8_t val = memMap.read(*(info.registers_16[0]));
    _and(cpu, val);
}

void OpCodeMapping::Call::AND8_d8(LR35902& cpu, Memory::Map&, OpStructure&){
    cpu.registers.PC+=1;
    const uint8_t val = *cpu.registers.PC;
    _and(cpu, val);
}
void OpCodeMapping::Call::_xor(LR35902& cpu,uint8_t val){
    cpu.registers.A |= val;
    cpu.registers.F.Z = (cpu.registers.A == 0);
    cpu.registers.F.N = 0;
    cpu.registers.F.H = 0;
    cpu.registers.F.C = 0;
}

void OpCodeMapping::Call::XOR8(LR35902& cpu, Memory::Map&, OpStructure& info){
    //info.registers_8[0]
    const uint8_t val = *(info.registers_8[1]);
    _xor(cpu, val);
}
void OpCodeMapping::Call::XOR8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    //info.registers_8[0]
    _xor(cpu, val);
}

void OpCodeMapping::Call::XOR8_d8(LR35902& cpu, Memory::Map&, OpStructure&){
    cpu.registers.PC+=1;
    const uint8_t val = *cpu.registers.PC;
    _xor(cpu, val);
}

void OpCodeMapping::Call::_or(LR35902& cpu,uint8_t val){
    cpu.registers.A = (cpu.registers.A ||  val);
    cpu.registers.F.Z = (cpu.registers.A == 0);
    cpu.registers.F.N = 0;
    cpu.registers.F.H = 0;
    cpu.registers.F.C = 0;
}

void OpCodeMapping::Call::OR8(LR35902& cpu, Memory::Map&, OpStructure& info){
    //info.registers_8[0]
    const uint8_t val = *(info.registers_8[1]);
    _or(cpu, val);
}
void OpCodeMapping::Call::OR8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    _or(cpu, val);
}

void OpCodeMapping::Call::OR8_d8(LR35902& cpu, Memory::Map&, OpStructure&){
    cpu.registers.PC+=1;
    const uint8_t val = *cpu.registers.PC;
    _or(cpu, val);
}

void OpCodeMapping::Call::_cp(LR35902& cpu, uint8_t val){
    uint8_t result = cpu.registers.A - val;
    cpu.registers.F.Z = (result == 0);
    cpu.registers.F.N = 1;
    cpu.registers.F.H = ((static_cast<int8_t>(cpu.registers.A & 0xF) - (val & 0xF)) < 0);
    cpu.registers.F.C = ((static_cast<int16_t>(cpu.registers.A) - val) < 0);
}
void OpCodeMapping::Call::CP8(LR35902& cpu, Memory::Map&, OpStructure& info){
    //info.registers_8[0]
    const uint8_t val = *(info.registers_8[1]);
    _cp(cpu, val);
    
}
void OpCodeMapping::Call::CP8_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(*(info.registers_16[0]));
    _cp(cpu, val);
}

void OpCodeMapping::Call::CP8_d8(LR35902& cpu, Memory::Map&, OpStructure&){
    cpu.registers.PC+=1;
    const uint8_t val = *cpu.registers.PC;
    _cp(cpu, val);
}

void OpCodeMapping::Call::INC_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    memMap.read(*(info.registers_16[0]))++;
}

void OpCodeMapping::Call::DEC_REG16V(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    memMap.read(*(info.registers_16[0]))--;
}

void OpCodeMapping::Call::RET(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC = memMap.getMemoryAt(_pop16(cpu, memMap));
}

void OpCodeMapping::Call::RETI(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    EI(cpu, memMap, info);
    cpu.registers.PC = memMap.getMemoryAt(_pop16(cpu, memMap));
}

void OpCodeMapping::Call::RET_NZ(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    if (!cpu.registers.F.Z) {
        //The address is not 16 bits, so when I push/pop the current PC I will actually store the 
        //memory index
        cpu.registers.PC = memMap.getMemoryAt(_pop16(cpu, memMap));
        cpu.extraCycles=12;
    }
}

void OpCodeMapping::Call::RET_Z(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    if (cpu.registers.F.Z) {
        //The address is not 16 bits, so when I push/pop the current PC I will actually store the 
        //memory index
        cpu.registers.PC = memMap.getMemoryAt(_pop16(cpu, memMap));
        cpu.extraCycles=12;
    }
}

void OpCodeMapping::Call::RET_NC(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    if (!cpu.registers.F.C) {
        //The address is not 16 bits, so when I push/pop the current PC I will actually store the 
        //memory index
        cpu.registers.PC = memMap.getMemoryAt(_pop16(cpu, memMap));
        cpu.extraCycles=12;
    }
}

void OpCodeMapping::Call::RET_C(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    if (cpu.registers.F.C) {
        //The address is not 16 bits, so when I push/pop the current PC I will actually store the 
        //memory index
        cpu.registers.PC = memMap.getMemoryAt(_pop16(cpu, memMap));
        cpu.extraCycles=12;
    }
}

void OpCodeMapping::Call::PUSH(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    _push16(cpu, memMap, *(info.registers_16[0]));
}

void OpCodeMapping::Call::PUSH_AF(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t f = 0;
    //Writes to the top 4 bits
    f |= cpu.registers.F.Z << 7;
    f |= cpu.registers.F.N << 6;
    f |= cpu.registers.F.H << 5;
    f |= cpu.registers.F.C << 4;
    _push8(cpu, memMap, cpu.registers.A);
    _push8(cpu, memMap, f);
}

void OpCodeMapping::Call::POP(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    info.registers_16[0] = reinterpret_cast<uint16_t*>(_pop16(cpu, memMap));
}

void OpCodeMapping::Call::POP_AF(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    const uint8_t f = _pop8(cpu, memMap);
    cpu.registers.A = _pop8(cpu, memMap);
    cpu.registers.F.Z = f & 0b10000000;
    cpu.registers.F.N = f & 0b01000000;
    cpu.registers.F.H = f & 0b00100000;
    cpu.registers.F.C = f & 0b00010000;
}

// In some instances here the 0x1 is redundant, but its left to make the intentions clear.
// Also, for *RLCA and other ***A variants the check is not performed (as it is a faster variant).
void OpCodeMapping::Call::_rl(LR35902& cpu, OpStructure& info, uint8_t reg, bool check = true){
    *(info.registers_8[0]) = *(info.registers_8[0]) << 1 | reg & 0x1;
    if(check)
        cpu.registers.F.Z = (*(info.registers_8[0]) == 0);
    cpu.registers.F.H = cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::RLCA(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.C = (*(info.registers_8[0]) >> 7) & 0x1;
    _rl(cpu, info, cpu.registers.F.C, false);
}

//RL operations use the previous carry value, while RL do not
void OpCodeMapping::Call::RLA(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F._C = cpu.registers.F.C;
    cpu.registers.F.C = *(info.registers_8[0]) & 0b10000000;
    _rl(cpu, info, cpu.registers.F._C, false);
}

void OpCodeMapping::Call::RLC(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.C = *(info.registers_8[0]) & 0b10000000;
    _rl(cpu, info, cpu.registers.F.C);
}

void OpCodeMapping::Call::RLC_HL(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    cpu.registers.F.C = val & 0b10000000;
    val = val << 1 | cpu.registers.F.C & 0x1;
    cpu.registers.F.Z = (val == 0);
    cpu.registers.F.H = cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::RL(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F._C = cpu.registers.F.C;
    cpu.registers.F.C = *(info.registers_8[0]) & 0b10000000;
    _rl(cpu, info, cpu.registers.F._C);
}
void OpCodeMapping::Call::RL_HL(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    cpu.registers.F._C = cpu.registers.F.C;
    cpu.registers.F.C = val & 0b10000000;
    val = val << 1 | cpu.registers.F.C;
    cpu.registers.F.Z = (val == 0);
    cpu.registers.F.H = cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::_rr(LR35902& cpu, OpStructure& info, uint8_t reg, bool check = true){
    *(info.registers_8[0]) = *(info.registers_8[0]) >> 1 | reg << 7;
    if(check)
        cpu.registers.F.Z = (*(info.registers_8[0]) == 0);
    cpu.registers.F.H = cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::RRCA(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.C = *(info.registers_8[0]) & 0x1;
    _rr(cpu, info, cpu.registers.F.C, false);
}

void OpCodeMapping::Call::RRA(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F._C = cpu.registers.F.C;
    cpu.registers.F.C = *(info.registers_8[0]) & 0x1;
    _rr(cpu, info, cpu.registers.F._C, false);
}

void OpCodeMapping::Call::RRC(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.C = *(info.registers_8[0]) & 0x1;
    _rr(cpu, info, cpu.registers.F.C);
}

void OpCodeMapping::Call::RRC_HL(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    cpu.registers.F.C = *(info.registers_8[0]) & 0x1;
    val = val >> 1 | cpu.registers.F.C << 7;
    cpu.registers.F.Z = (val == 0);
    cpu.registers.F.H = cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::RR(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F._C = cpu.registers.F.C;
    cpu.registers.F.C = *(info.registers_8[0]) & 0x1;
    _rr(cpu, info, cpu.registers.F._C);
}

void OpCodeMapping::Call::RR_HL(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    cpu.registers.F._C = cpu.registers.F.C;
    cpu.registers.F.C = *(info.registers_8[0]) & 0x1;
    val = val >> 1 | cpu.registers.F.C << 7;
    cpu.registers.F.Z = (val == 0);
    cpu.registers.F.H = cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::SLA(LR35902& cpu, Memory::Map&, OpStructure& info){
    //Check if after the shift it will "overflow"
    cpu.registers.F.C = *(info.registers_8[0]) & 0b10000000;
    *(info.registers_8[0]) <<= 1;
    cpu.registers.F.Z = (*(info.registers_8[0]) == 0);
    cpu.registers.F.N = cpu.registers.F.H = 0;
}

void OpCodeMapping::Call::SLA_HL(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    cpu.registers.F.C = val & 0b10000000;
    val <<= 1;
    cpu.registers.F.Z = (val == 0);
    cpu.registers.F.N = cpu.registers.F.H = 0;
}

void OpCodeMapping::Call::SRA(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.C = *(info.registers_8[0]) & 0b00000001;
    //shift right arithmetic (b7=b7)
    *(info.registers_8[0]) = *(info.registers_8[0]) >> 1 | *(info.registers_8[0]) & 0b10000000;
    cpu.registers.F.Z = (*(info.registers_8[0]) == 0);
    cpu.registers.F.N = cpu.registers.F.H = 0;
}

void OpCodeMapping::Call::SRA_HL(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    cpu.registers.F.C = val & 0b00000001;
    //shift right arithmetic (b7=b7)
    val = val >> 1 | val & 0b10000000;
    cpu.registers.F.Z = (val == 0);
    cpu.registers.F.N = cpu.registers.F.H = 0;
}

void OpCodeMapping::Call::SRL(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    //Check if after the shift it will "overflow"
    cpu.registers.F.C = *(info.registers_8[0]) & 0b10000000;
    *(info.registers_8[0]) >>= 1;
    cpu.registers.F.Z = (*(info.registers_8[0]) == 0);
    cpu.registers.F.N = cpu.registers.F.H = 0;
}

void OpCodeMapping::Call::SRL_HL(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    cpu.registers.F.C = val & 0b00000001;
    //shift right arithmetic (b7=b7)
    val >>=1;
    cpu.registers.F.Z = (val == 0);
    cpu.registers.F.N = cpu.registers.F.H = 0;
}

void OpCodeMapping::Call::SWAP(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    *(info.registers_8[0]) = *(info.registers_8[0]) << 4 | *(info.registers_8[0]) >> 4;
    cpu.registers.F.Z = (*(info.registers_8[0]) == 0);
    cpu.registers.F.N = cpu.registers.F.H = cpu.registers.F.C = 0;
}

void OpCodeMapping::Call::SWAP_HL(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    val = val << 4 | val >> 4;
    cpu.registers.F.Z = (val == 0);
    cpu.registers.F.N = cpu.registers.F.H = cpu.registers.F.C = 0;
}

void OpCodeMapping::Call::CPL(LR35902& cpu, Memory::Map&, OpStructure&){
    cpu.registers.A = ~cpu.registers.A;
    cpu.registers.F.H = cpu.registers.F.N = 1;
}

void OpCodeMapping::Call::SCF(LR35902& cpu, Memory::Map&, OpStructure&){
    cpu.registers.F.C = 1;
    cpu.registers.F.H = cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::CCF(LR35902& cpu, Memory::Map&, OpStructure&){
    cpu.registers.F.C = ~cpu.registers.F.C;
    cpu.registers.F.H = cpu.registers.F.N = 0;
}

void OpCodeMapping::Call::DAA(LR35902& cpu, Memory::Map&, OpStructure&){
    uint8_t& a = cpu.registers.A;

    // From https://forums.nesdev.com/viewtopic.php?t=15944.
    if (!cpu.registers.F.N) {  
        // after an addition, adjust if (half-)carry occurred or if result is out of bounds
        if (cpu.registers.F.C || a > 0x9F) { a += 0x60; cpu.registers.F.C = 1; }
        if (cpu.registers.F.H || (a & 0xF) > 9) { a += 0x6; }
        
    } else {  
        // after a subtraction, only adjust if (half-)carry occurred
        if (cpu.registers.F.C) { a -= 0x60; }
        if (cpu.registers.F.H) { a -= 0x6; }
    }
    // these flags are always updated
    cpu.registers.F.Z = (a == 0); // the usual z flag
    cpu.registers.F.H = 0; // h flag is always cleared
    cpu.registers.A = a;
}

void OpCodeMapping::Call::JR_r8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC+=*reinterpret_cast<int8_t*>(++cpu.registers.PC);
}

void OpCodeMapping::Call::JR_NZ_r8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    // jump if Z is not set
    ++cpu.registers.PC;
    if(!cpu.registers.F.Z ) {
       cpu.registers.PC+=*reinterpret_cast<int8_t*>(cpu.registers.PC);
       cpu.extraCycles=4;
    }
}

void OpCodeMapping::Call::JR_Z_r8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    ++cpu.registers.PC;
    if(cpu.registers.F.Z ) {
       cpu.registers.PC+=*reinterpret_cast<int8_t*>(cpu.registers.PC);
       cpu.extraCycles=4;
    }
}

void OpCodeMapping::Call::JR_NC_r8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    // jump if C is not set
    ++cpu.registers.PC;
    if(!cpu.registers.F.C ) {
       cpu.registers.PC+=*reinterpret_cast<int8_t*>(cpu.registers.PC);
       cpu.extraCycles=4;
    }
}

void OpCodeMapping::Call::JR_C_r8(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    ++cpu.registers.PC;
    if(cpu.registers.F.C ) {
       cpu.registers.PC+=*reinterpret_cast<int8_t*>(cpu.registers.PC);
       cpu.extraCycles=4;
    }
}

//Absolute value, so we just assign it by using the value as the value stored as the position in the memory array
void OpCodeMapping::Call::JP_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint16_t pos = *reinterpret_cast<uint8_t*>(++cpu.registers.PC);
    pos |=(*reinterpret_cast<uint8_t*>(++cpu.registers.PC) << 8);
    cpu.registers.PC=memMap.getMemoryAt(pos);
    cpu.changedPC = true;
}

void OpCodeMapping::Call::JP_NZ_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info) {
    if(!cpu.registers.F.Z ) {
       JP_a16(cpu, memMap, info);
       cpu.extraCycles=4;
    } else{
        cpu.registers.PC+=2;
    }
}

void OpCodeMapping::Call::JP_Z_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    if(cpu.registers.F.Z) {
       JP_a16(cpu, memMap, info);
       cpu.extraCycles=4;
    } else{
        cpu.registers.PC+=2;
    }
}

void OpCodeMapping::Call::JP_NC_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    if(!cpu.registers.F.C) {
       JP_a16(cpu, memMap, info);
       cpu.extraCycles=4;
    } else{
        cpu.registers.PC+=2;
    }
}

void OpCodeMapping::Call::JP_C_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    if(cpu.registers.F.C ) {
       JP_a16(cpu, memMap, info);
       cpu.extraCycles=4;
    } else{
        cpu.registers.PC+=2;
    }
}
void OpCodeMapping::Call::JP_HL(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    cpu.registers.PC=memMap.getMemoryAt(cpu.registers.HL._pair);
    cpu.changedPC = true;
}


//Here we use the fact that the PC points to some address within the memory,
//So we subtract it from the memory start to get the current index (which is 16 bits)
void OpCodeMapping::Call::CALL_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint16_t target = *reinterpret_cast<uint8_t*>(++cpu.registers.PC);
    target |=(*reinterpret_cast<uint8_t*>(++cpu.registers.PC)) << 8;

    const ptrdiff_t index = (cpu.registers.PC - memMap.getRomStart());
    _push16(cpu, memMap, static_cast<uint16_t>(index));
    cpu.registers.PC=memMap.getMemoryAt(target);
    cpu.changedPC = true;
}

void OpCodeMapping::Call::CALL_NZ_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info) {
    // jump if Z is not set
    if(!cpu.registers.F.Z ) {
        CALL_a16(cpu, memMap, info);
        cpu.extraCycles=12;
    } else{
        cpu.registers.PC+=2;
    }
}

void OpCodeMapping::Call::CALL_Z_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if(cpu.registers.F.Z ) {
        CALL_a16(cpu, memMap, info);
        cpu.extraCycles=12;
    } else{
        cpu.registers.PC+=2;
    }
}

void OpCodeMapping::Call::CALL_NC_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    // jump if C is not set
    if(!cpu.registers.F.C ) {
        CALL_a16(cpu, memMap, info);
        cpu.extraCycles=12;
    } else{
        cpu.registers.PC+=2;
    }
}

void OpCodeMapping::Call::CALL_C_a16(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    // jump if Z is set
    if(cpu.registers.F.C ) {
        CALL_a16(cpu, memMap, info);
        cpu.extraCycles=12;
    } else{
        cpu.registers.PC+=2;
    }
}

void OpCodeMapping::Call::EI(LR35902& cpu, Memory::Map&, OpStructure& ){
    cpu.imeType = IMEType::OnNext;
}

void OpCodeMapping::Call::DI(LR35902& cpu, Memory::Map&, OpStructure& ){
    cpu.imeType = IMEType::None;
}

void OpCodeMapping::Call::_push8(LR35902& cpu, Memory::Map& memMap, uint8_t val){
    memMap.write(val, --cpu.registers.SP);
}

void OpCodeMapping::Call::_push16(LR35902& cpu, Memory::Map& memMap, uint16_t val){
    memMap.write(val & 0xFF, --cpu.registers.SP);
    memMap.write(val >> 8, --cpu.registers.SP);
}

uint8_t OpCodeMapping::Call::_pop8(LR35902& cpu, Memory::Map& memMap){
    return memMap.read(cpu.registers.SP++);
}

uint16_t OpCodeMapping::Call::_pop16(LR35902& cpu, Memory::Map& memMap){
    int16_t val = memMap.read(cpu.registers.SP++) << 8;
    val |= memMap.read(cpu.registers.SP++);
    return val;
}

template<int target>
void OpCodeMapping::Call::_rst(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    uint16_t index = *reinterpret_cast<uint8_t*>(++cpu.registers.PC);
    index |=(*reinterpret_cast<uint8_t*>(++cpu.registers.PC)) << 8;

    _push16(cpu, memMap, static_cast<uint16_t>(index));
    cpu.registers.PC=memMap.getMemoryAt(target);
    cpu.changedPC = true;
}

template<int N>
void OpCodeMapping::Call::_bit(LR35902& cpu, Memory::Map&, OpStructure& info){
    cpu.registers.F.Z = ((*(info.registers_8[0]) & (1UL << N)) == 0);
    cpu.registers.F.N = 0;
    cpu.registers.F.H = 1;
}

template<int N>
void OpCodeMapping::Call::_bit_hl(LR35902& cpu, Memory::Map& memMap, OpStructure& info){
    uint8_t val = memMap.read(cpu.registers.HL._pair);
    cpu.registers.F.Z = ((val & (1UL << N)) == 0);
    cpu.registers.F.N = 0;
    cpu.registers.F.H = 1;
}

template<int N>
void OpCodeMapping::Call::_res(LR35902& cpu, Memory::Map&, OpStructure& info){
    *(info.registers_8[0]) &= ~(1UL << N);
}

template<int N>
void OpCodeMapping::Call::_res_hl(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    val &= ~(1UL << N);
}

template<int N>
void OpCodeMapping::Call::_set(LR35902& cpu, Memory::Map&, OpStructure& info){
    *(info.registers_8[0]) |= (1UL << N);
}

template<int N>
void OpCodeMapping::Call::_set_hl(LR35902& cpu, Memory::Map& memMap, OpStructure&){
    uint8_t& val = memMap.read(cpu.registers.HL._pair);
    val |= (1UL << N);
}