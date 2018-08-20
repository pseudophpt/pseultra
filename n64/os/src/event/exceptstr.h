/*
 * pseultra/n64/os/src/event/exceptstr.h
 * Exception message header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/event/exceptstr.h
 * @brief Exception string header 
 * @date 19 Aug 2018
 * @author pseudophpt
 *
 * This file defines the messages for each type of exception
 */

#ifndef OS_EVENT_EXCEPTSTR_H_GUARD
#define OS_EVENT_EXCEPTSTR_H_GUARD

/** @brief Exception string table */
char *osDebugExceptStr [32] = {
    "Interrupt",
    "TLB Modification",
    "TLB Miss on Load",
    "TLB Miss on Store",
    "Address Error on Load",
    "Address Error on Store",
    "Bus Error on Fetch",
    "Bus Error on Data Reference",
    "Syscall",
    "Breakpoint",
    "Reserved Instruction",
    "Coprocessor Unusable",
    "Arithmetic Overflow",
    "Trap",
    "",
    "Floating-Point",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "Watch",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    ""
};

#endif
