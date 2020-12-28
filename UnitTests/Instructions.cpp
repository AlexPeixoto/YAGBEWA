#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <Catch/catch2.hpp>

//Hack for UT
#define private public
#include <CPU/OpCodeMapping.h>
#include <CPU/OpStructure.h>
#include <CPU/LR35902.h>

using namespace CPU;
using namespace Memory;
namespace {
    OpCodeMapping mapping;
    Map memMap;
}

TEST_CASE( "Check for STOP", "[INSTRUCTIONS]" ) {
    REQUIRE(CPU::LR35902::halt == false);
    auto _instruction = mapping.instructions[0x76];
    _instruction.call(nullptr, memMap, _instruction);
    REQUIRE(CPU::LR35902::halt == true);
}

TEST_CASE( "Test ADC8", "[INSTRUCTIONS]" ) {
    char **pc = new char*();
    *pc = new char[16]{0x0, 0x1};
    
    auto _instruction = mapping.instructions[0x88];
    LR35902::registers.A = 10;
    _instruction.registers_8[0] = new uint8_t();
    *(_instruction.registers_8[0]) = static_cast<char>(1);
    _instruction.call(pc, memMap, _instruction);
    REQUIRE(LR35902::registers.F.Z == false);
    REQUIRE(LR35902::registers.F.N == 0);
    REQUIRE(LR35902::registers.F.H == 0);
    REQUIRE(LR35902::registers.F.C == 0);
    REQUIRE(LR35902::registers.A == 11);

    delete _instruction.registers_8[0];
}

TEST_CASE( "Test ADC8 Half", "[INSTRUCTIONS]" ) {
    char **pc = new char*();
    *pc = new char[16]{0x0, 0x1};
    
    auto _instruction = mapping.instructions[0x88];
    LR35902::registers.A = 0xF;
    _instruction.registers_8[0] = new uint8_t();
    *(_instruction.registers_8[0]) = static_cast<char>(0);
    _instruction.call(pc, memMap, _instruction);
    REQUIRE(LR35902::registers.F.H == 0);
    // Now do a half overflow
    *(_instruction.registers_8[0]) = static_cast<char>(1);
    _instruction.call(pc, memMap, _instruction);
    REQUIRE(LR35902::registers.F.H == 1);
    REQUIRE(LR35902::registers.F.C == 0);
    delete _instruction.registers_8[0];
}

TEST_CASE( "Test ADC8 Carry", "[INSTRUCTIONS]" ) {
    char **pc = new char*();
    *pc = new char[16]{0x0, 0x1};
    
    auto _instruction = mapping.instructions[0x88];
    LR35902::registers.A = 0xFF;
    _instruction.registers_8[0] = new uint8_t();
    *(_instruction.registers_8[0]) = static_cast<char>(0);
    _instruction.call(pc, memMap, _instruction);
    REQUIRE(LR35902::registers.F.C == 0);
    // Now do a half overflow
    *(_instruction.registers_8[0]) = static_cast<char>(1);
    _instruction.call(pc, memMap, _instruction);
    REQUIRE(LR35902::registers.F.C == 1);
    delete _instruction.registers_8[0];
}