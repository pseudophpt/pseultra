/*
 * pseultra/n64/ucode/include/ucode/rdp.h
 * RDP Header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/ucode/rdp.h
 * @brief RDP Header 
 * @date 20 Aug 2018
 * @author pseudophpt
 *
 * @todo Add triangle RDP commands
 *
 * This file defines macros related to the RDP 
 */

#ifndef UCODE_RDP_H_GUARD
#define UCODE_RDP_H_GUARD

#define UCODE_RDP_OPC_Set_Color_Image 0x3f
#define UCODE_RDP_OPC_Set_Texture_Image 0x3d
#define UCODE_RDP_OPC_Set_Z_Image 0x3e
#define UCODE_RDP_OPC_Set_Tile 0x35
#define UCODE_RDP_OPC_Load_Tile 0x34
#define UCODE_RDP_OPC_Load_Block 0x33
#define UCODE_RDP_OPC_Set_Tile_Size 0x32
#define UCODE_RDP_OPC_Load_Tlut 0x30
#define UCODE_RDP_OPC_Fill_Rectangle 0x36
#define UCODE_RDP_OPC_Texture_Rectangle 0x24
#define UCODE_RDP_OPC_Texture_Rectangle_Flip 0x25
#define UCODE_RDP_OPC_Set_Combine_Mode 0x3c
#define UCODE_RDP_OPC_Set_Other_Modes 0x2f
#define UCODE_RDP_OPC_Set_Env_Color 0x3b
#define UCODE_RDP_OPC_Set_Prim_Color 0x3a
#define UCODE_RDP_OPC_Set_Blend_Color 0x39
#define UCODE_RDP_OPC_Set_Fog_Color 0x38
#define UCODE_RDP_OPC_Set_Fill_Color 0x37
#define UCODE_RDP_OPC_Set_Prim_Depth 0x3c

#endif
