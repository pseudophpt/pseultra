/*
 * pseultra/n64/math/src/mtx.c
 * Floating point operations
 * 
 * (C) pseudophpt 20189
 */

/**
 * @file src/mtx.c
 * @brief Floating point operations
 * @date 1 Jul 2019
 * @author pseudophpt
 *
 * This file provides routines for performing operations on floating point numbers 
 */

#include <math.h>

/**
 * @brief Constructs a translation matrix at the provided address 
 * @param[out] mtx Matrix to write result to
 * @param[in] dx Translation in x direction (s15.16)
 * @param[in] dy Translation in y direction (s15.16)
 * @param[in] dz Translation in z direction (s15.16)
 * @param[in] transpose Transpose this matrix if this value is non-zero. Must be used if this matrix is on the base of a matrix stack for pseultra microcodes.
 * @date 1 Jul 2019
 * @author pseudophpt
 *
 * This function constructs a fixed point translation matrix for use with microcode given translation components.
 *
 */
void
mathMtxTrans
(MMtx *mtx, s32 dx, s32 dy, s32 dz, int transpose) {
    // Construct identity matrix
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            mtx->frac[i][j] = 0;
            if (i == j) {
                mtx->intgr[i][j] = 1;
            }
            else {
                mtx->intgr[i][j] = 0;
            }
        }
    }

    // If not transposing, coefficients go in the rightmost column vector
    if (transpose == 0) {
        mtx->intgr[0][3] = (dx >> 16);
        mtx->frac[0][3] = (dx & 0xFFFF);
                     
        mtx->intgr[1][3] = (dy >> 16);
        mtx->frac[1][3] = (dy & 0xFFFF);
                     
        mtx->intgr[2][3] = (dz >> 16);
        mtx->frac[2][3] = (dz & 0xFFFF);
    }
    
    // If transposing, coefficients go in the bottom row vector
    else {
        mtx->intgr[3][0] = (dx >> 16);
        mtx->frac[3][0] = (dx & 0xFFFF);

        mtx->intgr[3][1] = (dy >> 16);
        mtx->frac[3][1] = (dy & 0xFFFF);

        mtx->intgr[3][2] = (dz >> 16);
        mtx->frac[3][2] = (dz & 0xFFFF);
    }
}
