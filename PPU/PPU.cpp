#include <PPU.h>
#include <Bus.h>

namespace{
    /*Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
     Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
     Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
     Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
     Bit 2 - Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
     Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
             0: During H-Blank
             1: During V-Blank
             2: During Searching OAM
             3: During Transferring Data to LCD Driver
    */
    const uint16_t LCD_STATUS_REGISTER_ADDR = 0xFF41;

    //Scrolls and position
    const uint16_t LCD_SCY_ADDR = 0xFF42;
    const uint16_t LCD_SCX_ADDR = 0xFF43;

    //Used to trigger interruption when in specific Y position
    const uint16_t LCD_LY_ADDR = 0xFF44;
    const uint16_t LCD_LYC_ADDR = 0xFF45;

    //Specified Window x and y position
    const uint16_t LCD_WY_ADDR = 0xFF4A;
    const uint16_t LCD_WX_ADDR = 0xFF4B;

    //Pallete
    //Background Pallete
    const uint16_t BGP_ADDR =  0xFF47;
    //Object Palette
    const uint16_t OBP0_ADDR =  0xFF48;
    const uint16_t OBP1_ADDR =  0xFF49;

    //OAM DMA Transfers
    const uint16_t DMA_ADDR = 0xFF46;

    //Tile data start
    //each block is a 128 tile with 16 bytes each
    //each 2 bytes is a line (so each line is 16 bits)
    const uint16_t TILE_ADDR = 0x8000;
    const uint16_t TILE_SIZE = 0x17FF;

    const uint16_t CLOCKS_PER_LINE = 456;

}
using namespace PPU;

Core::Core(Bus* bus) : bus(bus){}

void Core::setMode(uint8_t mode){
    bus->memoryMap[LCD_STATUS_REGISTER_ADDR] &= 0b11111100;
    bus->memoryMap[LCD_STATUS_REGISTER_ADDR] |= mode;
    //We also check if the the specifc bit for that interrupt is enabled, if it is
    //during the mode switch we trigger a LCDC interrupt
    const uint8_t modeBit = (mode + 3);
    if(bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & (1UL << modeBit))
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);
}

uint8_t Core::getMode(){
    return bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x3;
}

void Core::processMode0(){
    if(modeProcessed == 0 || getMode() != 0)
        return;
    //Check if mode is also enabled
    if((bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00001000) == 0)
        return;

    //std::cout << "processMode0" << std::endl;
    modeProcessed = 0;
}
void Core::processMode1(){
    if(modeProcessed == 1 || getMode() != 1)
        return;
    
    //Check if mode is also enabled
    if((bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00010000) == 0)
        return;
    //std::cout << "processMode1" << std::endl;
    modeProcessed = 1;
}

void Core::processMode2(){
    //Here I need to figure out which tiles will be used
    if(modeProcessed == 2 || getMode() != 2)
        return;

    //Check if mode is also enabled
    if((bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00100000) == 0)
        return;

    //std::cout << "processMode2" << std::endl;
    modeProcessed = 2;
}

void Core::processMode3(){
    //Mode 3 is always enabled
    if(modeProcessed == 3 || getMode() != 3)
        return;

    //std::cout << "processMode3" << std::endl;
    modeProcessed = 3;
}

void Core::processModes(){
    processMode0();
    processMode1();
    processMode2();
    processMode3();
}

void Core::tick(uint16_t ticks) {
    static uint16_t dots = 0;
    if(!isLCDEnabled())
        return;
    //Each 4 "dots" per CPU cycle
    dots += ticks * 4;
    //Cycle through modes, 2, 3, 0, 1.
    //OAM, DRAWING, H-BLANK, V-BLANK

    //During modes 2 and 3 CPU cannot access the OAM
    //During mode 3 CPU cannot access VRAM
    //So I can just run once, as it would be expected that at this time everything was processed
    //This is usually called "Interrupt" on some docs, but I dont have to actually trigger an interruption
    //Just do what the PPU documentation states that its done at this time
    if(dots <= 80){
        setMode(2);
    } else if(dots <= 252){
        //Mode 3 is set to the shortest amount of time 172 dots (as we do the rendering in one shot)
        //then we give the most amount of time back to the CPU to perform operations
        //While it is possilble to have accurate timming currently its probably not worth it (unless some game is really bound to this timming).
        setMode(3);
    } else if(dots <= 456){
        //Mode 0 does nothing, 
        setMode(0);
    } else {
        dots -= CLOCKS_PER_LINE;
        uint8_t& line = bus->memoryMap[LCD_LY_ADDR];
        //< 144 Normal render
        //renderline
        if(line < 144){
            //regular rendering
        }
        else if(line >=144 && line < 153){
            //if V-BLANK interrupt.. as its done only on line 144, its done only once (we will increment the line after that.)
            setMode(1);
        }
        line++;
    }
    
    //Those will only be triggered once, each one will validate itself
    //if the mode is set and if the mode processed is not itself (which means that it was not)
    //computed yet
    processModes();

    checkLYC_LY();
}

bool Core::isLCDEnabled() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b10000000; }
bool Core::isWindowTileMapDisplaySelectHigh() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b01000000; }
bool Core::isWindowDisplayEnabled() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00100000; }
bool Core::isBgWindowTileHigh() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00010000; }
bool Core::isBgTileMapHigh() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00001000; }
bool Core::isOBGSize() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00000100; }
bool Core::isOBGDisplayEnabled() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00000010; }
bool Core::isBGWindowDisplayPriority() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0x1; }

void Core::renderLine(){
    const uint8_t Y = bus->memoryMap [LCD_LY_ADDR];

}

//Have in mind that the window is not THE WINDOW, it is a subsection that the PPU can render
void Core::renderWindow() { 

}

void Core::checkLYC_LY(){
    //Checkk for VBLANK
    //std::cout << static_cast<uint16_t>(bus->memoryMap[LCD_LY_ADDR]) << std::endl;
    //std::cout << (bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x00010000) << std::endl;
    if(bus->memoryMap[LCD_LY_ADDR] == 144/* && bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x00010000*/) {
        //std::cout << "VBLANK HERE WE GO" << std::endl;
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::VBLANK);

        //If I also need to set LCDC during VBLANK
        if(bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x00010000)
            bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);

    } else if(bus->memoryMap[LCD_LY_ADDR] == bus->memoryMap[LCD_LYC_ADDR]) {
        //If the coincidence interrupt is not enabled, we just skip this
        if((bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00100000) == 0)
            return;

        //Set Coincidence flag
        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] |= 0b0000100;
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);
    } else{
        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] &= ~(0b0000100);
    }   
}