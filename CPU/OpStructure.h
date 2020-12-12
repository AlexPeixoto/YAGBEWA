#pragma once

#include <cstdint>
#include <functional>

//This file maps all instructions, parmeters, registers and jump conditions. It also defines the Operation struct that will store the instruction + parameters in a way that is easier to use in order to process.
namespace CPU{
    enum class INSTRUCTION{
        NOP, LD, INC, DEC, RLCA, ADD, RRCA, STOP, RLA, JR, RRA, CPL, SCF, DAA, CCF, HALT, SUB, ADC, SBC, AND, XOR, OR, CP, RET, POP, JP, PUSH, RST, CB, CALL, RETI, LDH, DI, EI,
        //CB
        RLC,
        RRC,
        RL, RR,
        SLA, SRA,
        SWAP, SRL,
        BIT,/* BIT,
        BIT, BIT,
        BIT, BIT,
        BIT, BIT,*/
        RES,/* RES,
        RES, RES,
        RES, RES,
        RES, RES,*/
        SET/*, SET,
        SET, SET,
        SET, SET, 
        SET, SET*/
    };

    enum class PARAMETER_TYPE{
        NONE,

        D8,
        A8,
        R8,

        D16,
        A16,

        REG,
        REGV, //REG contains the address.
        JMP,
        RST,
        BIT
    };
    enum class REG{
        //Preserve this order from B to A as this is the order seen for several instructions
        B, C,
        D, E,
        H, L,
        HL,
        A,

        BC,
        DE,
        HLP,
        HLM,
        F, //F IS NOT ALWAYS USED, IT CONTAINS ALL THE FLAGS (ZNHC)
        AF,
        Z,
        SP
    };

    //It is passed as a parameter (type JUMP)
    enum class JMP{
        NZ,
        Z,
        NC,
        C
    };

    //Maps parameters for RST calls
    enum class RST{
        H00,
        H10,
        H20,
        H30,
        H08,
        H18,
        H28,
        H38
    };
    
    //This can, in theory, be initialized at compile time
    struct OpStructure{
        //Stores registers being used.
        uint16_t* registers_16[2];
        //8 bit registers
        uint8_t* registers_8[2];
        bool invalid;
        uint8_t cycleCount;

        using FunctionCallRef = std::function<void(char**, Memory::Map&, OpStructure&)>;
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