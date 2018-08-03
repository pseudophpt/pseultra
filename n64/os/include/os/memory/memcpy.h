/*
 * pseultra/n64/os/include/os/memory/memcpy.h
 * Memory copying routine
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/memory/memcpy.h
 * @brief Memory copying header 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to memory copying 
 */

#ifndef OS_MEMORY_MEMCPY_H_GUARD
#define OS_MEMORY_MEMCPY_H_GUARD

/*
 * Macros
 */

/*
 * Structs
 */

#ifndef __asm__

#endif

/*
 * Public functions
 */

#ifdef __asm__
.extern osCopyMemory
#else
void osCopyMemory (void *dest, void *src, int size);
#endif

#ifdef __asm__
.extern osZeroMemory
#else
void osZeroMemory (void *dest, int size);
#endif

/*
 * Public variables
 */

#ifdef __os_internal__

/*
 * Internal functions
 */

/*
 * Internal variables
 */

#endif

#endif
