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
extern void mathMtxTrans (MMtx *mtx, float dx, float dy, float dz, int transpose);
#endif

#ifdef __asm__
.extern mathMtxRot
#else
extern void mathMtxRot (MMtx *mtx, float x, float y, float z, float theta, int transpose);
#endif

#ifdef __asm__
.extern mathMtxPersp
#else
extern u16 mathMtxPersp (MMtx *mtx, float yfov, float invasp, float n, float f);
#endif

#endif
