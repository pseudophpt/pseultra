/*
 * pseultra/n64/ucode/include/ucode/rsp.h
 * RSP Header
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/ucode/rsp.h
 * @brief RSP Header 
 * @date 20 Aug 2018
 * @author pseudophpt
 *
 * This file defines macros related to the RSP 
 */

#ifndef UCODE_RSP_H_GUARD
#define UCODE_RSP_H_GUARD

/*
 * RSP COP0 Registers
 */
#ifdef __asm__

#define DMA_CACHE $0
#define DMA_DRAM $1
#define DMA_READ_LENGTH $2
#define DMA_WRITE_LENGTH $3
#define SP_STATUS $4
#define DMA_FULL $5
#define DMA_BUSY $6
#define SP_RESERVED $7
#define CMD_START $8
#define CMD_END $9
#define CMD_CURRENT $10
#define CMD_STATUS $11
#define CMD_CLOCK $12
#define CMD_BUSY $13
#define CMD_PIPE_BUSY $14
#define CMD_TMEM_BUSY $15

#endif

/*
 * RSP specific instruction definitions
 */
#ifdef __asm__

#endif

#endif
