/*
 * pseultra/n64/os/include/os/interfaces/vi.h
 * Video interface header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/interfaces/vi.h
 * @brief Video interface header 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to the video interface (VI) 
 */

#ifndef OS_INTERFACES_VI_H_GUARD
#define OS_INTERFACES_VI_H_GUARD

/*
 * Macros
 */

/** @brief VI option for pixel mode @see osViInit */
#define OS_VI_OPTION_PIXEL 0x1
/** @brief VI option for 5/5/5/3 pixel mode @see osViInit */
#define OS_VI_OPTION_PIXEL_5553 0x0
/** @brief VI option for 8/8/8/8 pixel mode @see osViInit */
#define OS_VI_OPTION_PIXEL_8888 0x1
/** @brief VI option for resolution @see osViInit */
#define OS_VI_OPTION_RES 0x2
/** @brief VI option for 320x240 resolution @see osViInit */
#define OS_VI_OPTION_RES_LOW 0x0
/** @brief VI option for 640x4810 resolution @see osViInit */
#define OS_VI_OPTION_RES_HIGH 0x2
/** @brief Macro to construct VI options @see osViInit 
 *
 * To use this macro, specify the pixel mode as the first argument (5553 or 8888), and the resolution as the second argument (LOW or HIGH)
 */
#define OS_VI_MODE(pixel, res) \
    (OS_VI_OPTION_PIXEL_##pixel | \
    OS_VI_OPTION_RES_##res)

/*
 * Structs
 */

#ifndef __asm__
/** @brief OS VI Mode type */
typedef u8 OSViMode;
#endif

/*
 * Public functions
 */

#ifdef __asm__
.extern osViGetSwapBuffer
#else
void *osViGetSwapBuffer (void);
#endif

#ifdef __asm__
.extern osViGetCurrentBuffer
#else
void *osViGetCurrentBuffer (void);
#endif

#ifdef __asm__
.extern osViInit
#else
void osViInit (OSViMode mode);
#endif

#ifdef __asm__
.extern osViSwapBuffer
#else
void osViSwapBuffer (void *buffer);
#endif

/*
 * Public variables
 */

#ifdef __os_internal__

/*
 * Internal functions
 */

#ifdef __asm__
.extern __osViUpdateBuffer
#else
void __osViUpdateBuffer (void);
#endif

/*
 * Internal variables
 */

#ifdef __asm__
.extern __osViSwapBuffer
#else
extern void *__osViSwapBuffer;
#endif

#ifdef __asm__
.extern __osViCurrentBuffer
#else
extern void *__osViCurrentBuffer;
#endif

#endif

#endif
