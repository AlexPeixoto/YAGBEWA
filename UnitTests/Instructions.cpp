#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <Catch/catch2.hpp>

//Hack for UT
#define private public
#include <CPU/OpCodeMapping.h>
#include <CPU/OpStructure.h>
#include <CPU/LR35902.h>
#include <Bus.h>

using namespace CPU;
using namespace Memory;
namespace {
    LR35902 cpu(new Bus());
    OpCodeMapping mapping(cpu);
    Map memMap;
    

    void resetRegisters(){
        cpu.registers.A = 0;
        cpu.registers.BC[0] = 0;
        cpu.registers.BC[1] = 0;
        cpu.registers.DE[0] = 0;
        cpu.registers.DE[1] = 0;
        cpu.registers.HL[0] = 0;
        cpu.registers.HL[1] = 0;
        cpu.registers.SP = 0;
        cpu.registers.PC = 0;

        cpu.registers.F.Z = 0;
        cpu.registers.F.N = 0;
        cpu.registers.F.H = 0;
        cpu.registers.F.C = 0;
        cpu.registers.F._C = 0;
    }
}

TEST_CASE( "Reinterpret Cast trick", "[PC]" ) {
    uint8_t **pc = new uint8_t*();
    *pc = new uint8_t[16]{0x0, 0x1, 0b10000011};

    REQUIRE(reinterpret_cast<int8_t*>(*pc)[2] == static_cast<int8_t>(-125));
}


TEST_CASE( "Check for HALT", "[INSTRUCTIONS]" ) {
    resetRegisters();
    REQUIRE(cpu.haltType == CPU::HaltType::None);
    auto _instruction = mapping.instructions[0x76];
    _instruction.call(cpu, memMap, _instruction);
    REQUIRE(cpu.haltType == CPU::HaltType::Normal);
}

TEST_CASE( "Test ADC8", "[INSTRUCTIONS]" ) {
    resetRegisters();
    char **pc = new char*();
    
    auto _instruction = mapping.instructions[0x88];
    cpu.registers.A = 10;
    _instruction.registers_8[1] = new uint8_t();
    *(_instruction.registers_8[1]) = static_cast<char>(1);
    _instruction.call(cpu, memMap, _instruction);
    REQUIRE(cpu.registers.F.Z == false);
    REQUIRE(cpu.registers.F.N == 0);
    REQUIRE(cpu.registers.F.H == 0);
    REQUIRE(cpu.registers.F.C == 0);
    REQUIRE(cpu.registers.A == 11);

    delete _instruction.registers_8[1];
}

TEST_CASE( "Test ADC8 Half", "[INSTRUCTIONS]" ) {
    resetRegisters();
    
    auto _instruction = mapping.instructions[0x88];
    cpu.registers.A = 0xF;
    _instruction.registers_8[1] = new uint8_t();
    *(_instruction.registers_8[1]) = static_cast<char>(0);
    _instruction.call(cpu, memMap, _instruction);
    REQUIRE(cpu.registers.F.H == 0);
    // Now do a half overflow
    *(_instruction.registers_8[1]) = static_cast<char>(1);
    _instruction.call(cpu, memMap, _instruction);
    REQUIRE(cpu.registers.F.H == 1);
    REQUIRE(cpu.registers.F.C == 0);
    delete _instruction.registers_8[1];
}

TEST_CASE( "Test ADC8 Carry", "[INSTRUCTIONS]" ) {
    char **pc = new char*();
    
    auto _instruction = mapping.instructions[0x88];
    cpu.registers.A = 0xFF;
    _instruction.registers_8[1] = new uint8_t();
    *(_instruction.registers_8[1]) = static_cast<char>(0);
    _instruction.call(cpu, memMap, _instruction);
    REQUIRE(cpu.registers.F.C == 0);
    // Now do a half overflow
    *(_instruction.registers_8[1]) = static_cast<char>(1);
    _instruction.call(cpu, memMap, _instruction);
    REQUIRE(cpu.registers.F.C == 1);
    delete _instruction.registers_8[1];
}

TEST_CASE( "Test DAA", "[INSTRUCTIONS]" ) {
    resetRegisters();
    char **pc = new char*();
    
    auto _instruction = mapping.instructions[0x27];
    cpu.registers.A = 14;
    _instruction.call(cpu, memMap, _instruction);
    REQUIRE(static_cast<uint32_t>(cpu.registers.A) == 0x14);
}

TEST_CASE( "Test SET", "[INSTRUCTIONS]" ) {
    resetRegisters();
    auto _instruction = mapping.instructions[0xcb];
    cpu.registers.PC = new uint8_t[2]{0xF0, 0xF0};
    cpu.registers.BC[0] = 0;
    _instruction.call(cpu, memMap, _instruction);
    REQUIRE(static_cast<uint32_t>(cpu.registers.BC[0]) == 0b01000000);
}