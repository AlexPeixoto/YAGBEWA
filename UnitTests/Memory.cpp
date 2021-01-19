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
        cpu.registers.BC._pair = 0;
        cpu.registers.DE._pair = 0;
        cpu.registers.HL._pair = 0;
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

TEST_CASE( "Test union for proper byte arrangement", "[UNION MEMORY ARRANGEMENT]") {
    resetRegisters();

    cpu.registers.DE._reg[0] = 0;
    cpu.registers.DE._reg[1] = 0x48;

    cpu.registers.HL._reg[0] = 0x02;
    cpu.registers.HL._reg[1] = 0xFB;
    
    std::cout << "DE" << std::hex << cpu.registers.DE._pair << std::endl;
    std::cout << "D" << std::hex << cpu.registers.DE._reg[0] << std::endl;
    std::cout << "E" << std::hex << cpu.registers.DE._reg[1] << std::endl;
    std::cout << "HL" << std::hex << cpu.registers.HL._pair << std::endl;
    std::cout << "H" << std::hex << cpu.registers.HL._reg[0] << std::endl;
    std::cout << "L" << std::hex << cpu.registers.HL._reg[1] << std::endl;
    cpu.registers.DE._pair += cpu.registers.HL._pair;
    std::cout << "After sum" << std::endl;
    std::cout << "D" << std::hex << cpu.registers.DE._reg[0] << std::endl;
    std::cout << "E" << std::hex << cpu.registers.DE._reg[1] << std::endl;
    std::cout << "DE" << std::hex << cpu.registers.DE._pair << std::endl;

    REQUIRE(cpu.registers.DE._pair == 0x0343);
}