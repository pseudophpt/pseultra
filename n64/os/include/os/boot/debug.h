/*
 * pseultra/n64/os/include/os/boot/boot.h
 * Boot process header 
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/boot/boot.h
 * @brief Boot process headers
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs and constants related to the boot process
 */

#ifndef OS_BOOT_DEBUG_H_GUARD
#define OS_BOOT_DEBUG_H_GUARD

/*
 * Macros
 */

/** @brief Default location for debug buffer */
#define OS_DEBUG_BUFFER 0x100000
/** @brief Debug buffer width */
#define OS_DEBUG_BUFFER_WIDTH 320
/** @brief Debug buffer height */
#define OS_DEBUG_BUFFER_HEIGHT 240
/** @brief Debug buffer X start  pixels */
#define OS_DEBUG_BUFFER_X_START 40
/** @brief Debug buffer X end in pixels*/
#define OS_DEBUG_BUFFER_X_END 280
/** @brief Debug buffer Y start in pixels */
#define OS_DEBUG_BUFFER_Y_START 60
/** @brief Debug buffer Y end in pixels */
#define OS_DEBUG_BUFFER_Y_END 180
/** @brief Debug buffer character width in pixels */
#define OS_DEBUG_CHAR_WIDTH 6
/** @brief Debug font character count */
#define OS_DEBUG_CHAR_COUNT 36
/** @brief Convert character block to debug buffer x pixel */
#define OS_DEBUG_CHAR_TO_X_PIXEL(x) (((x) * OS_DEBUG_CHAR_WIDTH) + OS_DEBUG_BUFFER_X_START)
/** @brief Convert character block to debug buffer y pixel */
#define OS_DEBUG_CHAR_TO_Y_PIXEL(y) (((y) * OS_DEBUG_CHAR_WIDTH) + OS_DEBUG_BUFFER_Y_START)
/** @brief Convert x and y pixel to offset */
#define OS_DEBUG_XY_PIXEL_TO_OFFSET(x,y) (((x) * 0x4) + ((y) * 0x4 * OS_DEBUG_BUFFER_WIDTH))

/*
 * Structs
 */

#ifndef __asm__

#endif

/*
 * Public functions
 */

/*
 * Public variables
 */

#ifdef __asm__
.extern osDebugFont
#else
extern u8 osDebugFont [];
#endif

#ifdef __asm__
.extern osDebugRegNames
#else
extern char *osDebugRegNames [];
#endif

#ifdef __os_internal__

/*
 * Internal functions
 */

#ifdef __asm__
.extern __osDebugInit
#else
void __osDebugInit ();
#endif

#ifdef __asm__
.extern __osDebugWriteChar
#else
void __osDebugWriteChar (int x, int y, u8 ch);
#endif

#ifdef __asm__
.extern __osDebugPrint
#else
void __osDebugPrint (int x, int y, char *str);
#endif

#ifdef __asm__
.extern __osDebugDumpRegisters
#else
void __osDebugDumpRegisters ();
#endif

#ifdef __asm__
.extern __osDebugFormatHex
#else
void __osDebugFormatHex (u32 value, char *str);
#endif

#ifdef __asm__
.extern __osError
#else
void __osError (char *error_msg);
#endif

/*
 * Internal variables
 */

#endif

#endif
