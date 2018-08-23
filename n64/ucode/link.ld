/*
 * pseultra/n64/ucode/link.ld
 * Microcode linker script
 * 
 * (C) pseudophpt 2018
 */

SECTIONS {
    .text 0x00000000 : {
        * (.text)
    }

    .data 0x00000000 : {
        * (.data)
    }
    
    .bss : {
        * (.bss)
        * (COMMON)
    }

    /DISCARD/ : {
        * (.MIPS.*)
        * (.reginfo)
        * (.gnu.*)
    }
}
