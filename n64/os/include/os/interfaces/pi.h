/*
 * pseultra/n64/os/include/os/interfaces/pi.h
 * Parallel interface header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/interfaces/pi.h
 * @brief Parallel interface header 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to the parallel interface (PI) 
 */

#ifndef OS_INTERFACES_PI_H_GUARD
#define OS_INTERFACES_PI_H_GUARD

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
.extern osPiSyncDma
#else
void osPiSyncDma (void *src, void *dest, int size);
#endif

#ifdef __asm__
.extern osPiAsyncDma
#else
void osPiAsyncDma (void *src, void *dest, int size);
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
