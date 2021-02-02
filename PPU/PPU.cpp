#include <PPU.h>
#include <Bus.h>

namespace{

    constexpr uint16_t LCD_CONTROL_REGISTER_ADDR = 0xFF40;

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
    constexpr uint16_t LCD_STATUS_REGISTER_ADDR = 0xFF41;

    //Scrolls and position (viewport)
    constexpr uint16_t LCD_SCY_ADDR = 0xFF42;
    constexpr uint16_t LCD_SCX_ADDR = 0xFF43;

    //Used to trigger interruption when in specific Y position
    constexpr uint16_t LCD_LY_ADDR = 0xFF44;
    constexpr uint16_t LCD_LYC_ADDR = 0xFF45;

    //Specified Window x and y position (for example, like a dialog box)
    constexpr uint16_t LCD_WY_ADDR = 0xFF4A;
    constexpr uint16_t LCD_WX_ADDR = 0xFF4B;

    //Pallete
    //Background Pallete
    constexpr uint16_t BGP_ADDR =  0xFF47;
    //Object Palette
    constexpr uint16_t OBP0_ADDR =  0xFF48;
    constexpr uint16_t OBP1_ADDR =  0xFF49;

    //OAM DMA Transfers
    constexpr uint16_t OAM_TABLE_ADDR = 0xFE00;
    constexpr uint16_t DMA_ADDR = 0xFF46;

    //Tile data start
    //each block is a 128 tile with 16 bytes each
    //each 2 bytes is a line (so each line is 16 bits)
    constexpr uint16_t TILE_ADDR = 0x8000;
    constexpr uint16_t TILE_SIZE = 0x17FF;

    constexpr uint16_t CLOCKS_PER_LINE = 456;

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

void Core::initPalleteTable(std::array<Color, 4>& palette, uint16_t memPosition){
    const uint8_t paletteMem = bus->memoryMap[memPosition];
    for(int x=0; x<=3; x++){
        switch((paletteMem >> (x * 2)) & 0x3){
            case 0x00:
                palette[x] = {0xFF, 0xFF, 0xFF};
                continue;
            case 0x01:
                palette[x] = {0xCC, 0xCC, 0xCC};
                continue;
            case 0x02:
                palette[x] = {0x66, 0x66, 0x66};
                continue;
            case 0x03:
                palette[x] = {0x00, 0x00, 0x00};
                continue;
        }
    }
}

void Core::initSprites(){
    for(int x=0; x<40; x++){
        //4 bytes per entry
        const uint8_t spacing = 4;
        const uint8_t flags = bus->memoryMap[OAM_TABLE_ADDR + spacing + 3];
        sprites.at(x) = {
            bus->memoryMap[OAM_TABLE_ADDR + spacing], //pos x
            bus->memoryMap[OAM_TABLE_ADDR + spacing + 1], //pos y
            bus->memoryMap[OAM_TABLE_ADDR + spacing + 2], //tile number
            static_cast<uint8_t>(flags & 0b1000000), //Priority
            static_cast<uint8_t>(flags & 0b0100000), //Y-Flip
            static_cast<uint8_t>(flags & 0b0010000), //X-Flip
            static_cast<uint8_t>(flags & 0b0001000) //Palette
        };
    }
}

void Core::renderLine(){
    //Lets check the tile mode first (tile = background)
    const uint16_t baseTileAddr = isTileDataSelectHigh() ? 0x8000 : 0x8800;
    static uint16_t count=0;
    const uint16_t baseSpriteAddr = 0x8000;
    const bool isTallSprite = isSpriteDoubleHeight();

    //Background map information, this is just the index to be used
    //To access the baseTileAddr above
    const uint16_t baseBackgroundMapAddr = isBgTileMapHigh() ? 0x9C00 : 0x9800;
    
    //This is the line that I will render
    const uint8_t line = bus->memoryMap[LCD_LY_ADDR];

    //I need 2 things here, my real Y position on the screen, this is calculated with line being rendered + SCY
    //which is the "adjustment"
    //0xFF42 + 0xFF44
    const int yAdjusted = line + bus->memoryMap[LCD_SCY_ADDR];
    const int yTileAdjusted = (yAdjusted / 8);
    
    //Now I calculate the difference between the tile index and the adjustment
    //For example, I know that each tile is 8 pixels, so if SCY is 14 I skip the first Tile, then 6 pixels of the picked tile
    const int ySkipPixels = (yAdjusted % 8);

    //This should ALL be white
    for(int x=0; x<160; x++){
        //Render background, have in mind that I could possibly do the opposite (render 32 tiles)
        //would probably be WAY cheaper
        //Should be pixel + scroll X
        const int xAdjusted = x + bus->memoryMap[LCD_SCX_ADDR];
        const int xTileAdjusted = (xAdjusted / 8);
        
        bool backgroundRendered = false;
        //Each tile is a byte, so we retrieve the byte that corresponds to this position
        //Missing signed vs unsigned here (depending on the )
        //Here we are looking at the tilemap to extract the tile index
        const uint32_t tileMemPos = baseBackgroundMapAddr + (yTileAdjusted * 32 /*tiles per line*/) + xTileAdjusted;
        const int tileIndex = bus->memoryMap[tileMemPos];   
         
        const uint16_t colorByte = baseTileAddr +
                                  (tileIndex * 16) +
                                  (ySkipPixels * 2); //2 bytes per line
         
        const uint8_t colorIndex_0 = bus->memoryMap[colorByte];
        const uint8_t colorIndex_1 = bus->memoryMap[colorByte + 1];
        int bit = (xAdjusted % 8);
        bit -= 7;
        bit *= -1;
        const uint8_t index = (colorIndex_0 >> bit) & 0x1 | (((colorIndex_1 >> bit) & 0x1) << 1);

        internalBuffer[x][line] = backgroundColorMap.at(index);
    }
}

void Core::processMode0(){
    if(modeProcessed == 0 || getMode() != 0)
        return;
    //Check if mode is also enabled
    if((bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00001000) == 0)
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);

    
    modeProcessed = 0;
}
void Core::processMode1(){
    if(modeProcessed == 1 || getMode() != 1)
        return;
    
    //Check if mode is also enabled
    if((bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00010000) == 0)
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);

    //Lets copy internal buffer into screen buffer (its not exactly needed, but more as a safety measure)
    for(int x=0; x<160; x++)
        for(int y=0; y<144; y++)
            screen[x][y]=internalBuffer[x][y];
    
    modeProcessed = 1;
}

void Core::processMode2(){
    //Here I need to figure out which tiles will be used
    if(modeProcessed == 2 || getMode() != 2)
        return;

    //Check if mode is also enabled
    if((bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00100000) == 0)
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);

    //Load backgroundColorMap palette from BGP_ADDR
    initPalleteTable(backgroundColorMap, BGP_ADDR);
    //Init both object palletes
    //initPalleteTable(objectPallete1, OBP0_ADDR);
    //initPalleteTable(objectPallate2, OBP1_ADDR);

    
    modeProcessed = 2;
}

void Core::processMode3(){
    //Mode 3 is always enabled
    if(modeProcessed == 3 || getMode() != 3)
        return;

    renderLine();
    
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
    static bool lineRendered = false;
    if(!isLCDEnabled())
        return;
    //Each 4 "dots" per CPU cycle
    //Each scanline is 456 dots (114 CPU cycles) 
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
        lineRendered = false;
        setMode(0);
    } else {
        dots -= CLOCKS_PER_LINE;
        uint8_t& line = bus->memoryMap[LCD_LY_ADDR];
        //< 144 Normal render
        //renderline
        if(line < 144){
        }
        else if(line >=144 && line < 153){
            //if V-BLANK interrupt.. as its done only on line 144, its done only once (we will increment the line after that.)
            setMode(1);
        }
        //Is 153, we reset the line
        else{
            line = 0;
            
            

            checkLYC_LY();
            return;
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
bool Core::isTileDataSelectHigh() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00010000; }
bool Core::isBgTileMapHigh() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00001000; }
bool Core::isSpriteDoubleHeight() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00000100; }
bool Core::isSpriteEnabled() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00000010; }
bool Core::isBGWindowDisplayPriority() { return bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0x1; }


//Have in mind that the window is not THE WINDOW, it is a subsection that the PPU can render
void Core::renderWindow() { 

}

void Core::checkLYC_LY(){
    //Checkk for VBLANK
    if(bus->memoryMap[LCD_LY_ADDR] == 144/* && bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x00010000*/) {
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::VBLANK);

        //If I also need to set LCDC during VBLANK
        if(bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x00010000)
            bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);

    } else if(bus->memoryMap[LCD_LY_ADDR] == bus->memoryMap[LCD_LYC_ADDR]) {
        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] |= 0b0000100;
        //If the coincidence interrupt is not enabled, we just skip this
        if((bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00100000) == 0)
            return;

        //Set Coincidence flag
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);
    } else{
        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] &= ~(0b0000100);
    }   
}