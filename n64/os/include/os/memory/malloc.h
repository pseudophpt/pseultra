/*
 * pseultra/n64/os/include/os/memory/malloc.h
 * Memory allocation
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/memory/malloc.h
 * @brief Memory allocation header 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to memory allocation 
 */

#ifndef OS_MEMORY_MALLOC_H_GUARD
#define OS_MEMORY_MALLOC_H_GUARD

/*
 * Structs
 */

#ifndef __asm__

/** @brief Struct describing one contiguous block of memory on a heap*/
typedef struct OSHeapLink_t {
    /** @brief Pointer to previous node */
	struct OSHeapLink_t *prev;
    /** @brief Pointer to next node */
	struct OSHeapLink_t *next;
    /** @brief Flags about the memory block */
	u8 flags;
    /** @brief Size of the memory block */
	u32 size;
} OSHeapLink;

#endif

/*
 * Public functions
 */

#ifdef __asm__
.extern osInitHeap
#else
void osInitHeap (void *heap, int heap_size);
#endif

#ifdef __asm__
.extern osMalloc
#else
void *osMalloc (int size, void *heap);
#endif

#ifdef __asm__
.extern osFree
#else
void osFree (void *region);
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
