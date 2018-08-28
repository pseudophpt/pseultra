/*
 * pseultra/tools/rspvfix/src/rspvfix.c
 * RSP Vector load/store fixer
 *
 * (C) pseudophpt 2018
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <elf.h>
#include <util.h>

// Amounts to shift for each load/store op
int shift_amounts [32] = {
    0, // LBV
    1, // LSV
    2, // LLV
    3, // LDV
    4, // LQV
    5, // LRV
    3, // LPV
    3, // LUV
    4, // LHV
    4, // LFV
    0, //
    4, // LTV
    0,
    0,
    0,
    0,
    0, // SBV
    1, // SSV
    2, // SLV
    3, // SDV
    4, // SQV
    5, // SRV
    3, // SPV
    3, // SUV
    4, // SHV
    4, // SFV
    3, // SWV
    4, // STV
    0,
    0,
    0,
    0
};

int main (int argc, char *argv[]) {
    FILE *file;

    if (argc != 2) {
        printf("Usage: rspvfix <binary> \n");
        return 0;
    }

    // Open binary
    file = fopen(argv[1], "r+");

    // Go to beginning
    fseek(file, 0, SEEK_SET);

    // Read header
    elf32_header header;
    fread(&header, sizeof(elf32_header), 1, file);

    // Get section headers offset
    uint32_t shoff = BE_TO_LE32(header.shoff);

    // Shared string table index
    uint16_t shstrndx = BE_TO_LE16(header.shstrndx);

    // Get shared string table 
    elf32_shentry shstrtab_entry;

    fseek(file, shoff + shstrndx * sizeof(elf32_shentry), SEEK_SET);
    fread(&shstrtab_entry, sizeof(elf32_shentry), 1, file);
    
    char *shstrtab = malloc(shoff);
    
    fseek(file, BE_TO_LE32(shstrtab_entry.offset), SEEK_SET);
    fread(shstrtab, BE_TO_LE32(shstrtab_entry.size), 1, file);

    // Get .text and .vsl sections
    fseek(file, shoff, SEEK_SET);
    
    uint32_t *text_contents = NULL;
    uint32_t *vsl_contents = NULL;

    uint32_t text_off;
    uint32_t vsl_off;

    uint32_t text_size;
    uint32_t vsl_size;

    for (int i = 0; i < BE_TO_LE16(header.shnum); i ++) {
        // Read section header entry
        elf32_shentry cur_entry;

        fread(&cur_entry, sizeof(elf32_shentry), 1, file);

        // Is it the .text or .vsl section? If so read it
        if (text_contents == NULL && strcmp(BE_TO_LE32(cur_entry.name) + shstrtab, ".text") == 0) {
            text_contents = malloc(BE_TO_LE32(cur_entry.size));
            fseek(file, BE_TO_LE32(cur_entry.offset), SEEK_SET);
            fread(text_contents, BE_TO_LE32(cur_entry.size), 1, file);
            
            text_size = BE_TO_LE32(cur_entry.size);
            text_off = BE_TO_LE32(cur_entry.offset);
            
            fseek(file, shoff, SEEK_SET);
        }
        else if (vsl_contents == NULL && strcmp(BE_TO_LE32(cur_entry.name) + shstrtab, ".vsl") == 0) {
            vsl_contents = malloc(BE_TO_LE32(cur_entry.size));
            fseek(file, BE_TO_LE32(cur_entry.offset), SEEK_SET);

            fread(vsl_contents, BE_TO_LE32(cur_entry.size), 1, file);
            
            vsl_size = cur_entry.size;
            
            vsl_size = BE_TO_LE32(cur_entry.size);
            vsl_off = BE_TO_LE32(cur_entry.offset);
            
            fseek(file, shoff, SEEK_SET);
        }
        else if (text_contents != NULL && vsl_contents != NULL) break; 
    }
        
    // Make sure there exist .text and .vsl sections
    if (text_contents == NULL || vsl_contents == NULL) {
        fprintf(stderr, "Error: .vsl or .text section not found!\n");
        return -1;
    }

    // Free shared string table
    free(shstrtab);

    uint32_t *text_ptr = text_contents;
    uint32_t *vsl_ptr = vsl_contents;

    uint32_t text_left = text_size;

    // Read through text section for vector load/store ops
    while (vsl_size > 0 && text_left > 0) {
        uint32_t inst = BE_TO_LE32(*text_ptr);

        // Check if SWC2 / LWC2 instruction
        if ((inst & 0xdc000000) == 0xc8000000) {
            printf("Resolving vector load/store at 0x%x... ", (uint32_t)(text_ptr) - (uint32_t)(text_contents));

            // Get load/store type
            uint8_t type = (inst & 0xf800) >> 11;

            // Get offset shift amount
            uint8_t offset_shift = shift_amounts[type];
           
            // Get VSL offset
            uint8_t vsl_offset = BE_TO_LE32(*vsl_ptr) >> offset_shift;

            // If it's too large, error
            if (vsl_offset > 0x7F) {
                fprintf(stderr, "Error: the offset generated by this vector load/store is too large to fit in a single instruction. Consider using a separate GPR, or moving said offset to somewhere lower in memory\n");
                return -1;
            }

            // Inform the user that this load/store op has been resolved
            printf("Resolved to 0x%x.\n", vsl_offset);

            // Write back the load/store op
            *text_ptr = LE_TO_BE32((inst & ~0x7F) | (vsl_offset & 0x7F));

            // Move VSL pointer
            vsl_ptr ++;
            vsl_size -= 4;
        }

        // Move text pointer
        text_ptr ++;
        text_left -= 4;
    }

    // If we reached the end before parsing all VSL relocations
    if (vsl_size > 0) {
        fprintf(stderr, "Error: Reached end of .text section before reading all .vsl entries!\n");
        return -1;
    }

    // Write back
    fseek(file, text_off, SEEK_SET);
    fwrite(text_contents, 1, text_size, file);

    // Inform the user that all loads/stores have been fixed
    printf("All vector loads/stores fixed.\n");

    // Free contents of vsl and text sctions
    free(text_contents);
    free(vsl_contents);

    // Close binary
    fclose(file);
}
