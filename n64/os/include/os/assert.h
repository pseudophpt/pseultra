/*
 * pseultra/n64/os/include/os/assert.h
 * OS Assert Header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/assert.h
 * @brief OS Assert Header 
 * @date 20 Aug 2018
 * @author pseudophpt
 *
 * This file defines the assert macro which halts the game if the specified condition is not true 
 */

#ifndef OS_ASSERT_H_GUARD
#define OS_ASSERT_H_GUARD

#define OS_ASSERT_STRINGIFY2(x) #x
#define OS_ASSERT_STRINGIFY(x) OS_ASSERT_STRINGIFY2(x)

#ifdef __asm__



#else

#define assert(x) \
    if (!(x)) __osError("Assertion Failed: " OS_ASSERT_STRINGIFY(x) "\nLine " OS_ASSERT_STRINGIFY(__LINE__) " in " OS_ASSERT_STRINGIFY(__FILE__));

#endif

#endif
