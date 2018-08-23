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

#ifndef __asm__

/** @brief Display list command for PSM3D */
typedef struct __attribute__((packed, align(8))) uPSM3DDispCmd_t {
    /** @brief First part of command */
    u32 cmd1;
    /** @brief Second part of command */
    u32 cmd2;
} uPSM3DDispCmd;

#endif

/*
 * Opcodes
 */

#define UCODE_PSM3D_OP_NOOP 0x00
#define UCODE_PSM3D_OP_END_DL 0x01
#define UCODE_PSM3D_OP_SET_COLOR_IMAGE 0x02
#define UCODE_PSM3D_OP_SET_TEXTURE_IMAGE 0x03
#define UCODE_PSM3D_OP_SET_Z_IMAGE 0x04
#define UCODE_PSM3D_OP_SET_SCISSOR 0x05
#define UCODE_PSM3D_OP_SET_BLEND_MODE 0x06
#define UCODE_PSM3D_OP_SET_COMBINE_MODE 0x07
#define UCODE_PSM3D_OP_SET_PRIM_COLOR 0x08
#define UCODE_PSM3D_OP_SET_BLEND_COLOR 0x09

/*
 * Operation macros
 */

#define usPSM3DNoop() { (UCODE_PSM3D_OP_NOOP << 24) | 0, 0 }
#define usPSM3DEndDL() { (UCODE_PSM3D_OP_END_DL << 24) | 0, 0 }
#define usPSM3DSetColorImg(dram_addr) { (UCODEPSM_3D_OP_END_DL << 24) | 0, 0 }

/*
 * Microcode locations
 */

#ifdef __asm__
.extern uPSM3DTextStart
#else
extern u8 uPSM3DTextStart [];
#endif

#ifdef __asm__
.extern uPSM3DTextEnd
#else
extern u8 uPSM3DTextEnd [];
#endif

#ifdef __asm__
.extern uPSM3DDataStart
#else
extern u8 uPSM3DDataStart [];
#endif

#ifdef __asm__
.extern uPSM3DDataEnd
#else
extern u8 uPSM3DDataEnd [];
#endif

#endif
