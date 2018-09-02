/*
 * pseultra/n64/os/src/boot/reg.h
 * Registers header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/boot/reg.h
 * @brief Registers header 
 * @date 19 Aug 2018
 * @author pseudophpt
 *
 * This file defines strings for each register
 */

#ifndef OS_BOOT_REG_H_GUARD
#define OS_BOOT_REG_H_GUARD

/** @brief All register names for debug register dump */
char *osDebugRegNames [32] = {
    "zr", 
    "at", 
    "v0", "v1",
    "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9",
    "k0", "k1",
    "gp", "sp",
    "s8",
    "ra"
};

#endif
