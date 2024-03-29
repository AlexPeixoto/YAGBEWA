# YAGBEWA (Yet another gameboy emulator without audio)

This is a non 100% accurate gameboy emulator (even tho it still attempts to have clock cycles mapped, it lacks it for special cases).
This was implemented only as a fun side-project and has not the goal to be more than a reference.
The code was heavily commented when it comes to odd behaviors (Like unhalting the CPU if IF register is set but IE is not).

The code does pass all the blargg test roms and all the DMG-ACID2 checks.

As for game testing I only played with Tetris and Started the 1st round of dr mario (as stated this was more of an experient, its possible that other )

![It works](https://github.com/AlexPeixoto/GBEmulator/blob/master/ItWorks.png)

# Missing features
 - Lack of Memory Bank controller (only 32kb rom can be loaded)
 - Lack of APU
 - Doesn't support CGB Games.

# Knows issues
 - Due to the improper clock mapping the timer is not 100% accurate as well.

# Some problems faced (in case someone might face issues during development)
 - During the bloargg tests I noticed that most of the problems were incorrectly setting or just missing the flags.
 - At the very beginning I noticed that sometimes I might not be moving the PC twice when reading a 16 bit data 
 - Another problem was that I was doing the proper jump, but after that the main routine would increment PC.
 - I used an union in the beginning to map 2 uint8_t as a uint16_t, well, endianness came back to hunt me.
 - The most complex part to fix was by far the PPU, I noticed things like interrupts being triggered twice, which broke the DMG-ACID2 tests.
 - Triggering LCDC for mode 3 by mistake.
 - Was not incrementing the DIV properly (Was having the same piece all the times on Tetris).
 - Forgot to reset to mode 0 and LY = 0 when disabling the LCD

# References used:

- https://github.com/gbdev/awesome-gbdev
- https://gekkio.fi/files/gb-docs/gbctr.pdf
- https://www.huderlem.com/demos/gameboy2bpp.html
- https://hacktix.github.io/GBEDG/ppu/#lcd-control-register--lcdc----ff40-
- http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf
- http://gbdev.gg8.se/wiki/articles/Memory_Bank_Controllers#0000-3FFF_-_ROM_Bank_00_.28Read_Only.29
- https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
- https://gbdev.io/pandocs/
