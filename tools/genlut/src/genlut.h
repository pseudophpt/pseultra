/*
 * pseultra/tools/genlut/src/genlut.h
 * GenLUT header file
 *
 * (C) pseudophpt 2018
 */

#ifndef GENLUT_GENLUT_H_GUARD
#define GENLUT_GENLUT_H_GUARD

typedef struct lut_func_t {
    float (*flop)(int); // Floating point operation
    char *lut_name; // LUT function name
    int entries;
} lut_func;

void gen_lut (lut_func lut, FILE *lut_file);

float sinf_wrap (int);
float cosf_wrap (int);

#endif
