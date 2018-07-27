/*
 * pseultra/os/except/handler.c
 * Exception handler
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

extern u32 __osHandlerStart;
extern u32 __osHandlerEnd;

extern void __osUnmaskInterrupts (void);

void __osInitExceptions (void) {
    // Install exception handler for the three non-NMI exceptions
    osCopyMemory((void *)EXC_VEC_TLB_MISS, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
    osCopyMemory((void *)EXC_VEC_XTLB_MISS, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
    osCopyMemory((void *)EXC_VEC_GENERAL, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
    __osUnmaskInterrupts();
}

u32 osGetIntMask (void) {
    return *(u32 *)(KSEG1_ADDR(MI_INTR_MASK_REG));
}

void osSetIntMask (u32 mask) {
    *(u32 *)(KSEG1_ADDR(MI_INTR_MASK_REG)) = mask;
}
