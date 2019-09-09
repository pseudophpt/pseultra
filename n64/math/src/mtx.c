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

static inline void mathMtxWrite (MMtx *mtx, int r, int c, s32 e);

/**
* @brief Writes to a matrix entry 
* @param[out] mtx Matrix to write result to
* @param[in] r Row of element to write 
* @param[in] c Column of element to write
* @param[in] e Element to write 
* @date 3 Jul 2019
* @author pseudophpt
*
* This inline function writes a s16.15 fixed point number to a certain element of a fixed point array
*
*/
static inline void
mathMtxWrite
(MMtx *mtx, int r, int c, s32 e) {
    mtx->intgr[r][c] = e >> 16;
    mtx->frac[r][c] = e & 0xFFFF;
}

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
        mathMtxWrite(mtx, 0, 3, dxs);
        mathMtxWrite(mtx, 1, 3, dys);
        mathMtxWrite(mtx, 2, 3, dzs);
    }
    
    // If transposing, coefficients go in the bottom row vector
    else {
        mathMtxWrite(mtx, 3, 0, dxs);
        mathMtxWrite(mtx, 3, 1, dys);
        mathMtxWrite(mtx, 3, 2, dzs);
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
                mathMtxWrite(mtx, i, j, fixed_value);
            }
            else
            {
                mathMtxWrite(mtx, j, i, fixed_value);
            }
        }
    }

    // Fill bottom and right vectors
    for (int i = 0; i < 3; i ++) {
        mathMtxWrite(mtx, 3, i, 0);
        mathMtxWrite(mtx, i, 3, 0);
    }
    
    // Fill bottom right element with 1
    mathMtxWrite(mtx, 3, 3, mathFtoS(1));
}

/**
 * @brief Constructs a perspective projection matrix at the provided address 
 * @param[out] mtx Matrix to write result to
 * @param[in] yfov Field of view of Y in radians 
 * @param[in] invasp Inverse aspect ratio (height / width) of screen
 * @param[in] n Distance from camera to near clipping plane
 * @param[in] f Distance from camera to far clipping plane
 * @return W scale value
 * @date 2 Jul 2019
 * @author pseudophpt
 *
 * This function constructs a fixed point perspective projection matrix from given values. It is automatically non-transposed, as all projection matrices are at the base 
 *
 */
u16
mathMtxPersp
(MMtx *mtx, float yfov, float invasp, float n, float f) {
    // Clear matrix
    for (int i = 0; i < 4; i ++) {
        for (int j = 0; j < 4; j ++) {
            mathMtxWrite(mtx, i, j, 0);
        }
    }
    
    // Calculate cotangent of field of view in y direction
    float cot = mathFCos(yfov / 2) / mathFSin (yfov / 2);

    // Write matrix values
    mathMtxWrite(mtx, 0, 0, mathFtoS(cot * invasp)); 
    mathMtxWrite(mtx, 1, 1, mathFtoS(cot));
    mathMtxWrite(mtx, 2, 2, mathFtoS((n + f) / (n - f)));
    mathMtxWrite(mtx, 2, 3, mathFtoS((2 * n * f) / (n - f)));    
    mathMtxWrite(mtx, 3, 2, mathFtoS(-1));

    u16 w_scale = mathFtoS(2 / (n + f)) & 0xFFFF; // W scale value to normalize W = 1.0 halfway between near and far planes

    return w_scale;
}
