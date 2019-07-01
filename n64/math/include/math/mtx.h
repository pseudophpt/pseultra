/*
 * pseultra/n64/math/include/math/mtx.h
 * Matrix operations
 * 
 * (C) pseudophpt 2019 
 */

/**
 * @file include/math/mtx.h
 * @brief Matrix operations header
 * @date 1 Jul 2019
 * @author pseudophpt
 *
 * This file includes all matrix definitions
 */

#ifndef MATH_MTX_H_GUARD
#define MATH_MTX_H_GUARD

#ifndef __asm__

/** @brief Fixed point matrix */
typedef struct __attribute__((packed, aligned(8))) MMtx_t {
    /** @brief Integral part of matrix */
    s16 intgr [4][4];
    /** @brief Fractional part of matrix */
    u16 frac [4][4];
} MMtx;

#endif

#ifdef __asm__
.extern mathMtxTrans
#else
extern void mathMtxTrans (MMtx *mtx, s32 dx, s32 dy, s32 dz, int transpose);
#endif

#endif
