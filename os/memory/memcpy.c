/*
 * pseultra/os/memory/memcpy.c
 * Memory copying function
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

void osCopyMemory (void *dest, void *src, int size) {
    while (size > 0) {
        // Must do byte write
        if ((((u32)src & 2) == 1) || ((size & 2) == 1)) {
            *(u8 *)dest = *(u8 *)src;
            src = (void *)((u8 *)src + 1);
            size --;
            continue;
        }
        // Must do hword write
        else if ((((u32)src & 4) == 2) || ((size & 4) == 2)) {
            *(u16 *)dest = *(u16 *)src;
            src = (void *)((u16 *)src + 1);
            size -= 2;
            continue;
        }
        // We can do a word write
        else {
            *(u32 *)dest = *(u32 *)src;
            src = (void *)((u32 *)src + 1);
            size -= 4;
            continue;
        }
    }    
}
