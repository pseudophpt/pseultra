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
    .text 0xA4000000 : {
        boot.o (.text)
        boot.o (.data)
    }

    .bss : {
        boot.o (.bss)
        boot.o (COMMON)
    }
}
