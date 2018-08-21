/*
 * pseultra/n64/os/include/os/boot/boot.h
 * Boot process header 
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/boot/boot.h
 * @brief Boot process headers
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs and constants related to the boot process
 */

#ifndef OS_BOOT_DEBUG_H_GUARD
#define OS_BOOT_DEBUG_H_GUARD

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

/*
 * Public variables
 */

#ifdef __asm__
.extern osDebugFont
#else
extern u8 osDebugFont [];
#endif

#ifdef __asm__
.extern osDebugRegNames
#else
extern char *osDebugRegNames [];
#endif

#ifdef __os_internal__

/*
 * Internal functions
 */

#ifdef __asm__
.extern __osDebugInit
#else
void __osDebugInit ();
#endif

#ifdef __asm__
.extern __osDebugWriteChar
#else
void __osDebugWriteChar (int x, int y, u8 ch);
#endif

#ifdef __asm__
.extern __osDebugPrint
#else
void __osDebugPrint (int x, int y, char *str);
#endif

#ifdef __asm__
.extern __osDebugDumpRegisters
#else
void __osDebugDumpRegisters ();
#endif

#ifdef __asm__
.extern __osDebugFormatHex
#else
void __osDebugFormatHex (u32 value, char *str);
#endif

#ifdef __asm__
.extern __osError
#else
void __osError (char *error_msg);
#endif

/*
 * Internal variables
 */

#endif

#endif
