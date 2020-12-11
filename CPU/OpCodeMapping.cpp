#include <OpCodeMapping.h>
#include <LR35902.h>

using namespace CPU;
using OP = OpCodeMapping::Call;
OpCodeMapping::OpCodeMapping() :
    instructions({
        //NOP, LD
        {1, OP::NOP}, {3, OP::LD_REG_d16, &LR35902::registers.BC._pair},// {1, OP::LD_REGV_REG, &LR35902::registers.BC._pair, &LR35902::registers.A}, //{1, OP::INC, &LR35902::registers.BC._pair}//, {1, OP::INC, &LR35902::registers.BC._reg[0]}, {1, OP::DEC, &LR35902::registers.BC._reg[0]}
    })
{}

void OpCodeMapping::Call::NOP(char** pc, Memory::Map& memMap, const OpStructure& info){}
void OpCodeMapping::Call::LD_REG_d16(char** pc, Memory::Map& memMap, const OpStructure& info){


}

void OpCodeMapping::Call::LD_REGV_REG(char** pc, Memory::Map& memMap, const OpStructure& info){


}

void OpCodeMapping::Call::LD_REGV_d16(char**, Memory::Map&, const OpStructure&){}

void OpCodeMapping::Call::INC(char**, Memory::Map&, const OpStructure&){}

void OpCodeMapping::Call::DEC(char**, Memory::Map&, const OpStructure&){}