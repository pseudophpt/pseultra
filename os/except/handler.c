/*
 * pseultra/os/except/handler.c
 * Exception handler
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

extern u32 __osHandlerStart;
extern u32 __osHandlerEnd;

void __osInitExceptions (void) {
    // Install exception handler for the three non-NMI exceptions
    int x = __osHandlerStart;

    osCopyMemory((void *)INT_VEC_TLB_MISS, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
    osCopyMemory((void *)INT_VEC_XTLB_MISS, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
    osCopyMemory((void *)INT_VEC_GENERAL, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
}
