/*
 * pseultra/n64/math/src/mathf.c
 * Floation point operations
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
 * This function performs a fast sine calculation on a floating point number number in the range [-PI, PI] in radians, and returns the floating point result. It uses a polynomial to quickly approinimate the value of sine.
 *
 * @note Using this function with a number out of the range [-PI, PI] will be inaccurate due to the polynomial calculation
 */
float
mathFSin
(float in) {
    return (MATH_MATHF_4_BY_PI * in) + (((in < 0.0) ? 1 : -1) * MATH_MATHF_4_BY_PI_SQUARED * in * in);
}

