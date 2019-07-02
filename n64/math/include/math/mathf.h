/*
 * pseultra/n64/math/include/math/mathf.h
 * Floating point operations
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/math/mathf.h
 * @brief Floating point operations header
 * @date 2 Sep 2018
 * @author pseudophpt
 *
 * This file includes all floating point operation headers 
 */

#ifndef MATH_MATHF_H_GUARD
#define MATH_MATHF_H_GUARD

#ifdef __asm__
.extern mathFMod
#else
extern float mathFMod (float in, float mod);
#endif

#ifdef __asm__
.extern mathFSin
#else
extern float mathFSin (float in);
#endif

#ifdef __asm__
.extern mathFCos
#else
extern float mathFCos (float in);
#endif

#ifdef __asm__
.extern mathFtoS
#else
extern s32 mathFtoS (float in);
#endif

#endif
