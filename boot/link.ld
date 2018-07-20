/*
 * pseultra/boot/link.ld
 * Bootcode linker script
 * 
 * (C) pseudophpt 2018
 */

INPUT(
    "boot.o"
)

OUTPUT(
    "boot.elf"
)

SECTIONS {
    . = 0xA4000000; /* SP_DMEM in KSEG1 */    

    .text : {
        boot.o (.text)
    }

    .data : {
        boot.o (.data)
    }

    .bss : {
        boot.o (.bss)
        boot.o (COMMON)
    }
}
