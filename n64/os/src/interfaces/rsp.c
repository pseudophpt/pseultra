/*
 * pseultra/n64/os/src/interfaces/rsp.c
 * RSP interface
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/interfaces/rsp.c
 * @brief RSP interface
 * @date 20 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines for the RSP
 */

#include <os_priv.h>

/**
 * @brief Load microcode into RSP
 * @date 20 Aug 2018
 * @author pseudophpt
 * @param[in] ucode_start Pointer to the start of the microcode to copy 
 * @param[in] ucode_end Pointer to the end of the microcode to copy
 *
 * This function performs a microcode DMA into RSP IMEM in preparation for execution of a graphics task
 *
 * @note One must be careful not to load microcode into the RSP while a task is currently executing or microcode is being loaded. Wait for an SP interrupt before loading more microcode or starting a new task
 */
void
osRspLoadUCode
(void *ucode_start, void *ucode_end) {
    // Wait for any SP DMAs to finish
    while (*(u32 *)N64_KSEG1_ADDR(N64_SP_STATUS_REG) & 
            (N64_SP_STATUS_REG_DMA_BUSY |
             N64_SP_STATUS_REG_DMA_FULL |
             N64_SP_STATUS_REG_IO_FULL));

    // Make sure SP is halted
    *(u32 *)N64_KSEG1_ADDR(N64_SP_STATUS_REG) = N64_SP_STATUS_REG_SET_HALT;

    // Load into IMEM at 0
    *(u32 *)N64_KSEG1_ADDR(N64_SP_MEM_ADDR_REG) = N64_SP_MEM_ADDR_REG_IMEM | N64_SP_MEM_ADDR_REG_ADDR(0);
    
    // Load from RDRAM at ucode_start
    *(u32 *)N64_KSEG1_ADDR(N64_SP_DRAM_ADDR_REG) = N64_SP_DRAM_ADDR_REG_ADDR((u32)ucode_start);
    
    // DMA length of ucode into IMEM
    *(u32 *)N64_KSEG1_ADDR(N64_SP_RD_LEN_REG) = 
        N64_SP_RD_LEN_REG_LENGTH((u32)ucode_end - (u32)ucode_start - 1) |
        N64_SP_RD_LEN_REG_COUNT(0) |
        N64_SP_RD_LEN_REG_SKIP(0);

    // Wait for this DMA to finish
    while (*(u32 *)N64_KSEG1_ADDR(N64_SP_STATUS_REG) & 
            (N64_SP_STATUS_REG_DMA_BUSY |
             N64_SP_STATUS_REG_DMA_FULL |
             N64_SP_STATUS_REG_IO_FULL));
}

/**
 * @brief Begin RSP task 
 * @date 20 Aug 2018
 * @author pseudophpt
 *
 * This function starts an RSP task 
 *
 * @note Microcode must be loaded via osRspLoadUCode() before starting an RSP task
 * @note One must be careful not to start a new task into the RSP while a task is currently executing or microcode is being loaded. Wait for an SP interrupt before loading more microcode or starting a new task
 * 
 * @see osRspLoadUCode
 */
void
osRspStartTask
() {
    // Set halt bit, clear broke bit, set interrupt on break
    *(u32 *)N64_KSEG1_ADDR(N64_SP_STATUS_REG) = 
        N64_SP_STATUS_REG_SET_HALT |
        N64_SP_STATUS_REG_CLEAR_BROKE |
        N64_SP_STATUS_REG_SET_INTR_ON_BREAK;

    // Reset PC
    *(u32 *)N64_KSEG1_ADDR(N64_SP_PC_REG) = 0;

    // Clear halt bit
    *(u32 *)N64_KSEG1_ADDR(N64_SP_STATUS_REG) = N64_SP_STATUS_REG_CLEAR_HALT;
}
