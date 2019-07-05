/*
 * pseultra/n64/os/include/os/interfaces/si.h
 * Serial interface header
 * 
 * (C) pseudophpt 2019 
 */

/**
 * @file include/os/interfaces/si.h
 * @brief Serial interface header 
 * @date 4 Jul 2019
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to the serial interface (SI) 
 */

#ifndef OS_INTERFACES_SI_H_GUARD
#define OS_INTERFACES_SI_H_GUARD

/*
 * Macros
 */

/** @brief Error code for no device connected */
#define OS_SI_ERROR_NODEV 0x80
/** @brief Error code for bad command format */
#define OS_SI_ERROR_BADCMD 0x40
/** @brief Error code mask */
#define OS_SI_ERROR_MASK 0xC0

/*
 * Structs
 */

#ifndef __asm__

/** @brief Struct describing controller data */
typedef struct OSCont_t {
    /** @brief Buttons being pressed */
    u16 buttons;
    /** @brief X on control stick */
    s8 x;
    /** @brief Y on control stick */
    s8 y;
    /** @brief Errors */
    u8 err;
} OSCont;

#endif

/*
 * Public functions
 */

#ifdef __asm__
.extern osSiStartTask
#else
void osSiStartTask (int controllers);
#endif

#ifdef __asm__
.extern osSiWaitTask
#else
void osSiWaitTask ();
#endif

#ifdef __asm__
.extern osSiReadData
#else
void osSiReadData (OSCont controllers []);
#endif

/*
 * Public variables
 */

#ifdef __os_internal__

/*
 * Internal functions
 */

#ifdef __asm__
.extern __osSiWrite
#else
void __osSiWrite ();
#endif

#ifdef __asm__
.extern __osSiRead
#else
void __osSiRead ();
#endif

/*
 * Internal variables
 */

#ifdef __asm__
.extern __osSiBuffer
#else
extern u8 __osSiBuffer [];
#endif

#endif

#endif
