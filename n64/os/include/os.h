/*
 * pseultra/headers/os.h
 * OS Header
 * 
 * (C) pseudophpt 2018 
 */

#ifndef OS_H_GUARD
#define OS_H_GUARD

#include <n64.h>

// Types
typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned long u32;
typedef signed long s32;

// Null
#define NULL ((void *) 0)

// Default stack size
#define OS_STACK_SIZE 0x1000

#include <os/memory.h>
#include <os/event.h>

#endif
