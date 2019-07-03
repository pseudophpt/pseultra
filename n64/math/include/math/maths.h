/*
 * pseultra/n64/math/include/math/maths.h
 * Fixed point operations
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/math/maths.h
 * @brief Fixed point operations header
 * @date 4 Sep 2018
 * @author pseudophpt
 *
 * This file includes all fixed point operation headers 
 */

#ifndef MATH_MATHS_H_GUARD
#define MATH_MATHS_H_GUARD

#ifdef __asm__
.extern mathSSin
#else
extern s32 mathSSin (s16 in);
#endif

#ifdef __asm__
.extern mathSCos
#else
extern s32 mathSCos (s16 in);
#endif

#endif
