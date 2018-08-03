/*
 * pseultra/n64/os/src/event/exception.c
 * Exception handler
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/event/exception.c
 * @brief Exception handling routines
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines for the handling of exceptions.
 */

#include <os_priv.h>

/**
 * @internal
 * @brief Initializes exception handlers
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function copies the general event handler into the three exception vectors for non-NMI exceptions, which are: TLB miss, XTLB miss, and General Exception. Additionally, it unmasks all interrupts.
 */
void __osInitExceptions (void) {
    // Install exception handler for the three non-NMI exceptions
    osCopyMemory((void *)EXC_VEC_TLB_MISS, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
    osCopyMemory((void *)EXC_VEC_XTLB_MISS, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
    osCopyMemory((void *)EXC_VEC_GENERAL, (void *)&__osHandlerStart, (u32)&__osHandlerEnd - (u32)&__osHandlerStart);
    __osUnmaskInterrupts();
}

/**
 * @brief Returns RCP interrupt mask
 * @return RCP interrupt mask
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function returns the interrupt mask associated with masking the 6 RCP interrupts.
 */
u32 osGetIntMask (void) {
    return *(u32 *)(KSEG1_ADDR(MI_INTR_MASK_REG));
}

/**
 * @brief Sets RCP interrupt mask
 * @param[in] mask RCP interrupt mask
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function sets the interrupt mask associated with masking the 6 RCP interrupts.
 */
void osSetIntMask (u32 mask) {
    *(u32 *)(KSEG1_ADDR(MI_INTR_MASK_REG)) = mask;
}

/**
 * @internal
 * @brief Handles a general MIPS interrupt 
 * @param[in] interrupt Coprocessor 0 Cause register at the time of interrupt, masked for only the interrupt bit.
 * @date 1 Aug 2018
 * @author pseudophpt
 * @todo Add handling for timer and the 2 software interrupts
 *
 * This function handles a general interrupt given the Coprocessor 0 Cause register at the time of interrupt, masked for only the interrupt bit. It should only be called within an exception handler where the cause has been determined to be an interrupt
 */
void __osHandleInterrupt (u32 interrupt) {
    if (interrupt & INT_CAUSE_MASK_RCP) {
        __osHandleRCPInterrupt();
    }
}

/**
 * @internal
 * @brief Handles an RCP interrupt 
 * @date 1 Aug 2018
 * @author pseudophpt
 * @todo Add parameter for interrupt register
 *
 * This function handles an RCP interrupt by copying the corresponding event queue to the main event queue, and disabling the interrupt line for each cause. 
 */
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
