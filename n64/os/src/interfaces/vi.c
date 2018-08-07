/*
 * pseultra/n64/os/src/interfaces/vi.c
 * Video interface
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/interfaces/vi.c
 * @brief Parallel interface
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines for the video interface (VI)
 */

#include <os_priv.h>

void *__osViCurrentBuffer;
void *__osViSwapBuffer;

/**
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
