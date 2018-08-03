/*
 * pseultra/n64/os/include/os/event/exception.h
 * Exception handler
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/event/exception.h
 * @brief OS Exception header 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to the handling of exceptions 
 */

#ifndef OS_EVENT_EXCEPTION_H_GUARD
#define OS_EVENT_EXCEPTION_H_GUARD

// Functions
#ifdef __asm__
.extern osGetIntMask
#else
u32 osGetIntMask (void);
#endif

#ifdef __asm__
.extern osSetIntMask
#else
void osSetIntMask(u32 mask);
#endif

// Variables

#ifdef __os_internal__
// Internal functions

#ifdef __asm__
.extern __osHandleInterrupt
#else
void __osHandleInterrupt (u32 interrupt);
#endif

#ifdef __asm__
.extern __osHandleRCPInterrupt
#else
void __osHandleRCPInterrupt ();
#endif

#ifdef __asm__
.extern __osHandleExceptions
#else
void __osHandleException();
#endif

#ifdef __asm__
.extern __osUnmaskInterrupts
#else
void __osUnmaskInterrupts();
#endif

// Internal variables
#ifdef __asm__
.extern __osHandlerStart
#else
extern u32 __osHandlerStart;
#endif

#ifdef __asm__
.extern __osHandlerEnd
#else
extern u32 __osHandlerEnd;
#endif

#endif

#endif
