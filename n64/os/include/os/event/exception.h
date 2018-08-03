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
u32 osGetIntMask (void);
void osSetIntMask(u32 mask);

// Variables

#ifdef __os_internal__
// Internal functions
void __osHandleInterrupt (u32 interrupt);
void __osHandleRCPInterrupt ();
void __osHandleException();
void __osUnmaskInterrupts();

// Internal variables
extern u32 __osHandlerStart;
extern u32 __osHandlerEnd;
#endif

#endif
