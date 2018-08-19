/*
 * pseultra/n64/os/src/boot/debug.c
 * OS debug code
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/boot/debug.c
 * @brief Debug routines 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines for debugging
 */

#include <os_priv.h>

/* Font data */
#include "font.h"

/**
 * @internal
 * @brief Initialize debugging mode
 * @date 19 Aug 2018
 * @author pseudophpt
 *
 * This function should be called when an assertion fails or an exception occurs. It initializes the VI for printing out debug information
 *
 */
void 
__osDebugInit
() {
    // Initialize VI mode for 5/5/5/3 320x240 
    osViInit(OS_VI_MODE(8888, LOW));

    // Set and swap VI buffer
    osViSwapBuffer((void *)OS_DEBUG_BUFFER);
    __osViUpdateBuffer();
}

/**
 * @internal
 * @brief Write character to debug screen 
 * @date 19 Aug 2018
 * @author pseudophpt
 *
 * @param x X position of character
 * @param y Y position of character
 * @param ch Character to draw
 *
 * This function draws one character to the debug screen
 *
 */
void
__osDebugWriteChar
(int x, int y, u8 ch) {
    // Get offset in font map
    int offset; 

    // If character is a letter
    if (ch >= 'A' && ch <= 'z') {
        offset = (ch - 'A') % ('A' - 'a'); // Case neutralize 
    }
    // If character is a number
    else if (ch >= '0' && ch <= '9') {
        offset = 26 + (ch - '0'); // Get number offset
    }
    // No character found, return
    else return;

    // Write character to frame buffer
    for (int row = 0; row < 5; row ++) {
        // Get bitmap for this row
        u8 row_pixels = osDebugFont[(offset * 5) + row];

        for (int col = 0; col < 5; col ++) {
            *(u32 *)N64_KSEG1_ADDR(OS_DEBUG_BUFFER + OS_DEBUG_XY_PIXEL_TO_OFFSET(
                        OS_DEBUG_CHAR_TO_X_PIXEL(x) + col, // X pixel
                        OS_DEBUG_CHAR_TO_Y_PIXEL(y) + row // Y pixel
                        ))
                = (row_pixels & (1 << (7 - col))) ? 0xFFFFFFFFF : 0x000000FF;
        }
    }
}

void
__osDebugPrint
(int x, int y, char *str) {
    // Iterate through characters
    while (*str != '\0') {
        if (*str == '\n') {
            x = 0;
            y ++;
        }
        else {
            __osDebugWriteChar(x, y, *str);
            x ++;
        }
        str ++;
    }
}
