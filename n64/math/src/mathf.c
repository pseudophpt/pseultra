/*
 * pseultra/n64/math/src/mathf.c
 * Floating point operations
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/mathf.c
 * @brief Floating point operations
 * @date 2 Sep 2018
 * @author pseudophpt
 *
 * This file provides routines for performing operations on floating point numbers 
 */

#include <math.h>

/** @brief Constant describing 4 divided by pi */
#define MATH_MATHF_4_BY_PI 1.27323954474
/** @brief Constant describing 4 divided by pi squared */
#define MATH_MATHF_4_BY_PI_SQUARED 0.40528473456
/** @brief Constant describing pi */
#define MATH_MATHF_PI 3.14159265359 

/**
 * @brief Performs a modulo operation on two floating point numbers 
 * @param[in] in Floating point number to divide
 * @param[in] mod Floating point modulus
 * @return Result of floating point modulo of (in / mod)
 * @date 2 Sep 2018
 * @author pseudophpt
 *
 * This function performs a floating point modulo operation on two numbers and returns the result 
 *
 */
float
mathFMod
(float in, float mod) {
    return in - ((int)(in / mod) * mod);    
}

/**
 * @brief Performs a sine calculation on a floating point number 
 * @param[in] in Floating point number to calculate sine of (in radians)
 * @return Result of sine calculation
 * @date 2 Sep 2018
 * @author pseudophpt
 *
 * This function performs a fast sine calculation on a floating point number number in the range [-PI, PI] in radians, and returns the floating point result. It uses a polynomial to quickly approximate the value of sine.
 *
 * @note Using this function with a number out of the range [-PI, PI] will be inaccurate due to the polynomial calculation
 */
float
mathFSin
(float in) {
    // Quadratic approximation, symmetric across origin
    return (MATH_MATHF_4_BY_PI * in) + (((in < 0.0) ? 1 : -1) * MATH_MATHF_4_BY_PI_SQUARED * in * in);
}

/**
 * @brief Performs a cosine calculation on a floating point number 
 * @param[in] in Floating point number to calculate cosine of (in radians)
 * @return Result of cosine calculation
 * @date 4 Sep 2018
 * @author pseudophpt
 *
 * This function performs a fast cosine calculation on a floating point number number in the range [-PI, PI] in radians, and returns the floating point result. It uses a polynomial to quickly approximate the value of cosine.
 *
 * @note Using this function with a number out of the range [-PI, PI] will be inaccurate due to the polynomial calculation
 */
float
mathFCos
(float in) {
    // Change to sine input
    in = (MATH_MATHF_PI / 2) - in;
    
    // Wrap around if necessary
    if (in > MATH_MATHF_PI) {
        in -= (MATH_MATHF_PI * 2);
    }

    // Return sine approximation
    return mathFSin(in);
}

/**
 * @brief Converts a floating point number into fixed point s16.15
 * @param[in] in Floating point number to convert to fixed point
 * @return Clamped s15.16 equivalent of input float
 * @date 1 Jul 2019
 * @author pseudophpt
 *
 * This function converts a floating point number into a signed s16.15 fixed point number. It clamps for numbers larger than 32768 or smaller than -32768.
 */
s32
mathFtoS
(float in) {
    // Clamp
    if (in >= 32768.0)
    {
        return 0x7FFFFFFF;
    }
    else if (in < -32768.0)
    {
        return 0x80000000;
    }
    else
    {
        // Return in << 16 floored
        return (s32)(in * 65536.0);
    }
}
