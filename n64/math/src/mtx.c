/*
 * pseultra/n64/math/src/mtx.c
 * Floating point operations
 * 
 * (C) pseudophpt 20189
 */

/**
 * @file src/mtx.c
 * @brief Matrix operations
 * @date 1 Jul 2019
 * @author pseudophpt
 *
 * This file provides routines for performing operations on fixed point matrices
 */

#include <math.h>

/**
 * @brief Constructs a translation matrix at the provided address 
 * @param[out] mtx Matrix to write result to
 * @param[in] dx Translation in x direction
 * @param[in] dy Translation in y direction
 * @param[in] dz Translation in z direction
 * @param[in] transpose Transpose this matrix if this value is non-zero. Must be used if this matrix is not on the base of a matrix stack for pseultra microcodes.
 * @date 1 Jul 2019
 * @author pseudophpt
 *
 * This function constructs a fixed point translation matrix for use with microcode given translation components.
 *
 */
void
mathMtxTrans
(MMtx *mtx, float dx, float dy, float dz, int transpose) {
    s32 dxs = mathFtoS(dx);
    s32 dys = mathFtoS(dy);
    s32 dzs = mathFtoS(dz);

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
        mtx->intgr[0][3] = (dxs >> 16);
        mtx->frac[0][3] = (dxs & 0xFFFF);
                     
        mtx->intgr[1][3] = (dys >> 16);
        mtx->frac[1][3] = (dys & 0xFFFF);
                     
        mtx->intgr[2][3] = (dzs >> 16);
        mtx->frac[2][3] = (dzs & 0xFFFF);
    }
    
    // If transposing, coefficients go in the bottom row vector
    else {
        mtx->intgr[3][0] = (dxs >> 16);
        mtx->frac[3][0] = (dxs & 0xFFFF);

        mtx->intgr[3][1] = (dys >> 16);
        mtx->frac[3][1] = (dys & 0xFFFF);

        mtx->intgr[3][2] = (dzs >> 16);
        mtx->frac[3][2] = (dzs & 0xFFFF);
    }
}

/**
 * @brief Constructs an Euler rotation matrix at the provided address 
 * @param[out] mtx Matrix to write result to
 * @param[in] x Normalized X component of the axis of rotation
 * @param[in] y Normalized Y component of the axis of rotation
 * @param[in] z Normalized Z component of the axis of rotation
 * @param[in] theta Amount of rotation around axis
 * @param[in] transpose Transpose this matrix if this value is non-zero. Must be used if this matrix is not on the base of a matrix stack for pseultra microcodes.
 * @date 1 Jul 2019
 * @author pseudophpt
 *
 * This function constructs a fixed point rotation matrix from Euler rotation for use with microcode given components.
 *
 */
void
mathMtxRot
(MMtx *mtx, float x, float y, float z, float theta, int transpose) {
    // Calculate values necessary for calculation of this matrix
    float sin = mathFSin(theta);
    float cos = mathFCos(theta);

    // Create components to make this easier
    float components [4] = { x, y, z, 0 };

    // Construct matrix
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j ++) {
            // First expression
            float value = components[i] * components[j] * (1 - cos);
            
            // Add second expression
            if (i == j)
            {
                value += cos;
            }
            else
            {
                int sign = ((4 + j - i) % 3) - 1; // Sign of added expression
                int component = ((6 - i - j) % 3); // Component to use
                value += (sign * sin * components[component]);
            }

            // Convert to fixed point
            s32 fixed_value = mathFtoS(value);
            
            // Apply to matrix
            if (transpose == 0)
            {
                mtx->intgr[i][j] = (fixed_value >> 16);
                mtx->frac[i][j] = (fixed_value & 0xFFFF);
            }
            else
            {
                mtx->intgr[j][i] = (fixed_value >> 16);
                mtx->frac[j][i] = (fixed_value & 0xFFFF);
            }
        }
    }

    // Fill bottom and right vectors
    for (int i = 0; i < 3; i ++) {
        mtx->intgr[3][i] = 0;
        mtx->frac[3][i] = 0; 
        
        mtx->intgr[i][3] = 0;
        mtx->frac[i][3] = 0; 
    }
    
    // Fill bottom right element with 1
    mtx->intgr[3][3] = 1;
    mtx->frac[3][3] = 0; 
}
