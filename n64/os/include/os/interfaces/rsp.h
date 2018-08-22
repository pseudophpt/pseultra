/*
 * pseultra/n64/os/include/os/interfaces/rsp.h
 * RSP interface header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/interfaces/rsp.h
 * @brief RSP header 
 * @date 20 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs, constants, and functions related to the RSP 
 */

#ifndef OS_INTERFACES_RSP_H_GUARD
#define OS_INTERFACES_RSP_H_GUARD

/*
 * Macros
 */

/*
 * Structs
 */

#ifndef __asm__

/** @brief Structure describing an RSP microcode task */
typedef struct __attribute__((packed, aligned(8))) OSUTask_t {
    /** @brief Physical DRAM Pointer to display list @note The display list must be aligned to 64 bits */
    void *dl;
    /** @brief Currently unused */
    u32 unused1 [3];
} OSUTask;

#endif

/*
 * Public functions
 */

#ifdef __asm__
.extern osRspLoadUCode
#else
void osRspLoadUCode (void *ucode_start, void *ucode_end);
#endif

#ifdef __asm__
.extern osRspStartTask
#else
void osRspStartTask (OSUTask task);
#endif

/*
 * Public variables
 */

#ifdef __os_internal__

/*
 * Internal functions
 */

/*
 * Internal variables
 */

#endif

#endif
