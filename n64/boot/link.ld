/*
 * pseultra/boot/link.ld
 * Bootcode linker script
 * 
 * (C) pseudophpt 2018
 */

INPUT(
    "src/boot.o"
)

OUTPUT(
    "src/boot.elf"
)

SECTIONS {
    .text 0xA4000000 : {
        src/boot.o (.text)
        src/boot.o (.data)
    }

    .bss : {
        src/boot.o (.bss)
        src/boot.o (COMMON)
    }
}
