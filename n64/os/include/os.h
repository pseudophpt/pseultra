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

#include <ints.h>

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
