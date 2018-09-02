/*
 * pseultra/tools/makerom/src/makerom_elf.h
 * ELF header
 *
 * (C) pseudophpt 2018
 */

#ifndef MAKEROM_ELF_H_GUARD
#define MAKEROM_ELF_H_GUARD

#include <elf.h>

elf32_shentry get_section (char *buffer, const char *section_name); 

#endif
