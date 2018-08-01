/*
 * pseultra/tools/makerom/src/makerom.h
 * Makerom header file
 *
 * (C) pseudophpt 2018
 */

#ifndef MAKEROM_MAKEROM_H_GUARD
#define MAKEROM_MAKEROM_H_GUARD

#include <stdio.h>
#include <stdint.h>

// Sections are object files which are passed to makerom
typedef struct section_t {
    char *filename;
    char *buffer;
} section;

// Segments are the result of makerom, and are dynamically loaded
typedef struct segment_t {
    char *name;
    section *sections;
    int section_count;
    uint32_t rom_start;
    uint32_t rom_end;
} segment;

void process_specfile (FILE *file);
void calculate_rom_layout ();
void generate_linker_script(FILE *lscript);
void make_rom (char *rom_name, char *bootcode);

section create_section (char *filename);
segment create_segment (char *name);
void add_section (section sec, segment *seg);
void add_segment (segment seg); 

char *open_file (char *filename); 
void close_file (char *buffer);
    
#endif
