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

u32 osGetIntMask (void);
void osSetIntMask(u32 mask);

#endif
