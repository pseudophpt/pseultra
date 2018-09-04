/*
 * pseultra/include/ints.h
 * Integer types header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/ints.h
 * @brief Integer types header 
 * @date 4 Sep 2018
 * @author pseudophpt
 *
 * This file is included in any code using pseultra integer types
 */

#ifndef INTS_H_GUARD
#define INTS_H_GUARD

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

/** @brief Unsigned 64 bit type */
typedef unsigned long long u64;
/** @brief Signed 64 bit type */
typedef signed long long s64;

#endif

#endif
