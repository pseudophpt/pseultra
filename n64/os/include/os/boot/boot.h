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

#ifndef OS_BOOT_BOOT_H_GUARD
#define OS_BOOT_BOOT_H_GUARD

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

#ifdef __os_internal__

/*
 * Internal functions
 */

#ifdef __asm__
.extern __osBoot
#else
void __osBoot ();
#endif

/*
 * Internal variables
 */

#ifdef __asm__
.extern __osBootStack
#else
extern u8 __osBootStack [];
#endif

#endif

#endif
