/*
 * pseultra/n64/os/include/os.h
 * OS Header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os.h
 * @brief OS Header 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file is included in any code using libpseultra
 */

#ifndef OS_H_GUARD
#define OS_H_GUARD

#include <n64.h>

#ifndef __asm__

/** @brief Unsigned 8 bit type */
typedef unsigned char u8;
/** @brief Signed 8 bit type */
typedef signed char s8;

/** @brief Unsigned 16 bit type */
typedef unsigned short u16;
/** @brief Signed 16 bit type */
typedef signed short s16;

/** @brief Unsigned 32 bit type */
typedef unsigned long u32;
/** @brief Signed 32 bit type */
typedef signed long s32;

#endif

/** @brief Void pointer to 0 */
#define NULL ((void *) 0)
/** @brief Default OS stack size */
#define OS_STACK_SIZE 0x4000

#include <os/assert.h>

#include <os/memory.h>
#include <os/event.h>
#include <os/boot.h>
#include <os/interfaces.h>

#endif
