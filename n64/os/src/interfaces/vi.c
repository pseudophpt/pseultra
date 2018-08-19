/*
 * pseultra/n64/os/src/interfaces/vi.c
 * Video interface
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/interfaces/vi.c
 * @brief Video interface
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines for the video interface (VI)
 */

#include <os_priv.h>

/** @internal @brief Current buffer used to draw to the screen by the VI */
void *__osViCurrentBuffer;
/** @internal @brief Buffer to be drawn to the screen by the VI on next interrupt */
void *__osViSwapBuffer;

/**
 * @internal
 *
 * @brief Update buffer on VI interrupt
 * @date 7 Aug 2018
 * @author pseudophpt
 *
 * This function updates the origin buffer on a VI interrupt to the value set by osViSwapBuffer 
 *
 * @see osViSwapBuffer
 */
void 
__osViUpdateBuffer
(void) {
    __osViCurrentBuffer = __osViSwapBuffer;
    *(u32 *)N64_KSEG1_ADDR(N64_VI_ORIGIN_REG) = (u32)__osViCurrentBuffer;
}

/**
 * @brief Gets swapped VI origin buffer 
 * @date 7 Aug 2018
 * @author pseudophpt
 * @return Pointer to the swapped VI origin buffer
 *
 * This function returns a pointer to the swapped VI origin buffer that the console is using to draw to the screen
 * @see osViSwapBuffer
 */
void *
osViGetSwapBuffer
(void) {
    return __osViSwapBuffer;
}

/**
 * @brief Gets current VI origin buffer 
 * @date 7 Aug 2018
 * @author pseudophpt
 * @return Pointer to the VI origin buffer
 *
 * This function returns a pointer to the current VI origin buffer that the console is using to draw to the screen
 *
 */
void *
osViGetCurrentBuffer
(void) {
    return __osViCurrentBuffer;
}

/**
 * @brief Swaps buffer to be read from on next VI
 * @date 7 Aug 2018
 * @author pseudophpt
 * @param[in] buffer Pointer to buffer to read from
 *
 * This function sets the buffer which the n64 will read from when drawing the next frame
 */
void 
osViSwapBuffer
(void *buffer) {
    __osViSwapBuffer = buffer;
}

/**
 * @brief Initializes VI registers
 * @date 10 Aug 2018
 * @author pseudophpt
 * @param[in] mode VI mode to set 
 *
 * This function initializes VI registers using the options passed via the mode argument 
 */
void 
osViInit
(OSViMode mode) {
    // Disable interrupts
    __osDisableInterrupts();
    
    // Get pixel and resolutions values from mode parameter
    u32 pixel_size, resolution;
    
    if ((mode & OS_VI_OPTION_PIXEL) == OS_VI_OPTION_PIXEL_5553) {
        pixel_size = N64_VI_STATUS_REG_PIXEL_SIZE_5553;
    }
    else if ((mode & OS_VI_OPTION_PIXEL) == OS_VI_OPTION_PIXEL_8888) {
        pixel_size = N64_VI_STATUS_REG_PIXEL_SIZE_8888;
    }
    
    if ((mode & OS_VI_OPTION_RES) == OS_VI_OPTION_RES_LOW) {
        // 320 width
        resolution = 0x140;
    }
    else if ((mode & OS_VI_OPTION_RES) == OS_VI_OPTION_RES_HIGH) {
        // 640 width
        resolution = 0x280;
    }
    
    // Set status register
    *(u32 *)N64_KSEG1_ADDR(N64_VI_STATUS_REG) = 
        pixel_size | 
        N64_VI_STATUS_REG_AA_MODE_REPLICATE | 
        /**N64_VI_STATUS_REG_AA_MODE_AA_RESAMP_FETCH_ALWAYS | 
        N64_VI_STATUS_REG_DITHER_FILTER_ENABLE | 
        N64_VI_STATUS_REG_DIVOT_ENABLE | 
        N64_VI_STATUS_REG_DITHER_FILTER_ENABLE | 
        N64_VI_STATUS_REG_GAMMA_DITHER_ENABLE | */
        N64_VI_STATUS_REG_PIXEL_ADVANCE_FMT(0x3);

    // Set resolution
    *(u32 *)N64_KSEG1_ADDR(N64_VI_WIDTH_REG) = resolution;

    // Interrupt at line 2
    *(u32 *)N64_KSEG1_ADDR(N64_VI_INTR_REG) = 0x2; 

     // Initalize other VI registers (Don't ask me what they mean lmao)
    *(u32 *)N64_KSEG1_ADDR(N64_VI_BURST_REG) = 0x3E52239;
    *(u32 *)N64_KSEG1_ADDR(N64_VI_V_SYNC_REG) = 0x20D;
    *(u32 *)N64_KSEG1_ADDR(N64_VI_H_SYNC_REG) = 0xC15;
    *(u32 *)N64_KSEG1_ADDR(N64_VI_LEAP_REG) = 0xC150C15;
    *(u32 *)N64_KSEG1_ADDR(N64_VI_H_START_REG) = 0x6C02EC;
    *(u32 *)N64_KSEG1_ADDR(N64_VI_V_START_REG) = 0x2501FF;
    *(u32 *)N64_KSEG1_ADDR(N64_VI_V_BURST_REG) = 0xE0204;
    
    // Scale registers
    *(u32 *)N64_KSEG1_ADDR(N64_VI_X_SCALE_REG) = 0x200; // Scale by 1
    *(u32 *)N64_KSEG1_ADDR(N64_VI_Y_SCALE_REG) = 0x400; // Scale by 1/2

    // Re-enable interrupts
    __osEnableInterrupts();
}
