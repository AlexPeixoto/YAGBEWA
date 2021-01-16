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
    const uint16_t LCD_CONTROL_REGISTER_ADDR = 0xFF40;
    const uint16_t LCD_STATUS_REGISTER_ADDR = 0xFF41;

    //Scrolls and position
    const uint16_t LCD_SCY_ADDR = 0xFF42;
    const uint16_t LCD_SCX_ADDR = 0xFF43;
    const uint16_t LCD_LY_ADDR = 0xFF44;
    const uint16_t LCD_LYC_ADDR = 0xFF45;

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
}
using namespace PPU;

Core::Core(Bus* bus) : bus(bus){}

void Core::tick() {

}

/*void Core::checkLYC_LY(){
    if(bus->memoryMap[LCD_LY_ADDR] == bus->memoryMap[LCD_LYC_ADDR]) {
        //Set Coincidence flag
        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] |= 0b0000100;
        //TODO
        //IF INTERRUPTION ENABLED, ACTIVATE INT 48 interruption

    }
}*/