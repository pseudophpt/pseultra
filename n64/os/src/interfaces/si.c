/*
 * pseultra/n64/os/src/interfaces/si.c
 * Serial interface
 * 
 * (C) pseudophpt 2019 
 */

/**
 * @file src/interfaces/si.c
 * @brief Video interface
 * @date 3 Jul 2019
 * @author pseudophpt
 *
 * This file provides routines for the serial interface (SI)
 */

#include <os_priv.h>

/** @internal @brief Buffer that is copied to and from PIFRAM on SI read/writes */ 
u8 __osSiBuffer [64];

/**
 * @internal
 *
 * @brief SI Write
 * @date 4 Jul 2019
 * @author pseudophpt
 *
 * This function starts an asynchronous serial interface DMA to copy 64 bytes of data from RDRAM to PIFRAM. 
 *
 * @note All events that respond to the finishing of an async DMA should be scheduled before this function is called, since the DMA may finish before any of the events are scheduled 
 * @note The source pointer is not addressed in K0, they are physical
 * @note The developer must make sure that all current SI DMA's are finished, sync or async
 * @note When the DMA finishes, a SI interrupt will be triggered. As such, any events scheduled for the PI will be copied to the main event queue as a result
 */
void
__osSiWrite
() {
    // Source and destination
    *(u32 *)N64_KSEG1_ADDR(N64_SI_DRAM_ADDR_REG) = N64_TO_PHYS((u32)&__osSiBuffer);

    // Write
    *(u32 *)N64_KSEG1_ADDR(N64_SI_PIF_ADDR_WR64B_REG) = N64_PIF_RAM_START;
}

/**
 * @internal
 *
 * @brief SI Read
 * @date 4 Jul 2019
 * @author pseudophpt
 *
 * This function starts an asynchronous serial interface DMA to copy 64 bytes of data from PIFRAM to RDRAM. 
 *
 * @note All events that respond to the finishing of an async DMA should be scheduled before this function is called, since the DMA may finish before any of the events are scheduled 
 * @note The source pointer is not addressed in K0, they are physical
 * @note The developer must make sure that all current SI DMA's are finished, sync or async
 * @note When the DMA finishes, a SI interrupt will be triggered. As such, any events scheduled for the PI will be copied to the main event queue as a result
 */
void
__osSiRead
() {
    // Source and destination
    *(u32 *)N64_KSEG1_ADDR(N64_SI_DRAM_ADDR_REG) = N64_TO_PHYS((u32)&__osSiBuffer);

    // Write
    *(u32 *)N64_KSEG1_ADDR(N64_SI_PIF_ADDR_RD64B_REG) = N64_PIF_RAM_START;
}

/**
 * @brief Start SI peripheral read task
 * @date 4 Jul 2019
 * @author pseudophpt
 *
 * @param[in] controllers Amount of controllers to read data from
 *
 * This function writes a task to the PIF for processing peripheral data. After this command, further processing should occur until no more is left over or until controller data is absolutely necessary. At that point, one should call osSiWaitTask to do a synchronous wait for processing to finish.
 *
 * @note Undefined behavior will occur if controllers is less than zero or greater than four.
 */
void
osSiStartTask
(int controllers)
{
    u32 *task_ptr = (u32 *)(N64_KSEG1_ADDR((u32)&__osSiBuffer));

    // Write task for each controller
    for (int i = 0; i < controllers; i ++)
    {
        // Read controller from selected channel
        *(task_ptr) = 0xFF010401;
        *(task_ptr + 1) = 0xFFFFFFFF;
        task_ptr += 2;
    }
    
    // End task command
    *task_ptr = 0xFE000000;

    // Write status byte as 1 to signal PIF to start processing task
    *(u8 *)N64_KSEG1_ADDR((u32)&__osSiBuffer[63]) = 1;

    // Write task
    __osSiWrite();
}

/**
 * @brief Wait for SI peripheral read task
 * @date 4 Jul 2019
 * @author pseudophpt
 *
 * This function performs a sync wait for the started SI peripheral task to finish. After waiting, an SI DMA read is performed, which once finished allows for data to be read via osSiReadData.
 *
 * @note If the DMA activated in osSiStartTask is not finished when this is called, undefined behavior will occur. As such, one should wait for the SI DMA to finish before calling this wait.
 */
void
osSiWaitTask
()
{
    // Wait for 
    while(*(u8 *)N64_KSEG1_ADDR(N64_PIF_RAM_START + 63) & 0x01);

    // Read 
    __osSiRead();
}

/**
 * @brief Read SI controller data
 * @date 4 Jul 2019
 * @author pseudophpt
 *
 * @param[out] controllers Array of controllers to read data into. Should be the same size as the amount of controllers read in.
 *
 * This function reads data from the SI after performing osSiStartTask and waiting for it to finish with osSiWaitTask. 
 *
 */

void
osSiReadData
(OSCont controllers [])
{
    u32 *task_ptr = (u32 *)(N64_KSEG1_ADDR((u32)&__osSiBuffer));
    int controller_no = 0; 

    // While we haven't read all controllers
    while(*task_ptr != 0xFE000000) {
        controllers[controller_no] = *(OSCont *)(task_ptr + 1); // Read in data as OSCont struct
        controllers[controller_no].err = (*(task_ptr) >> 8) & OS_SI_ERROR_MASK; // Write error code

        controller_no ++;
        task_ptr += 2;
    }
}
