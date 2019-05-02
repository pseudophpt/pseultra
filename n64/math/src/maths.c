/*
 * pseultra/n64/math/src/maths.c
 * Fixed point operations
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/maths.c
 * @brief Fixed point operations
 * @date 4 Sep 2018
 * @author pseudophpt
 *
 * This file provides routines for performing operations on fixed point numbers 
 */

#include <math.h>

// Include lookup table
#include "lut.h"

/**
 * @brief Performs a sine calculation on a fixed point number 
 * @param[in] in Fixed point number to calculate sine of (-0x8000 - 0x7FFF, representing -PI to PI)
 * @return Result of sine calculation
 * @date 4 Sep 2018
 * @author pseudophpt
 *
 * This function performs a fast sine calculation on a fixed point number in the range [-0x8000, 0x7FFF], representing [-PI, PI] and returns the fixed point s15.16 result. It uses a look-up table to quickly get the value of sine.
 */
s32
mathSSin
(s16 in) {
    // Sine is an odd function
    s32 ret = (in > 0) ? 1 : -1;
    if (in == 0) {
        return 0;
    }

    // Round towards 0
    in -= ret;

    // Get absolute value
    in *= ret;

    // Shift to offset
    in >>= 3;

    // If > PI/2, reflect over y-axis (sine's symmetry) 
    if (in >= 0x800) {
        in = 0xFFF - in;
    }

    // Multiply by look up value
    ret *= sin_lut[in];

    // Return
    return ret;
}

/**
 * @brief Performs a cosine calculation on a fixed point number 
 * @param[in] in Fixed point number to calculate cosine of (-0x8000 - 0x7FFF, representing -PI to PI)
 * @return Result of cosine calculation
 * @date 4 Sep 2018
 * @author pseudophpt
 *
 * This function performs a fast cosine calculation on a fixed point number in the range [-0x8000, 0x7FFF], representing [-PI, PI] and returns the fixed point s15.16 result. It uses a look-up table to quickly get the value of cosine.
 */
s32
mathSCos
(s16 in) {
    // Change to sine value
    in = 0x4000 - in;

    // Return sine
    return mathSSin(in);
}

