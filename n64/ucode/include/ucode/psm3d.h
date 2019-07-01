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

// TODO: Make SetOtherMode combinable by providing a way to list which bits
// are being edited, and their values

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

/** @brief Vertex for PSM3D */
typedef struct __attribute__((packed, aligned(8))) uPSM3DVtx_t {
    /** @brief X-Coordinate Integral (s15.16 fixed point) */
    s16 xi;
    /** @brief Y-Coordinate Integral (s15.16 fixed point) */
    s16 yi;
    /** @brief Z-Coordinate Integral (s15.16 fixed point) */
    s16 zi;
    /** @brief Padding */
    u16 pad;
    /** @brief X-Coordinate Fractional (s15.16 fixed point) */
    s16 xf;
    /** @brief Y-Coordinate Fractional (s15.16 fixed point) */
    s16 yf;
    /** @brief Z-Coordinate Fractional (s15.16 fixed point) */
    s16 zf;
    /** @brief Padding */
    u16 pad2;
    /** @brief S coordinate (s10.5) */
    s16 s;
    /** @brief T coordinate (s10.5) */
    s16 t;
    /** @brief Padding */
    u32 pad3;
    /** @brief X-Normal (s.7 fixed point) / R Shading */
    s8 xn;
    /** @brief Y-Normal (s.7 fixed point) / G Shading */
    s8 yn;
    /** @brief Z-Normal (s.7 fixed point) / B Shading */
    s8 zn;
    /** @brief Padding (this padding must be zero) */
    u8 pad4;
    /** @brief Padding */
    u32 pad5;
} uPSM3DVtx;

/** @brief Matrix for PSM3D */
typedef struct __attribute__((packed, aligned(8))) uPSM3DMtx_t {
    /** @brief Integral part of matrix */
    u16 intgr [4][4];
    /** @brief Fractional part of matrix */
    u16 frac [4][4];
} uPSM3DMtx;

/** @brief Viewport for PSM3D */
typedef struct __attribute__((packed, aligned(8))) uPSM3DVp_t {
    /** @brief Half the viewport width */
    u16 hwidth;
    /** @brief Half the viewport height */
    u16 hheight;
    /** @brief Viewport X offset */
    s16 xoff;
    /** @brief Viewport Y offset */
    s16 yoff;
} uPSM3DVp;

/** @brief Ambient light structure for PSM3D */
typedef struct __attribute((aligned(8))) uPSM3DAmbientLight_t {
    /** @brief Red value of ambient light color */
    u8 r;
    /** @brief Green value of ambient light color */
    u8 g;
    /** @brief Blue value of ambient light color */
    u8 b;
} uPSM3DAmbientLight;

/** @brief Point light structure for PSM3D */
typedef struct __attribute((aligned(8))) uPSM3DPointLight_t {
    /** @brief Red value of point light color */
    u8 r;
    /** @brief Green value of point light color */
    u8 g;
    /** @brief Blue value of point light color */
    u8 b;
    /** @brief Attenuation factor */
    u8 att;
    /** @brief X value of point light in current coordinate system (MODELVIEW) */
    s8 x;
    /** @brief Y value of point light in current coordinate system (MODELVIEW) */
    s8 y;
    /** @brief Z value of point light in current coordinate system (MODELVIEW) */
    s8 z;
    /** @brief Padding */
    u8 pad;
} uPSM3DPointLight;

/** @brief Light structure for PSM3D */
typedef struct __attribute__((packed, aligned(8))) uPSM3DLights_t {
    /** @brief Ambient light */
    uPSM3DAmbientLight ambient;
    /** @brief Point lights */
    uPSM3DPointLight point_lights [];
} uPSM3DLights;

#endif

#define _FMT(data, shift, size) (((data) << shift) & (((1 << size) - 1) << shift))

/*
 * Opcodes
 */

#define UCODE_PSM3D_OP_RDP_THROUGH 0x80

#define UCODE_PSM3D_OP_NOOP 0x00
#define UCODE_PSM3D_OP_END_DL 0x01
#define UCODE_PSM3D_OP_SET_OTHER_MODE 0x02
#define UCODE_PSM3D_OP_SET_RSP_MODE 0x03
#define UCODE_PSM3D_OP_RECT 0x04
#define UCODE_PSM3D_OP_LOAD_VTX 0x05
#define UCODE_PSM3D_OP_LOAD_MTX 0x06
#define UCODE_PSM3D_OP_TRI 0x07
#define UCODE_PSM3D_OP_SET_VP 0x08
#define UCODE_PSM3D_OP_POP_MTX 0x09
#define UCODE_PSM3D_OP_LOAD_LIGHTS 0x0A

/*
 * Operation macros
 */

#define usPSM3DNoop() { (UCODE_PSM3D_OP_NOOP << 24), 0 } 
#define uPSM3DNoop(dl) *((dl) ++) = (uPSM3DDispCmd) { _FMT(UCODE_PSM3D_OP_NOOP, 24, 8), 0 } 

#define usPSM3DEndDL() { (UCODE_PSM3D_OP_END_DL << 24), 0 }
#define uPSM3DEndDL(dl) *((dl) ++) = (uPSM3DDispCmd) { _FMT(UCODE_PSM3D_OP_END_DL, 24, 8), 0 }

#define usPSM3DSetOtherMode(maskh, maskl, datah, datal) { _FMT(UCODE_PSM3D_OP_SET_OTHER_MODE, 24, 8) | _FMT(maskh, 0, 24) , _FMT(datah, 0, 24) } , { maskl , datal }
#define uPSM3DSetOtherMode(dl, maskh, maskl, datah, datal) *((dl) ++) = (uPSM3DDispCmd) { _FMT(UCODE_PSM3D_OP_SET_OTHER_MODE, 24, 8) | _FMT(maskh, 0, 24) , _FMT(datah, 0, 24) }; *((dl) ++) = (uPSM3DDispCmd) {  maskl , datal }


#define UCODE_PSM3D_RSPMODE_TEXTURING 0x80
#define UCODE_PSM3D_RSPMODE_TEXTURING_ON 0x80
#define UCODE_PSM3D_RSPMODE_TEXTURING_OFF 0

#define UCODE_PSM3D_RSPMODE_TEXTURE_TILE 0x07
#define UCODE_PSM3D_RSPMODE_TEXTURE_TILENO(x) (x & 0x07)

#define UCODE_PSM3D_RSPMODE_CULL 0x300
#define UCODE_PSM3D_RSPMODE_CULL_CLOCK 0x200
#define UCODE_PSM3D_RSPMODE_CULL_COUNTER 0x100
#define UCODE_PSM3D_RSPMODE_CULL_NONE 0x000

#define UCODE_PSM3D_RSPMODE_ZBUF 0x400
#define UCODE_PSM3D_RSPMODE_ZBUF_OFF 0
#define UCODE_PSM3D_RSPMODE_ZBUF_ON 0x400

#define UCODE_PSM3D_RSPMODE_LIGHT 0x800
#define UCODE_PSM3D_RSPMODE_LIGHT_OFF 0
#define UCODE_PSM3D_RSPMODE_LIGHT_ON 0x800

#define UCODE_PSM3D_RSPMODE_SHADE 0x1000
#define UCODE_PSM3D_RSPMODE_SHADE_OFF 0
#define UCODE_PSM3D_RSPMODE_SHADE_ON 0x1000

#define usPSM3DSetRSPMode(mask, data) \
    {\
        _FMT(UCODE_PSM3D_OP_SET_RSP_MODE, 24, 8) | _FMT(mask, 0, 24)\
            ,\
        _FMT(data, 0, 24)\
    }
#define uPSM3DSetRSPMode(dl, mask, data) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(UCODE_PSM3D_OP_SET_RSP_MODE, 24, 8) | _FMT(mask, 0, 24)\
            ,\
        _FMT(data, 0, 24)\
    }

#define usPSM3DSetGeomMode(cull) \
    {\
        _FMT(UCODE_PSM3D_OP_SET_TX_MODE, 24, 8)\
            ,\
        UCODE_PSM3D_TXMODE_TEXTURING_##texturing\
    }
#define uPSM3DSetGeomMode(dl, texturing) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(UCODE_PSM3D_OP_SET_TX_MODE, 24, 8)\
            ,\
        UCODE_PSM3D_TXMODE_TEXTURING_##texturing\
    }


#define usPSM3DFillRectangle(xh, yh, xl, yl) \
    {\
        _FMT(UCODE_PSM3D_OP_RECT, 24, 8) |\
        _FMT(xl, 12, 12) |\
        _FMT(yl, 0, 12),\
            \
        _FMT(xh, 12, 12) |\
        _FMT(yh, 0, 12)\
    }
#define uPSM3DFillRectangle(dl, xh, yh, xl, yl) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(UCODE_PSM3D_OP_RECT, 24, 8) |\
        _FMT(xl, 12, 12) |\
        _FMT(yl, 0, 12),\
            \
        _FMT(xh, 12, 12) |\
        _FMT(yh, 0, 12)\
    }

#define usPSM3DTextureRectangle(xh, yh, xl, yl, sh, th, sl, tl) \
    {\
        _FMT(UCODE_PSM3D_OP_RECT, 24, 8) |\
        _FMT(xl, 12, 12) |\
        _FMT(yl, 0, 12),\
            \
        _FMT(xh, 12, 12) |\
        _FMT(yh, 0, 12)\
    },\
    {\
        _FMT(sh, 16, 16) |\
        _FMT(th, 0, 16),\
            \
        _FMT(sl, 16, 16) |\
        _FMT(tl, 0, 16)\
    }
#define uPSM3DTextureRectangle(dl, xh, yh, xl, yl, sh, th, sl, tl) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(UCODE_PSM3D_OP_RECT, 24, 8) |\
        _FMT(xl, 12, 12) |\
        _FMT(yl, 0, 12),\
            \
        _FMT(xh, 12, 12) |\
        _FMT(yh, 0, 12)\
    };\
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(sh, 16, 16) |\
        _FMT(th, 0, 16),\
            \
        _FMT(sl, 16, 16) |\
        _FMT(tl, 0, 16)\
    }

#define UCODE_PSM3D_LOAD_MTX_PUSH_MULTIPLY 0
#define UCODE_PSM3D_LOAD_MTX_PUSH_LOAD 1 // Transposed

#define UCODE_PSM3D_LOAD_MTX_STACK_PROJECTION 0
#define UCODE_PSM3D_LOAD_MTX_STACK_MODEL 1

#define usPSM3DLoadMtx(addr, pushtype, stack) \
    {\
        _FMT(UCODE_PSM3D_OP_LOAD_MTX, 24, 8) |\
        (UCODE_PSM3D_LOAD_MTX_PUSH_##pushtype << 8) |\
        UCODE_PSM3D_LOAD_MTX_STACK_##stack\
        ,\
            \
        _FMT(addr, 0, 24)\
    }
#define uPSM3DLoadMtx(dl, addr, pushtype, stack) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        (_FMT(UCODE_PSM3D_OP_LOAD_MTX, 24, 8) |\
        UCODE_PSM3D_LOAD_MTX_PUSH_##pushtype << 8) |\
        UCODE_PSM3D_LOAD_MTX_STACK_##stack\
        ,\
            \
        _FMT(addr, 0, 24)\
    }

#define usPSM3DLoadVtx(addr, pos, count) \
    {\
        _FMT(UCODE_PSM3D_OP_LOAD_VTX, 24, 8) |\
        _FMT(pos, 8, 8) |\
        _FMT(count, 0, 8)\
        ,\
            \
        _FMT(addr, 0, 24)\
    }
#define uPSM3DLoadVtx(dl, addr, pos, count) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(UCODE_PSM3D_OP_LOAD_VTX, 24, 8) |\
        _FMT(pos, 8, 8) |\
        _FMT(count, 0, 8)\
        ,\
            \
        _FMT(addr, 0, 24)\
    }

#define usPSM3DTri(vtx1, vtx2, vtx3) \
    {\
        _FMT(UCODE_PSM3D_OP_TRI, 24, 8) |\
        _FMT(vtx1, 16, 8) |\
        _FMT(vtx2, 8, 8) |\
        _FMT(vtx3, 0, 8)\
            ,\
        0\
    }
#define uPSM3DTri(dl, vtx1, vtx2, vtx3) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(UCODE_PSM3D_OP_TRI, 24, 8) |\
        _FMT(vtx1, 16, 8) |\
        _FMT(vtx2, 8, 8) |\
        _FMT(vtx3, 0, 8)\
            ,\
        0\
    }

#define usPSM3DSetVp(vp) \
    {\
        _FMT(UCODE_PSM3D_OP_SET_VP, 24, 8),\
            \
        _FMT(vp, 0, 24)\
    }
#define uPSM3DSetVp(dl, vp) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(UCODE_PSM3D_OP_SET_VP, 24, 8),\
            \
        _FMT(vp, 0, 24)\
    }

#define usPSM3DLoadLights(lights, count) \
    {\
        _FMT(UCODE_PSM3D_OP_LOAD_LIGHTS, 24, 8) |\
        _FMT(count, 0, 8),\
            \
        _FMT(lights, 0, 24)\
    }
#define uPSM3DLoadLights(dl, lights, count) \
    *((dl) ++) = (uPSM3DDispCmd) {\
        _FMT(UCODE_PSM3D_OP_LOAD_LIGHTS, 24, 8) |\
        _FMT(count, 0, 8),\
            \
        _FMT(lights, 0, 24)\
    }


#define usPSM3DPopMtx() { (UCODE_PSM3D_OP_POP_MTX << 24), 0 } 
#define uPSM3DPopMtx(dl) *((dl) ++) = (uPSM3DDispCmd) { _FMT(UCODE_PSM3D_OP_POP_MTX, 24, 8), 0 } 

#define UCODE_PSM3D_BLEND_MODE_M1A_IN 0
#define UCODE_PSM3D_BLEND_MODE_M1A_MEM 1
#define UCODE_PSM3D_BLEND_MODE_M1A_BLEND 2
#define UCODE_PSM3D_BLEND_MODE_M1A_FOG 3

#define UCODE_PSM3D_BLEND_MODE_M1B_IN 0
#define UCODE_PSM3D_BLEND_MODE_M1B_MEM 1
#define UCODE_PSM3D_BLEND_MODE_M1B_BLEND 2
#define UCODE_PSM3D_BLEND_MODE_M1B_FOG 3

#define UCODE_PSM3D_BLEND_MODE_M2A_CCA 0
#define UCODE_PSM3D_BLEND_MODE_M2A_FOGA 1
#define UCODE_PSM3D_BLEND_MODE_M2A_SHADEA 2
#define UCODE_PSM3D_BLEND_MODE_M2A_ZERO 3

#define UCODE_PSM3D_BLEND_MODE_M2B_1MA 0
#define UCODE_PSM3D_BLEND_MODE_M2B_MEMA 1
#define UCODE_PSM3D_BLEND_MODE_M2B_ONE 2
#define UCODE_PSM3D_BLEND_MODE_M2B_ZERO 3

#define usPSM3DSetBlendMode(m1a0, m2a0, m1b0, m2b0, m1a1, m2a1, m1b1, m2b1) \
    usPSM3DSetOtherMode(\
        0x0000, 0xFFFF0000,\
        0,\
        (UCODE_PSM3D_BLEND_MODE_M1A_##m1a0 << 30) | (UCODE_PSM3D_BLEND_MODE_M1A_##m1a1 << 28) |\
        (UCODE_PSM3D_BLEND_MODE_M1B_##m1b0 << 26) | (UCODE_PSM3D_BLEND_MODE_M1B_##m1b1 << 24) |\
        (UCODE_PSM3D_BLEND_MODE_M2A_##m2a0 << 22) | (UCODE_PSM3D_BLEND_MODE_M2A_##m2a1 << 20) |\
        (UCODE_PSM3D_BLEND_MODE_M2B_##m2b0 << 18) | (UCODE_PSM3D_BLEND_MODE_M2B_##m2b1) \
    )
#define uPSM3DSetBlendMode(dl, m1a0, m2a0, m1b0, m2b0, m1a1, m2a1, m1b1, m2b1) \
    uPSM3DSetOtherMode(dl, \
        0x0000, 0xFFFF0000,\
        0,\
        (UCODE_PSM3D_BLEND_MODE_M1A_##m1a0 << 30) | (UCODE_PSM3D_BLEND_MODE_M1A_##m1a1 << 28) |\
        (UCODE_PSM3D_BLEND_MODE_M1B_##m1b0 << 26) | (UCODE_PSM3D_BLEND_MODE_M1B_##m1b1 << 24) |\
        (UCODE_PSM3D_BLEND_MODE_M2A_##m2a0 << 22) | (UCODE_PSM3D_BLEND_MODE_M2A_##m2a1 << 20) |\
        (UCODE_PSM3D_BLEND_MODE_M2B_##m2b0 << 18) | (UCODE_PSM3D_BLEND_MODE_M2B_##m2b1) \
    )


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
#define uPSM3DRdpThrough(dl, opcode, data1, data2) \
    *((dl) ++) = (uPSM3DDispCmd) {\
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
#define uPSM3DSetColorImg(dl, dram_addr, format, size, width) \
    uPSM3DRdpThrough(dl, \
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
#define uPSM3DSetTextureImg(dl, dram_addr, format, size, width) \
    uPSM3DRdpThrough(dl, \
        UCODE_RDP_OPC_Set_Texture_Image,\
        (UCODE_PSM3D_SET_IMAGE_FMT_##format << 21) |\
        (UCODE_PSM3D_SET_IMAGE_SIZE_##size << 19) |\
        (width - 1), \
            \
        dram_addr\
    )

#define usPSM3DSetZImg(dram_addr) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Z_Image,\
        0, \
            \
        dram_addr\
    )
#define uPSM3DSetZImg(dl, dram_addr) \
    uPSM3DRdpThrough(dl, \
        UCODE_RDP_OPC_Set_Z_Image,\
        0, \
            \
        dram_addr\
    )

#define UCODE_PSM3D_SET_TILE_FMT_RGBA 0
#define UCODE_PSM3D_SET_TILE_FMT_YUV 1
#define UCODE_PSM3D_SET_TILE_FMT_CI 2
#define UCODE_PSM3D_SET_TILE_FMT_IA 3
#define UCODE_PSM3D_SET_TILE_FMT_I 4

#define UCODE_PSM3D_SET_TILE_SIZE_4BPP 0
#define UCODE_PSM3D_SET_TILE_SIZE_8BPP 1
#define UCODE_PSM3D_SET_TILE_SIZE_16BPP 2
#define UCODE_PSM3D_SET_TILE_SIZE_32BPP 3

#define usPSM3DSetTile(format, csize, size, tmem_addr, tile, palette, ct, mt, cs, ms, maskt, shiftt, masks, shifts) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Tile,\
        (UCODE_PSM3D_SET_TILE_FMT_##format << 21) |\
        (UCODE_PSM3D_SET_TILE_SIZE_##csize << 19) |\
        (size << 9) |\
        (tmem_addr),\
            \
        (tile << 24) |\
        (palette << 20) |\
        (ct << 19) |\
        (mt << 18) |\
        (maskt << 14) |\
        (shiftt << 10) |\
        (cs << 9) |\
        (ms << 8) |\
        (masks << 4) |\
        (shifts) |\
    )
#define uPSM3DSetTile(dl, format, csize, size, tmem_addr, tile, palette, ct, mt, cs, ms, maskt, shiftt, masks, shifts) \
    uPSM3DRdpThrough(dl, \
        UCODE_RDP_OPC_Set_Tile,\
        (UCODE_PSM3D_SET_TILE_FMT_##format << 21) |\
        (UCODE_PSM3D_SET_TILE_SIZE_##csize << 19) |\
        (size << 9) |\
        (tmem_addr),\
            \
        (tile << 24) |\
        (palette << 20) |\
        (ct << 19) |\
        (mt << 18) |\
        (maskt << 14) |\
        (shiftt << 10) |\
        (cs << 9) |\
        (ms << 8) |\
        (masks << 4) |\
        (shifts)\
    )

#define usPSM3DLoadTile(tile, sh, th, sl, tl) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Load_Tile,\
        (sl << 12) |\
        (tl), \
            \
        (tile << 24) |\
        (sh << 12) |\
        (th)\
    )
#define uPSM3DLoadTile(dl, tile, sh, th, sl, tl) \
    uPSM3DRdpThrough(dl, \
        UCODE_RDP_OPC_Load_Tile,\
        (sl << 12) |\
        (tl), \
            \
        (tile << 24) |\
        (sh << 12) |\
        (th)\
    )

#define usPSM3DSetTileSize(tile, sh, th, sl, tl) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Tile_Size,\
        (sl << 12) |\
        (tl), \
            \
        (tile << 24) |\
        (sh << 12) |\
        (th)\
    )
#define uPSM3DSetTileSize(dl, tile, sh, th, sl, tl) \
    uPSM3DRdpThrough(dl, \
        UCODE_RDP_OPC_Set_Tile_Size,\
        (sl << 12) |\
        (tl), \
            \
        (tile << 24) |\
        (sh << 12) |\
        (th)\
    )

#define usPSM3DSetEnvColor(r, g, b, a) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Env_Color,\
        0,\
        (r << 24) | (g << 16) | (b << 8) | a\
    )
#define uPSM3DSetEnvColor(dl, r, g, b, a) \
    uPSM3DRdpThrough(dl, \
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
#define uPSM3DSetBlendColor(dl, r, g, b, a) \
    uPSM3DRdpThrough(dl, \
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
#define uPSM3DSetFogColor(dl, r, g, b, a) \
    uPSM3DRdpThrough(dl, \
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
#define uPSM3DSetFillColor(dl, color) \
    uPSM3DRdpThrough(dl, \
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
#define uPSM3DSetPrimDepth(dl, z, delta) \
    uPSM3DRdpThrough(dl, \
        UCODE_RDP_OPC_Set_Prim_Depth,\
        0,\
        (z << 16) | (delta << 8)\
    )

#define usPSM3DSyncFull() \
    usPSM3DRdpThrough(\
        dl,\
        UCODE_RDP_OPC_Sync_Full,\
        0,\
        0\
    )
#define uPSM3DSyncFull(dl) \
    uPSM3DRdpThrough(dl, \
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
#define uPSM3DSyncPipe(dl) \
    uPSM3DRdpThrough(\
        dl,\
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
#define uPSM3DSyncLoad(dl) \
    uPSM3DRdpThrough(dl, \
        dl,\
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
#define uPSM3DSetScissor(dl, xh, yh, xl, yl) \
    uPSM3DRdpThrough(dl, \
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
#define uPSM3DSetConvert(dl, k0, k1, k2, k3, k4, k5) \
    uPSM3DRdpThrough(dl, \
        UCODE_RDP_OPC_Set_Convert,\
        ((k2 & 0x1f) << 27) | (k3 << 18) | (k4 << 9) | k5,\
        (k0 << 13) | (k1 << 4) \
    )

#define UCODE_PSM3D_CC_A_COMB 0
#define UCODE_PSM3D_CC_A_TEX0 1
#define UCODE_PSM3D_CC_A_TEX1 2
#define UCODE_PSM3D_CC_A_PRIM 3
#define UCODE_PSM3D_CC_A_SHADE 4
#define UCODE_PSM3D_CC_A_ENV 5
#define UCODE_PSM3D_CC_A_ONE 6
#define UCODE_PSM3D_CC_A_NOISE 7
#define UCODE_PSM3D_CC_A_ZERO 8

#define UCODE_PSM3D_CC_B_COMB 0
#define UCODE_PSM3D_CC_B_TEX0 1
#define UCODE_PSM3D_CC_B_TEX1 2
#define UCODE_PSM3D_CC_B_PRIM 3
#define UCODE_PSM3D_CC_B_SHADE 4
#define UCODE_PSM3D_CC_B_ENV 5
#define UCODE_PSM3D_CC_B_KEYC 6
#define UCODE_PSM3D_CC_B_K4 7
#define UCODE_PSM3D_CC_B_ZERO 8

#define UCODE_PSM3D_CC_C_COMB 0
#define UCODE_PSM3D_CC_C_TEX0 1
#define UCODE_PSM3D_CC_C_TEX1 2
#define UCODE_PSM3D_CC_C_PRIM 3
#define UCODE_PSM3D_CC_C_SHADE 4
#define UCODE_PSM3D_CC_C_ENV 5
#define UCODE_PSM3D_CC_C_KEYS 6
#define UCODE_PSM3D_CC_C_COMBA 7
#define UCODE_PSM3D_CC_C_TEX0A 8
#define UCODE_PSM3D_CC_C_TEX1A 9
#define UCODE_PSM3D_CC_C_PRIMA 10
#define UCODE_PSM3D_CC_C_SHADEA 11
#define UCODE_PSM3D_CC_C_ENVA 12
#define UCODE_PSM3D_CC_C_LOD 13
#define UCODE_PSM3D_CC_C_PRLOD 14
#define UCODE_PSM3D_CC_C_K5 15
#define UCODE_PSM3D_CC_C_ZERO 16

#define UCODE_PSM3D_CC_D_COMB 0
#define UCODE_PSM3D_CC_D_TEX0 1
#define UCODE_PSM3D_CC_D_TEX1 2
#define UCODE_PSM3D_CC_D_PRIM 3
#define UCODE_PSM3D_CC_D_SHADE 4
#define UCODE_PSM3D_CC_D_ENV 5
#define UCODE_PSM3D_CC_D_ONE 6
#define UCODE_PSM3D_CC_D_ZERO 7

#define UCODE_PSM3D_AC_A_COMB 0
#define UCODE_PSM3D_AC_A_TEX0 1
#define UCODE_PSM3D_AC_A_TEX1 2
#define UCODE_PSM3D_AC_A_PRIM 3
#define UCODE_PSM3D_AC_A_SHADE 4
#define UCODE_PSM3D_AC_A_ENV 5
#define UCODE_PSM3D_AC_A_ONE 6
#define UCODE_PSM3D_AC_A_ZERO 7

#define UCODE_PSM3D_AC_B_COMB 0
#define UCODE_PSM3D_AC_B_TEX0 1
#define UCODE_PSM3D_AC_B_TEX1 2
#define UCODE_PSM3D_AC_B_PRIM 3
#define UCODE_PSM3D_AC_B_SHADE 4
#define UCODE_PSM3D_AC_B_ENV 5
#define UCODE_PSM3D_AC_B_ONE 6
#define UCODE_PSM3D_AC_B_ZERO 7

#define UCODE_PSM3D_AC_C_LOD 0
#define UCODE_PSM3D_AC_C_TEX0 1
#define UCODE_PSM3D_AC_C_TEX1 2
#define UCODE_PSM3D_AC_C_PRIM 3
#define UCODE_PSM3D_AC_C_SHADE 4
#define UCODE_PSM3D_AC_C_ENV 5
#define UCODE_PSM3D_AC_C_PRLOD 6
#define UCODE_PSM3D_AC_C_ZERO 7

#define UCODE_PSM3D_AC_D_COMB 0
#define UCODE_PSM3D_AC_D_TEX0 1
#define UCODE_PSM3D_AC_D_TEX1 2
#define UCODE_PSM3D_AC_D_PRIM 3
#define UCODE_PSM3D_AC_D_SHADE 4
#define UCODE_PSM3D_AC_D_ENV 5
#define UCODE_PSM3D_AC_D_ONE 6
#define UCODE_PSM3D_AC_D_ZERO 7

#define usPSM3DSetCombineMode(cca0, ccb0, ccc0, ccd0, aca0, acb0, acc0, acd0, cca1, ccb1, ccc1, ccd1, aca1, acb1, acc1, acd1) \
    usPSM3DRdpThrough(\
        UCODE_RDP_OPC_Set_Combine_Mode,\
        (UCODE_PSM3D_CC_A_##cca0 << 20) |\
        (UCODE_PSM3D_CC_C_##ccc0 << 15) |\
        (UCODE_PSM3D_AC_A_##aca0 << 12) |\
        (UCODE_PSM3D_AC_C_##acc0 << 9) |\
        (UCODE_PSM3D_CC_A_##cca1 << 5) |\
        (UCODE_PSM3D_CC_C_##ccc1),\
            \
        (UCODE_PSM3D_CC_B_##ccb0 << 28) |\
        (UCODE_PSM3D_CC_B_##ccb1 << 24) |\
        (UCODE_PSM3D_AC_A_##aca1 << 21) |\
        (UCODE_PSM3D_AC_C_##acc1 << 18) |\
        (UCODE_PSM3D_CC_D_##ccd0 << 15) |\
        (UCODE_PSM3D_AC_B_##acb0 << 12) |\
        (UCODE_PSM3D_AC_D_##acd0 << 9) |\
        (UCODE_PSM3D_CC_D_##ccd1 << 6) |\
        (UCODE_PSM3D_AC_B_##acb1 << 3) |\
        (UCODE_PSM3D_AC_D_##acd1)\
    )

#define uPSM3DSetCombineMode(dl, cca0, ccb0, ccc0, ccd0, aca0, acb0, acc0, acd0, cca1, ccb1, ccc1, ccd1, aca1, acb1, acc1, acd1) \
    uPSM3DRdpThrough(dl, \
        UCODE_RDP_OPC_Set_Combine_Mode,\
        (UCODE_PSM3D_CC_A_##cca0 << 20) |\
        (UCODE_PSM3D_CC_C_##ccc0 << 15) |\
        (UCODE_PSM3D_AC_A_##aca0 << 12) |\
        (UCODE_PSM3D_AC_C_##acc0 << 9) |\
        (UCODE_PSM3D_CC_A_##cca1 << 5) |\
        (UCODE_PSM3D_CC_C_##ccc1),\
            \
        (UCODE_PSM3D_CC_B_##ccb0 << 28) |\
        (UCODE_PSM3D_CC_B_##ccb1 << 24) |\
        (UCODE_PSM3D_AC_A_##aca1 << 21) |\
        (UCODE_PSM3D_AC_C_##acc1 << 18) |\
        (UCODE_PSM3D_CC_D_##ccd0 << 15) |\
        (UCODE_PSM3D_AC_B_##acb0 << 12) |\
        (UCODE_PSM3D_AC_D_##acd0 << 9) |\
        (UCODE_PSM3D_CC_D_##ccd1 << 6) |\
        (UCODE_PSM3D_AC_B_##acb1 << 3) |\
        (UCODE_PSM3D_AC_D_##acd1)\
    )

#define UCODE_PSM3D_Z_SRC_PRIM 1
#define UCODE_PSM3D_Z_SRC_PIXEL 0

#define UCODE_PSM3D_Z_WRITE_ON 1
#define UCODE_PSM3D_Z_WRITE_OFF 0

#define UCODE_PSM3D_Z_COMPARE_ON 1
#define UCODE_PSM3D_Z_COMPARE_OFF 0

#define usPSM3DSetZMode(src, write, compare) \
    usPSM3DSetOtherMode(\
        0x0, 0x34,\
        0x0,\
        (UCODE_PSM3D_Z_SRC_##src << 2)|\
        (UCODE_PSM3D_Z_WRITE_##write << 5)|\
        (UCODE_PSM3D_Z_COMPARE_##compare << 4)\
    )
#define uPSM3DSetZMode(dl, src, write, compare) \
    uPSM3DSetOtherMode(dl, \
        0x0, 0x34,\
        0x0,\
        (UCODE_PSM3D_Z_SRC_##src << 2)|\
        (UCODE_PSM3D_Z_WRITE_##write << 5)|\
        (UCODE_PSM3D_Z_COMPARE_##compare << 4)\
    )

#define UCODE_PSM3D_IMAGE_READ_ON 1
#define UCODE_PSM3D_IMAGE_READ_OFF 0

#define usPSM3DSetImageReadMode(mode) \
    usPSM3DSetOtherMode(\
        0x0, 0x40,\
        0x0,\
        (UCODE_PSM3D_IMAGE_READ_##mode << 6)\
    )
#define uPSM3DSetImageReadMode(dl, mode) \
    uPSM3DSetOtherMode(dl, \
        0x0, 0x40,\
        0x0,\
        (UCODE_PSM3D_IMAGE_READ_##mode << 6)\
    )

#define UCODE_PSM3D_CYCLE_TYPE_1CYC 0
#define UCODE_PSM3D_CYCLE_TYPE_2CYC 1
#define UCODE_PSM3D_CYCLE_TYPE_COPY 2
#define UCODE_PSM3D_CYCLE_TYPE_FILL 3

#define usPSM3DSetCycleType(type)\
    usPSM3DSetOtherMode(\
        0x300000, 0x0,\
        UCODE_PSM3D_CYCLE_TYPE_##type << 20,\
        0x0\
    )
#define uPSM3DSetCycleType(dl, type)\
    uPSM3DSetOtherMode(dl, \
        0x300000, 0x0,\
        UCODE_PSM3D_CYCLE_TYPE_##type << 20,\
        0x0\
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
