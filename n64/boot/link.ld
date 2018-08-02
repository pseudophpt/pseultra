/*
 * pseultra/n64/boot/link.ld
 * Bootcode linker script
 * 
 * (C) pseudophpt 2018
 */

SECTIONS {
    .text 0xA4000000 : {
        * (.text)
        * (.data)
    }

    .bss : {
        * (.bss)
        * (COMMON)
    }
}
