#pragma once

#include <cstdint>
#include <CartridgeType.h>

namespace Memory::Cartridge{
    enum class GB_TYPE{
        NONE,
        CGB,
        OGB //Its either gameboy color or "another gameboy"
    };
    enum class GB_FUNCTIONS{ //tells if the rom has super gameboy features
        NONE,
        GB,
        SGB
    };
    enum class GB_DESTINATION{
        JAPANESE,
        NONJAPANESE
    };

    class Header{
        private:
            //START OF EACH SECTION
            const static uint16_t TITLE_START = 0x134;
            const static uint16_t TYPE_START = 0x143;
            const static uint16_t FUNCTIONS_START = 0x146;
            const static uint16_t CARTRIDGE_TYPE_START = 0x147;
            const static uint16_t ROM_BANK_COUNT_START = 0x148;
            const static uint16_t RAM_BANK_COUNT_START = 0x149;
            const static uint16_t DESTINATION_CODE_START = 0x14A;
			const static uint16_t TOTAL_BYTES = DESTINATION_CODE_START - TITLE_START;
            //END
                
            unsigned char* ptr;
                
            char romName[16];
            //16KB bank size
            uint8_t romBankCount=0;
            uint8_t ramBankCount=0;
            GB_DESTINATION destinationCode = GB_DESTINATION::JAPANESE;
            GB_FUNCTIONS function = GB_FUNCTIONS::NONE;
            GB_TYPE type = GB_TYPE::NONE;

            CartridgeType cartridgeType;


            void processHeader();
            void setRomName();
            void setType();
            void setFunctions();
            void setCatridgeType();
            void setRomBankCount();
            void setRamBankCount();
            void setDestination();
        public:
			Header() {};
			Header(unsigned char* ptr) : loadData(ptr) {};
                
			void loadData(unsigned char* ptr) {
				this->ptr = ptr;
				romName[0] = '\0';
				processHeader();
			}

            const char* getRomName();
            uint8_t getRomBankCount();
            uint8_t getRamBankCount();
            GB_DESTINATION getDestination();
            GB_FUNCTIONS getFunction();
            GB_TYPE getType();
            CartridgeType& getCartridgeType();

			constexpr static uint16_t getHeaderStartAddress() { return TITLE_START; }
			constexpr static uint16_t getTotalHeaderSize() { return TOTAL_BYTES; }

        
    };
}