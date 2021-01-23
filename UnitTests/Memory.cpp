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

TEST_CASE( "Test pointer assignment from uint16_t", "[ADDRESS]") {
    resetRegisters();
    uint8_t addrPart1 = 0xF3;
    uint8_t addrPart2 = 0x10;
    uint8_t **memory = new uint8_t*();
    *memory = new uint8_t[16]{0xF3, 0x10};

    uint8_t **pc = new uint8_t*();
    uint16_t pos = *reinterpret_cast<uint8_t*>((*memory)++);
    pos |=(*reinterpret_cast<uint8_t*>((*memory)++)) << 8;
    *pc = reinterpret_cast<uint8_t *>(pos);

    REQUIRE(*pc == reinterpret_cast<uint8_t*>(0x10F3));
}

TEST_CASE( "Test pointer subtraction uint16_t", "[ADDRESS]") {
    resetRegisters();

    uint8_t memory[255];
    uint8_t *start = &memory[0];
    uint8_t *current = &memory[30];

    ptrdiff_t index = current - start;

    REQUIRE(index == 30);
}