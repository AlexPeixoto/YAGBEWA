#pragma once

#include <cstdint>
#include <functional>

//This file maps all instructions, parmeters, registers and jump conditions. It also defines the Operation struct that will store the instruction + parameters in a way that is easier to use in order to process.
namespace CPU{
    class LR35902;
    //This can, in theory, be initialized at compile time
    struct OpStructure{
        //Stores registers being used.
        uint16_t* registers_16[2];
        //8 bit registers
        uint8_t* registers_8[2];
        bool invalid;
        uint8_t cycleCount;

        using FunctionCallRef = std::function<void(LR35902&, Memory::Map&, OpStructure&)>;
        // Call the function, this contains the PC, the memory map and the a reference to itself (so parameters and type can be read)
        FunctionCallRef call;
        
        OpStructure(){
            this->invalid=true;
        }

        OpStructure(int cycleCount, FunctionCallRef call){
            this->cycleCount = cycleCount;
            this->call = call;
            this->invalid = false;
        }

        // I really dont like this solution below, but its probably the simplest one and do not make me need to perform if statements during a fetch.
        OpStructure(int cycleCount, FunctionCallRef call,
                   uint16_t* register_1, uint16_t* register_2 = 0)
                   : OpStructure(cycleCount, call) {
            this->registers_16[0] = register_1;
            this->registers_16[1] = register_2;
        }

        OpStructure(int cycleCount, FunctionCallRef call,
                   uint8_t* register_1, uint8_t* register_2 = 0)
                   : OpStructure(cycleCount, call) {
            this->registers_8[0] = register_1;
            this->registers_8[1] = register_2;
        }

        OpStructure(int cycleCount, FunctionCallRef call,
                   uint16_t* register_1, uint8_t* register_2)
                   : OpStructure(cycleCount, call) {
            this->registers_16[0] = register_1;
            this->registers_8[0] = register_2;
        }

        OpStructure(int cycleCount, FunctionCallRef call,
                   uint8_t* register_1, uint16_t* register_2)
                   : OpStructure(cycleCount, call) {
            this->registers_8[0] = register_1;
            this->registers_16[0] = register_2;
        }
    };
}