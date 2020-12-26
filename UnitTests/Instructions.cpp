#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <Catch/catch2.hpp>

//Hack for UT
#define private public
#include <CPU/OpCodeMapping.h>
#include <CPU/OpStructure.h>

namespace {
    CPU::OpCodeMapping mapping;
    Memory::Map memMap;
}
//Have to add the .o files from the CPU folder
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    char **pc = nullptr;

    
    auto _instruction = mapping.instructions[0];
    _instruction.call(pc, memMap, _instruction);
}