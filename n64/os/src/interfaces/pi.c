/*
 * pseultra/n64/os/src/interfaces/pi.c
 * Parallel interface
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/interfaces/pi.c
 * @brief Parallel interface
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines for the parallel interface (PI)
 */

#include <os_priv.h>

/**
 * @brief Synchronous PI DMA
 * @date 3 Aug 2018
 * @author pseudophpt
 * @param[in] src Pointer to source location (in the cartridge domain)
 * @param[out] dest Pointer to destination location (in RDRAM)
 * @param[in] size Size in bytes of region to DMA
 *
 * This function starts a synchronized parallel interface DMA to copy data from cartridge to RDRAM.
 *
 * @note The asynchronous version of this function should be preferred whenever possible to allow for further processing during the DMA
 * @note The source and destination pointers are not addressed in K0, they are physical
 * @note The developer must make sure that all current DMA's are finished, sync or async
 * @note When the DMA finishes, a PI interrupt will be triggered, regardless of the DMA being sync or async. As such, any events schedules for the PI will be copied to the main event queue as a result
 */
void
osPiSyncDma
(void *src, void *dest, int size) {
    // Source and destination
    *(u32 *)N64_PI_DRAM_ADDR_REG = (u32)dest;
    *(u32 *)N64_PI_CART_ADDR_REG = (u32)src;

    // Write
    *(u32 *)N64_PI_WR_LEN_REG = size - 1;

    // Poll status register
    while (*(u32 *)N64_PI_STATUS_REG && 0x01);
}

/**
 * @brief Asynchronous PI DMA
 * @date 3 Aug 2018
 * @author pseudophpt
 * @param[in] src Pointer to source location (in the cartridge domain)
 * @param[out] dest Pointer to destination location (in RDRAM)
 * @param[in] size Size in bytes of region to DMA
 *
 * This function starts an asynchronous parallel interface DMA to copy data from cartridge to RDRAM. 
 *
 * @note All events that respond to the finishing of an async DMA should be scheduled before this function is called, since the DMA may finish before any of the events are scheduled 
 * @note The source and destination pointers are not addressed in K0, they are physical
 * @note The developer must make sure that all current DMA's are finished, sync or async
 * @note When the DMA finishes, a PI interrupt will be triggered, regardless of the DMA being sync or async. As such, any events schedules for the PI will be copied to the main event queue as a result
 */
void
osPiAsyncDma
(void *src, void *dest, int size) {
    // Source and destination
    *(u32 *)N64_PI_DRAM_ADDR_REG = (u32)dest;
    *(u32 *)N64_PI_CART_ADDR_REG = (u32)src;

    // Write
    *(u32 *)N64_PI_WR_LEN_REG = size - 1;
}
