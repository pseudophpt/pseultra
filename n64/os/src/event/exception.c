/*
 * pseultra/n64/os/src/event/exception.c
 * Exception handler
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

extern u32 __osHandlerStart;
extern u32 __osHandlerEnd;

extern void __osUnmaskInterrupts (void);
extern void __osEnqueueEvent (OSEvent event, OSEventQueue *queue);
extern void __osCopyEventQueue (OSEventQueue *src, OSEventQueue *dest);

void __osHandleInterrupt (u32 interrupt);
void __osHandleRCPInterrupt ();

extern OSEventQueue __osMainEventQueue;
extern OSEventQueue __osInterruptEventQueue [INT_RCP_COUNT];

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

// Handle general interrupt
void __osHandleInterrupt (u32 interrupt) {
    if (interrupt & INT_CAUSE_MASK_RCP) {
        __osHandleRCPInterrupt();
    }
}

// Handle RCP interrupt 
void __osHandleRCPInterrupt () {
    int interrupt = *(u32 *)(KSEG1_ADDR(MI_INTR_REG));

    // VI interrupt
    if (interrupt & INT_RCP_CAUSE_BIT_VI) {
        // Clear interrupt line
        *(u32 *)(KSEG1_ADDR(VI_CURRENT_REG)) = 0x1;

        // Queue events on VI queue
        __osCopyEventQueue(&__osInterruptEventQueue[INT_RCP_CAUSE_VI], &__osMainEventQueue);
    }
    
    // SI interrupt
    if (interrupt & INT_RCP_CAUSE_BIT_SI) {
        // Clear interrupt line
        *(u32 *)(KSEG1_ADDR(SI_STATUS_REG)) = 0x0;

        // Queue events on SI queue
        __osCopyEventQueue(&__osInterruptEventQueue[INT_RCP_CAUSE_SI], &__osMainEventQueue);
    }

    // AI interrupt
    if (interrupt & INT_RCP_CAUSE_BIT_AI) {
        // Clear interrupt line
        *(u32 *)(KSEG1_ADDR(AI_STATUS_REG)) = 0x0;

        // Queue events on AI queue
        __osCopyEventQueue(&__osInterruptEventQueue[INT_RCP_CAUSE_AI], &__osMainEventQueue);
    }

    // PI interrupt
    if (interrupt & INT_RCP_CAUSE_BIT_PI) {
        // Clear interrupt line
        *(u32 *)(KSEG1_ADDR(PI_STATUS_REG)) = 0x2;

        // Queue events on PI queue
        __osCopyEventQueue(&__osInterruptEventQueue[INT_RCP_CAUSE_PI], &__osMainEventQueue);
    }

    // SP interrupt
    if (interrupt & INT_RCP_CAUSE_BIT_SP) {
        // Clear broke flag to remove interrupt
        *(u32 *)(KSEG1_ADDR(SP_STATUS_REG)) = 0x4;

        // Queue events on SP queue
        __osCopyEventQueue(&__osInterruptEventQueue[INT_RCP_CAUSE_SP], &__osMainEventQueue);
    }
}
