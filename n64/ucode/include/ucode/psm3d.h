/*
 * pseultra/n64/ucode/include/ucode/psm3d.h
 * PSM3D Header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/ucode/psm3d.h
 * @brief PSM3D Header 
 * @date 20 Aug 2018
 * @author pseudophpt
 *
 * This file defines macros related to the PSM3D microcode 
 */

#ifndef UCODE_PSM3D_H_GUARD
#define UCODE_PSM3D_H_GUARD

#ifdef __asm__
.extern uPSM3DStart
#else
extern u8 uPSM3DStart [];
#endif

#ifdef __asm__
.extern uPSM3DEnd
#else
extern u8 uPSM3DEnd [];
#endif

#endif
