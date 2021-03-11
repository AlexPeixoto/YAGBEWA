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
    constexpr uint16_t SPRITE_ADDR = 0x8000;
    constexpr uint16_t SPRITE_SIZE = 0x17FF;

    constexpr uint16_t CLOCKS_PER_LINE = 456;

    //8 Pixels
    constexpr uint8_t SPRITE_WIDTH = 8;
    constexpr uint8_t SPRITE_HEIGHT = 8;
}
using namespace PPU;

Core::Core(Bus* bus) : bus(bus){
    bus->memoryMap[LCD_LY_ADDR] = 153;
    spritesOnLine = 0;
    setMode(1);
}

void Core::setMode(uint8_t mode){
    //2 first bits are the mode
    bus->memoryMap[LCD_STATUS_REGISTER_ADDR] &= 0b11111100;
    bus->memoryMap[LCD_STATUS_REGISTER_ADDR] |= (mode & 0x3);
    //We also check if the the specifc bit for that interrupt is enabled, if it is
    //during the mode switch we trigger a LCDC interrupt
    const uint8_t modeBit = (mode + 2);
    if(bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & (1UL << modeBit))
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);
}

uint8_t Core::getMode(){
    return bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x3;
}

void Core::initPalleteTable(std::array<Color, 4>& palette, uint16_t memPosition){
    const uint8_t paletteMem = bus->memoryMap[memPosition];
    //std::cout << "Hex pallete mem value: " << std::hex << static_cast<uint32_t>(paletteMem) << " at " << std::hex << static_cast<uint32_t>(memPosition) << std::endl;
    for(int x=0; x<=3; x++){
        switch((paletteMem >> (x * 2)) & 0x3){
            case 0x00:
                //std::cout << "Pallete for: " << x << " is 00 {FF}" << std::endl;
                palette[x] = {0xFF, 0xFF, 0xFF};
                continue;
            case 0x01:
                //std::cout << "Pallete for: " << x << " is 01 {CC}" << std::endl;
                palette[x] = {0xCC, 0xCC, 0xCC};
                continue;
            case 0x02:
                //std::cout << "Pallete for: " << x << " is 02 {66}" << std::endl;
                palette[x] = {0x66, 0x66, 0x66};
                continue;
            case 0x03:
                //std::cout << "Pallete for: " << x << " is 03 {00}" << std::endl;
                palette[x] = {0x00, 0x00, 0x00};
                continue;
        }
    }
}

void Core::initSprites(){
    for(int x=0; x<40; x++){
        //4 bytes per entry
        const uint8_t spacing = 4;
        const uint8_t flags = bus->memoryMap[OAM_TABLE_ADDR + (x * spacing) + 3];
        //std::cout << "FULL FLAG: " << static_cast<uint32_t>(flags) << std::endl;
        sprites.at(x) = {
            bus->memoryMap[OAM_TABLE_ADDR + (x * spacing)], //pos x
            bus->memoryMap[OAM_TABLE_ADDR + (x * spacing) + 1], //pos y
            bus->memoryMap[OAM_TABLE_ADDR + (x * spacing) + 2], //tile number
            static_cast<uint8_t>((flags & 0b10000000) >> 7), //Priority
            static_cast<uint8_t>((flags & 0b01000000) >> 6), //Y-Flip
            static_cast<uint8_t>((flags & 0b00100000) >> 5), //X-Flip
            static_cast<uint8_t>((flags & 0b00010000) >> 4) //Palette
        };
    }
}

void Core::getSpritesOnLine(){
    //Look for all the positions on the line
    spritesOnLine=0;
    const bool isTallSprite = isSpriteDoubleHeight();
    const uint16_t line = bus->memoryMap[LCD_LY_ADDR];
    //If its tall its 16 pixels, if not its 8
    const uint8_t height = isTallSprite ? 16 : 8;
    for(uint8_t pos=0; pos < 40; pos++){
        const auto sprite = sprites.at(pos);
        const int16_t realPosX = sprite.posX - 8;
        const int16_t realPosY = sprite.posY - 16;
        if(realPosY <= line && (realPosY + height) > line &&
            //Check if we are inside the screen
            realPosX >= 0 && realPosX <= 168){
                spritesIndex[spritesOnLine++] = pos;
                //As per GB documentation we only support 10 sprites per line.
                if(spritesOnLine == 10)
                    break;
        }
    }
}
uint8_t Core::renderBackgroundWindowPixel(uint16_t x, bool isWindow){
    const uint16_t line = bus->memoryMap[LCD_LY_ADDR];
    const int windowX = bus->memoryMap[LCD_WX_ADDR] - 7;
    const int windowY = bus->memoryMap[LCD_WY_ADDR];
    
    //Dont render when not needed
    if(!isBGWindowDisplayEnabled()){
        if(!isWindow)
            internalBuffer[x][line] = backgroundColorMap.at(0);
        return 0;
    }
    if(isWindow){
        //Skip if window is disabled
        if(!isWindowDisplayEnabled())
            return 0;
        //Skip id window is out of bounds
        if(windowX < 0 || windowX > 144 ||
           windowY < 0 || windowY > 166)
            return 0;

        //Nothing to render here
        if(x < windowX || line < windowY)
            return 0;
    }

    if(isWindow)
        std::cout << "Last Line: " << std::dec << wyLastLineCommited << std::endl;
    
    //I need 2 things here, my real Y position on the screen, this is calculated with line being rendered + SCY
    //which is the "adjustment". Also the reason why its 256 and not the height of the screen is because
    //er are actually moving inside the "screen buffer" which is 256 x 256 (see SCX, its % 256 as well)
    //0xFF42 + 0xFF44
    const int yAdjusted = isWindow ? static_cast<uint32_t>(line) - windowY : (static_cast<uint32_t>(line) + bus->memoryMap[LCD_SCY_ADDR])%256;
    const int yTileAdjusted = (yAdjusted / 8);
    
    //Now I calculate the difference between the tile index and the adjustment
    //For example, I know that each tile is 8 pixels, so if SCY is 14 I skip the first Tile, then 6 pixels of the picked tile
    const int backgroundLine = (yAdjusted % 8);
    if(isWindow){
        std::cout << "Updating to: " << std::dec <<  yAdjusted << std::endl;
        wyLastLine = yAdjusted;
    }

    //Lets check the tile mode first (tile = background)
    const uint16_t baseTileAddr = isTileDataSelectHigh() ? 0x8000 : 0x8800;
    const uint16_t baseBackgroundMapAddr = isWindow ? (isWindowTileMapDisplaySelectHigh() ? 0x9C00 : 0x9800) :
                                                      (isBgTileMapHigh() ? 0x9C00 : 0x9800);

    //Render background, have in mind that I could possibly do the opposite (render 32 tiles)
    //would probably be WAY cheaper
    const int xAdjusted = isWindow ? (x - windowX) : (x + bus->memoryMap[LCD_SCX_ADDR])%256;
    const int xTileAdjusted = (xAdjusted / 8);
    
    //Each tile is a byte, so we retrieve the byte that corresponds to this position
    //Here we are looking at the tilemap to extract the tile index
    const uint32_t tileMemPos = baseBackgroundMapAddr + ((yTileAdjusted * 32 /*tiles per line*/)) + xTileAdjusted;
    int tileIndex = bus->memoryMap[tileMemPos];
    // Used by dr mario :)
    if (!isTileDataSelectHigh()){
        tileIndex = *reinterpret_cast<int8_t*>(&bus->memoryMap[tileMemPos]);
        tileIndex+=128;
    }

    const uint16_t backgroundColorByte = baseTileAddr +
                                        ((tileIndex * 16) +
                                        (backgroundLine * 2)); //2 bytes per line

    const uint8_t backgroundColorIndex_0 = bus->memoryMap[backgroundColorByte];
    const uint8_t backgroundColorIndex_1 = bus->memoryMap[backgroundColorByte + 1];
    // The most significant bit is on the left, so we "invert" the reading order
    int backgroundBit = 7 - (xAdjusted % 8);
    const uint8_t backgroundPixelIndex = (backgroundColorIndex_0 >> backgroundBit) & 0x1 | 
                                            (((backgroundColorIndex_1 >> backgroundBit) & 0x1) << 1);
    internalBuffer[x][line] = backgroundColorMap.at(backgroundPixelIndex);
    
    return backgroundPixelIndex;
}

void Core::renderSpritePixel(uint16_t x, uint16_t existingPixel){
    if(!isSpriteEnabled())
        return;
    const uint16_t line = bus->memoryMap[LCD_LY_ADDR];
    uint16_t lastPos = 257;
    for(uint8_t spritePos = 0; spritePos < spritesOnLine; spritePos++) {
        const uint8_t pos = spritesIndex.at(spritePos);
        const auto& sprite = sprites.at(pos);
        // Bit7   BG and Window over OBJ (0=No, 1=BG and Window colors 1-3 over the OBJ)
        if(sprite.priority && existingPixel)
            continue;

        int16_t spriteColumn = x - (sprite.posX - 8);
        int16_t spriteLine = line - (sprite.posY - 16);
        if(spriteColumn >= 0 && spriteColumn <= 7) {
            const auto& selectedPallete = sprite.pallete ? objectPallete2 : objectPallete1;
            
            if(sprite.flipY) {
                //We are reading it from the other direction. Also if its double height we multiply
                //the height by 2, if not just by 1.
                spriteLine = (SPRITE_HEIGHT * (isSpriteDoubleHeight() + 1)) - spriteLine;
                //Properly adjust it so our range is 0-15§
                spriteLine -= 1;
            }
            if(sprite.flipX) {
                spriteColumn = (SPRITE_WIDTH - spriteColumn);
                //Properly adjust it so our range is 0-7
                spriteColumn -= 1;
            }
            //The sprite line verification (for the bit mask), should be done after the FLIP
            const uint16_t spriteTileIndex = isSpriteDoubleHeight() ? 
                                                (spriteLine < 8 ? sprite.tileIndex & 0xFE : sprite.tileIndex)
                                                : sprite.tileIndex;

            //So the sprite should be shown at this pixel, so lets retrieve the pixel
            //data (similar to the background) and then put it on the internalBuffer
            const uint16_t spriteColorByte = SPRITE_ADDR +
                            ((spriteTileIndex * 16) +
                            (spriteLine * 2)); //2 bytes per line

            const uint8_t spriteColorIndex_0 = bus->memoryMap[spriteColorByte];
            const uint8_t spriteColorIndex_1 = bus->memoryMap[spriteColorByte + 1];
            int spriteBit = 7 - spriteColumn;
            // The most significant bit is on the left, so we "invert" the reading order
            const uint8_t spritePixelIndex = (spriteColorIndex_0 >> spriteBit) & 0x1 | 
                                            (((spriteColorIndex_1 >> spriteBit) & 0x1) << 1);
            //std::cout << "SpritePixelIndex:" << spritePixelIndex << std::endl;
            if(spritePixelIndex){
                if(sprite.posX < lastPos){
                    internalBuffer[x][line] = selectedPallete.at(spritePixelIndex);
                    lastPos = sprite.posX;
                }
            }
        }
    }
}

void Core::renderLine(){
    //This is the line that I will render
    const uint16_t line = bus->memoryMap[LCD_LY_ADDR];
    //This should ALL be white
    for(int x=0; x<160; x++){
        internalBuffer[x][line] = {255, 0, 0};
        //const uint8_t backgroundPixelIndex = 0;
        uint8_t backgroundPixelIndex = renderBackgroundWindowPixel(x, false);
        //internalBuffer[x][line] = {255, 0, 0};
        if(!backgroundPixelIndex)
            backgroundPixelIndex = renderBackgroundWindowPixel(x, true);

        //Why not render the 10 sprites per line instead of crossing the data per pixel?
        //It is better to do the 10 sprites per line, the performance is wayy better, the only reason is
        //consistency....
        //As this is more of an experiment there is no concern here from performance perspective
        //This can easily be changed, but I wanted to do something different just to learn.....
        renderSpritePixel(x, backgroundPixelIndex);
    }
}

void Core::processMode0(){
    if(modeProcessed == 0 || getMode() != 0)
        return;
    
    modeProcessed = 0;
}
void Core::processMode1(){
    if(modeProcessed == 1 || getMode() != 1)
        return;
    
    modeProcessed = 1;
}

void Core::processMode2(){
    //Here I need to figure out which tiles will be used
    if(modeProcessed == 2 || getMode() != 2)
        return;

    //Load backgroundColorMap palette from BGP_ADDR
    initPalleteTable(backgroundColorMap, BGP_ADDR);
    //Init both object palletes
    initPalleteTable(objectPallete1, OBP0_ADDR);
    initPalleteTable(objectPallete2, OBP1_ADDR);

    //Load all the sprites from memory
    if(isSpriteEnabled()){
        initSprites();
        getSpritesOnLine();
    }
    
    modeProcessed = 2;
}

void Core::processMode3(){
    //Mode 3 is always enabled
    if(modeProcessed == 3 || getMode() != 3)
        return;
    //Lets copy internal buffer into screen buffer (its not exactly needed, but more as a safety measure)
    const uint8_t& line = bus->memoryMap[LCD_LY_ADDR];
    renderLine();
    //std::cout << "line: " << std::dec << static_cast<uint32_t>(line) << std::endl;
    for(int x=0; x<160; x++){
        screen[x][line]=internalBuffer[x][line];
    }
    
    modeProcessed = 3;
}

void Core::processModes(){
    processMode0();
    processMode1();
    processMode2();
    processMode3();
}

void Core::tick() {
    static uint16_t cycles = 110;
    static bool lineRendered = false;
    if(!isLCDEnabled())
        return;

    /*std::cout << "LY: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LY_ADDR]) << std::endl;
    std::cout << "LYC: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LYC_ADDR]) << std::endl;
    std::cout << "STAT: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_STATUS_REGISTER_ADDR]) << std::endl;
    std::cout << "CONTROL: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_CONTROL_REGISTER_ADDR]) << std::endl;
    std::cout << "Background: " << std::dec << static_cast<uint32_t>(isBGWindowDisplayEnabled()) << std::endl;*/
    
    //Cycle through modes, 2, 3, 0, 1.
    //OAM, DRAWING, H-BLANK, V-BLANK

    //During modes 2 and 3 CPU cannot access the OAM
    //During mode 3 CPU cannot access VRAM
    //So I can just run once, as it would be expected that at this time everything was processed
    //This is usually called "Interrupt" on some docs, but I dont have to actually trigger an interruption
    //Just do what the PPU documentation states that its done at this time
    if(cycles++ >= 456)
        cycles = 0;

    if(!isWindowDisplayEnabled() && wyLastLine > wyLastLineCommited) {
        wyLastLineCommited = wyLastLine;
        wyLastLine = 0;
    }

    uint8_t& line = bus->memoryMap[LCD_LY_ADDR];
    if(line <= 143){
        if(cycles <= 80){
            setMode(2);
            //processModes();
        } else if(cycles <= 252){
            //Mode 3 is set to the shortest amount of time 172 dots (as we do the rendering in one shot)
            //then we give the most amount of time back to the CPU to perform operations
            //While it is possilble to have accurate timming currently its probably not worth it (unless some game is really bound to this timming).
            setMode(3);
            //processModes();
        } else if(cycles < 456){
            //Mode 0 does nothing, 
            lineRendered = false;
            setMode(0);   
        }
        else {
            // Increment line if 456
            line++;
            checkLYC_LY();
            //std::cout << "LY: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LY_ADDR]) << std::endl;
            //std::cout << "LYC: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LYC_ADDR]) << std::endl;
            return;
        }
        processModes();
        //checkLYC_LY();
        
    } else {
        //if V-BLANK interrupt.. as its done only on line 144, its done only once (we will increment the line after that.)
        setMode(1);
        processModes();
        wyLastLineCommited = wyLastLine = 0;
        if(cycles == 456){
            line++;
            //std::cout << "LY: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LY_ADDR]) << std::endl;
            //std::cout << "LYC: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LYC_ADDR]) << std::endl;
            vblankServed = LYCLCServed = false;
            if(line == 152){
                line = 0;
                //std::cout << "LY: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LY_ADDR]) << std::endl;
                //std::cout << "LYC: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LYC_ADDR]) << std::endl;
            }
            checkLYC_LY();
        }   
    }
}

bool Core::isLCDEnabled() { return (bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b10000000) == 0b10000000; }
bool Core::isWindowTileMapDisplaySelectHigh() { return (bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b01000000) == 0b01000000; }
bool Core::isWindowDisplayEnabled() { return (bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00100000) == 0b00100000; }
bool Core::isTileDataSelectHigh() { return (bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00010000) == 0b00010000; }
bool Core::isBgTileMapHigh() { return (bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00001000) == 0b00001000; }
bool Core::isSpriteDoubleHeight() { return (bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00000100) == 0b00000100; }
bool Core::isSpriteEnabled() { return (bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0b00000010) == 0b00000010; }
bool Core::isBGWindowDisplayEnabled() { return (bus->memoryMap[LCD_CONTROL_REGISTER_ADDR] & 0x1) == 0x1; }

void Core::checkLYC_LY(){
    //Set coincidence bit
    if(bus->memoryMap[LCD_LY_ADDR] == bus->memoryMap[LCD_LYC_ADDR]){
        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] |= 0b0000100;
    }
    //Check for VBLANK
    //std::cout << "Stop at: " << std::dec << static_cast<uint32_t>(bus->memoryMap[LCD_LYC_ADDR]) << std::endl;
    //std::cout << "Compare at: " << std::dec << static_cast<uint32_t>(bus->memoryMap[LCD_LY_ADDR])
    //          << " and " << std::dec << static_cast<uint32_t>(bus->memoryMap[LCD_LYC_ADDR]) << std::endl;
    if(bus->memoryMap[LCD_LY_ADDR] == 144 && !vblankServed) {
        //This is managed by the main IE/IF structure not the LCDC
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::VBLANK);
        vblankServed = true;

        //If I also need to set LCDC during VBLANK
        if(bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0b00010000)
            bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);

        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] &= ~(0b00010000);
    } 
    //MIMICS STAT IRQ Blocking
    else if(
        (bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x4) == 0x4 &&
        (bus->memoryMap[LCD_STATUS_REGISTER_ADDR] & 0x40) == 0x40) {
        //std::cout << "IINTERRUPT TRIGGERED LYX=LC: " << std::hex << static_cast<uint32_t>(bus->memoryMap[LCD_LY_ADDR]) << std::endl;
        //Set Coincidence flag
        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] |= 0b0000100;
        bus->setInterruptFlag(CPU::INTERRUPTIONS_TYPE::LCDC);
        //bus->memoryMap[LCD_STATUS_REGISTER_ADDR] &= ~(0b00100000);
        //Unset the flags
        bus->memoryMap[LCD_STATUS_REGISTER_ADDR] &= ~(0b00000100);
    }  
}