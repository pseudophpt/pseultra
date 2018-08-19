/*
 * pseultra/n64/os/include/os/memory/cache.h
 * Caching routines
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/memory/cache.h
 * @brief Caching header 
 * @date 18 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to caching 
 */

#ifndef OS_MEMORY_CACHE_H_GUARD
#define OS_MEMORY_CACHE_H_GUARD

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
.extern osDCacheInvalidate
#else
void osDCacheInvalidate(void *addr, int size);
#endif

#ifdef __asm__
.extern osICacheInvalidate
#else
void osICacheInvalidate(void *addr, int size);
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
