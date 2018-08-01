/*
 * pseultra/makerom/elf.c
 * ELF interface for makerom
 *
 * (C) pseudophpt 2018
 */

#include "elf.h"
#include <string.h>
#include <util.h>
#include <stdio.h>

elf32_shentry get_section (char *buffer, const char *section_name) {  
    elf32_shentry ret;
    
    // Header
    elf32_header *header = (elf32_header *)(buffer);

    // Section header offset
    uint32_t shoff = BE_TO_LE32(header->shoff);

    // Section header table
    elf32_shentry *section_header = (elf32_shentry *)(buffer + shoff);
    
    // Shared string table index
    uint16_t shstrndx = BE_TO_LE16(header->shstrndx);

    // Get shared string table
    char *shstrtab = (char *)(buffer + BE_TO_LE32(section_header[shstrndx].offset));

    // Look through each section to find one with a matching name
    for (int i = 0; i < BE_TO_LE16(header->shnum); i ++) {
         if(strcmp(BE_TO_LE32(section_header[i].name) + shstrtab, section_name) == 0) {
            return section_header[i];
        }
    }

    // No matching section
    ret.size = 0;
    return ret;
}




