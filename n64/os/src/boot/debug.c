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

/* Register names */
#include "reg.h"

/**
 * @internal
 * @brief Initialize debugging mode
 * @date 19 Aug 2018
 * @author pseudophpt
 *
 * This function should be called when an assertion fails or an exception occurs. It initializes the VI for printing out debug information.
 *
 * @note Draw debug info to the screen before calling this function, so the VI doesn't end up reading something that being written to
 */
void 
__osDebugInit
() {
    // Poll VI register for vblank
    while (*(u32 *)N64_KSEG1_ADDR(N64_VI_CURRENT_REG) != 0);

    // Initialize VI mode for 8/8/8/8 320x240 
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
    for (int row = 0; row < OS_DEBUG_CHAR_WIDTH; row ++) {
        // Get bitmap for this row
        u8 row_pixels = osDebugFont[(offset * 5) + row];
        // Last row blank
        if (row == OS_DEBUG_CHAR_WIDTH - 1) row_pixels = 0;

        for (int col = 0; col < OS_DEBUG_CHAR_WIDTH; col ++) {
            *(u32 *)N64_KSEG1_ADDR(OS_DEBUG_BUFFER + OS_DEBUG_XY_PIXEL_TO_OFFSET(
                        OS_DEBUG_CHAR_TO_X_PIXEL(x) + col, // X pixel
                        OS_DEBUG_CHAR_TO_Y_PIXEL(y) + row // Y pixel
                        ))
                = (row_pixels & (1 << (7 - col))) ? 0xFFFFFFFFF : 0x000000FF;
        }
    }
}

/**
 * @internal
 * @brief Print string to debug screen 
 * @date 19 Aug 2018
 * @author pseudophpt
 *
 * @param x X position of string
 * @param y Y position of string
 * @param str String to print
 *
 * This function draws a null-terminated string to the debug screen
 *
 */
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

/**
 * @internal
 * @brief Dump register values to debug screen
 * @date 19 Aug 2018
 * @author pseudophpt
 *
 * This function draws the values of the 32 vr4300 GPRs to the screen
 *
 */
void
__osDebugDumpRegisters
() {
    for (int x = 0; x < 3; x ++) {
        for (int y = 0; y < 11; y ++) {
            // Register number
            int reg = (x * 11) + y;

            // If not a register
            if (reg == 32) break;

            // Draw register names 
            __osDebugPrint(x * 12, y + 4, osDebugRegNames[reg]); 
            
            // Format register value as hex string
            char value_string [9];

            // Null terminate
            value_string[8] = 0;

            // Get register value
            u32 value = __osExceptionRegSave[reg];
            
            for (int digit = 0; digit < 8; digit ++) {
                // Get digit value
                u8 digit_value = (value & (0xF << (4 * (7 - digit)))) >> (4 * (7 - digit));

                // Convert to character
                // Digit
                if (digit_value < 0xa) {
                    value_string[digit] = '0' + digit_value;
                }
                // Letter
                else value_string[digit] = 'a' + (digit_value - 0xa);
            }

            // Print value
            __osDebugPrint(x * 12 + 3, y + 4, value_string); 
        }
    }
}

/**
 * @internal
 * @brief Enter error state 
 * @date 19 Aug 2018
 * @author pseudophpt
 *
 * @param error_msg Message to display as cause
 *
 * This function should be called on exception or when an assertion fails. It displays the cause passed via error_msg, the value of the 32 GPRs, and then enters an infinite loop which cannot be exited.
 *
 */

void
__osError
(char *error_msg) {
    // Disable interrupts
    __osDisableInterrupts();
    
    // Write message
    __osDebugPrint(0, 0, error_msg);

    // Dump registers
    __osDebugDumpRegisters();

    // Initialize debug
    __osDebugInit();
    
    // Spin forever
    while(1);
}
