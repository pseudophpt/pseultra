/*
 * pseultra/n64/os/include/os/interfaces/vi.h
 * Video interface header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/interfaces/vi.h
 * @brief Video interface header 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to the video interface (VI) 
 */

#ifndef OS_INTERFACES_VI_H_GUARD
#define OS_INTERFACES_VI_H_GUARD

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
.extern osViGetSwapBuffer
#else
void *osViGetSwapBuffer (void);
#endif

#ifdef __asm__
.extern osViGetCurrentBuffer
#else
void *osViGetCurrentBuffer (void);
#endif

#ifdef __asm__
.extern osViSwapBuffer
#else
void osViSwapBuffer (void *buffer);
#endif

/*
 * Public variables
 */

#ifdef __os_internal__

/*
 * Internal functions
 */

#ifdef __asm__
.extern __osViUpdateBuffer
#else
void __osViUpdateBuffer (void);
#endif

/*
 * Internal variables
 */

#ifdef __asm__
.extern __osViSwapBuffer
#else
extern void *__osViSwapBuffer;
#endif

#ifdef __asm__
.extern __osViCurrentBuffer
#else
extern void *__osViCurrentBuffer;
#endif

#endif

#endif
