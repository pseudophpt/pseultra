/*
 * pseultra/n64/os/src/memory/memcpy.c
 * Memory copying function
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/memory/memcpy.c
 * @brief Memory copying routines
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines to copy memory from source to destination.
 */

#include <os_priv.h>

/**
 * @brief Copy memory from a source to destination
 * @param[out] dest Pointer to the start of the destination region
 * @param[in] src Pointer to the start of the source region
 * @param[in] size Size in bytes of region to copy
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function copies the region whose size is defined in the size parameter from the region at src to dest.
 */
void
osCopyMemory
(void *dest, void *src, int size) {
    while (size > 0) {
        // Must do byte write
        if ((((u32)src % 2) == 1) || (((u32)dest % 2) == 1) || ((size % 2) == 1)) {
            *(u8 *)dest = *(u8 *)src;
            src = (void *)((u8 *)src + 1);
            dest = (void *)((u8 *)dest + 1);
            size --;
            continue;
        }
        // Must do hword write
        else if ((((u32)src % 4) == 2) || ((((u32)dest % 4) == 2) || (size % 4) == 2)) {
            *(u16 *)dest = *(u16 *)src;
            src = (void *)((u16 *)src + 1);
            dest = (void *)((u16 *)dest + 1);
            size -= 2;
            continue;
        }
        // We can do a word write
        else {
            *(u32 *)dest = *(u32 *)src;
            src = (void *)((u32 *)src + 1);
            dest = (void *)((u32 *)dest + 1);
            size -= 4;
            continue;
        }
    }    
}

/**
 * @brief Zero a memory region
 * @param[out] dest Pointer to start of the region
 * @param[in] size Size in bytes of region to zero
 * @date 3 Aug 2018
 * @author pseudophpt
 *
 * This function zeroes a memory region, typically one that will be used as BSS.
 */
void
osZeroMemory
(void *dest, int size) {
    while (size > 0) {
        // Must do byte write
        if ((((u32)dest % 2) == 1) || ((size % 2) == 1)) {
            *(u8 *)dest = 0;
            dest = (void *)((u8 *)dest + 1);
            size --;
            continue;
        }
        // Must do hword write
        else if ((((u32)dest % 4) == 2) || ((size % 4) == 2)) {
            *(u16 *)dest = 0;
            dest = (void *)((u16 *)dest + 1);
            size -= 2;
            continue;
        }
        // We can do a word write
        else {
            *(u32 *)dest = 0;
            dest = (void *)((u32 *)dest + 1);
            size -= 4;
            continue;
        }
    }    

}
