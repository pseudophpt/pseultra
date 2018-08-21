/*
 * pseultra/n64/ucode/link.ld
 * Microcode linker script
 * 
 * (C) pseudophpt 2018
 */

SECTIONS {
    .text 0x00000000 : {
        * (.text)
        * (.data)
    }

    .bss 0x00000000 : {
        * (.bss)
        * (COMMON)
    }

    /DISCARD/ : {
        * (.MIPS.*)
    }
}
