/*
 * pseultra/headers/elf.h
 * ELF header
 *
 * (C) pseudophpt 2018
 */

#ifndef MAKEROM_ELF_H_GUARD
#define MAKEROM_ELF_H_GUARD

#include <stdint.h>

typedef struct __attribute__((__packed__)) elf32_header_t {
    uint32_t magic; // Magic number
    uint8_t class; // 64- or 32-bit 
    uint8_t data; // Endianness
    uint8_t version; // ELF Version
    uint8_t osabi; // OS ABI
    uint8_t abiversion; // ABI version
    uint32_t pad1; // Unused
    uint16_t pad2; // Unused
    uint8_t pad3; // Unused
    uint16_t type; // Type of ELF file
    uint16_t machine; // ISA
    uint32_t version2; // Version
    uint32_t entry; // Entry point
    uint32_t phoff; // Program headers offset
    uint32_t shoff; // Secton headers offset
    uint32_t flags; // Architecture dependent flags
    uint16_t ehsize; // Header size
    uint16_t phentsize; // Program header entry size
    uint16_t phnum; // Number of program header entries
    uint16_t shentsize; // Section header entry size
    uint16_t shnum; // Number of section header entries
    uint16_t shstrndx; // Index in section header to string table entry
} elf32_header;

typedef struct __attribute__((__packed__)) elf32_shentry_t { 
    uint32_t name; // Index in .shstrtab
    uint32_t type; // Type of entry
    uint32_t flags; // Flags
    uint32_t addr; // VMA Address
    uint32_t offset; // Offset 
    uint32_t size; // Section size
    uint32_t link; // Index of linked section
    uint32_t info; // Extra info
    uint32_t addralign; // Address alignment in bytes
    uint32_t entsize; // Entry size for those with fixed entries
} elf32_shentry;

elf32_shentry get_section (char *buffer, const char *section_name); 

#endif
