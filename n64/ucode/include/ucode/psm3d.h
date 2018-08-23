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

#include <ucode/rdp.h>

#ifndef __asm__

/** @brief Display list command for PSM3D */
typedef struct __attribute__((packed, aligned(8))) uPSM3DDispCmd_t {
    /** @brief First part of command */
    u32 cmd1;
    /** @brief Second part of command */
    u32 cmd2;
} uPSM3DDispCmd;

#endif

/*
 * Opcodes
 */

#define UCODE_PSM3D_OP_RDP_THROUGH 0x80

#define UCODE_PSM3D_OP_NOOP 0x00
#define UCODE_PSM3D_OP_END_DL 0x01

#define UCODE_PSM3D_OP_SET_BLEND_MODE 0x05
#define UCODE_PSM3D_OP_SET_COMBINE_MODE 0x06

/*
 * Operation macros
 */

#define usPSM3DNoop() { (UCODE_PSM3D_OP_NOOP << 24) | 0, 0 }

#define usPSM3DEndDL() { (UCODE_PSM3D_OP_END_DL << 24) | 0, 0 }

#define UCODE_PSM3D_SET_IMAGE_FMT_RGBA 0
#define UCODE_PSM3D_SET_IMAGE_FMT_YUV 1
#define UCODE_PSM3D_SET_IMAGE_FMT_CI 2
#define UCODE_PSM3D_SET_IMAGE_FMT_IA 3
#define UCODE_PSM3D_SET_IMAGE_FMT_I 4

#define UCODE_PSM3D_SET_IMAGE_SIZE_4BPP 0
#define UCODE_PSM3D_SET_IMAGE_SIZE_8BPP 1
#define UCODE_PSM3D_SET_IMAGE_SIZE_16BPP 2
#define UCODE_PSM3D_SET_IMAGE_SIZE_32BPP 3

#define usPSM3DRdpThrough(opcode, data1, data2) \
    {\
        (UCODE_PSM3D_OP_RDP_THROUGH << 24) |\
        (opcode << 24) |\
        data1,\
            \
        data2\
    }

#define usPSM3DSetColorImg(dram_addr, format, size, width) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Color_Image,\
        (UCODE_PSM3D_SET_IMAGE_FMT_##format << 21) |\
        (UCODE_PSM3D_SET_IMAGE_SIZE_##size << 19) |\
        (width - 1), \
            \
        dram_addr\
    )

#define usPSM3DSetTextureImg(dram_addr, format, size, width) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Texture_Image,\
        (UCODE_PSM3D_SET_IMAGE_FMT_##format << 21) |\
        (UCODE_PSM3D_SET_IMAGE_SIZE_##size << 19) |\
        (width - 1), \
            \
        dram_addr\
    )


#define usPSM3DSetEnvColor(r, g, b, a) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Env_Color,\
        0,\
        (r << 24) | (g << 16) | (b << 8) | a\
    )

#define usPSM3DSetBlendColor(r, g, b, a) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Blend_Color,\
        0,\
        (r << 24) | (g << 16) | (b << 8) | a\
    )

#define usPSM3DSetFogColor(r, g, b, a) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Fog_Color,\
        0,\
        (r << 24) | (g << 16) | (b << 8) | a\
    )

#define usPSM3DSetFillColor(color) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Fill_Color,\
        0,\
        color\
    )

#define usPSM3DSetPrimDepth(z, delta) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Prim_Depth,\
        0,\
        (z << 16) | (delta << 8)\
    )

#define usPSM3DSyncFull() \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Sync_Full,\
        0,\
        0\
    )

#define usPSM3DSyncPipe() \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Sync_Pipe,\
        0,\
        0\
    )

#define usPSM3DSyncLoad() \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Sync_Load,\
        0,\
        0\
    )

// TODO: Add field stuff... I'm too tired.

#define usPSM3DSetScissor(xh, yh, xl, yl) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Scissor,\
        (xh << 12) | yh,\
        (xl << 12) | yl\
    )

#define usPSM3DSetConvert(k0, k1, k2, k3, k4, k5) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Convert,\
        ((k2 & 0x1f) << 27) | (k3 << 18) | (k4 << 9) | k5,\
        (k0 << 13) | (k1 << 4) \
    )

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
