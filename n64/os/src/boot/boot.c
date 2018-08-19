/*
 * pseultra/n64/os/src/boot/boot.c
 * OS boot code
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/boot/boot.c
 * @brief Boot routines 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines for the boot process
 */

#include <os_priv.h>

extern void main (void);

/**
 * @internal
 * @brief OS boot functions
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function is called when the OS boots. It first initializes exceptions using __osInitExceptions(), then schedules the main function (which is defined by the developer) onto the main event queue). Finally, it enters the main event loop, in which it polls for events on the main event queue and executes them. 
 *
 * @see __osInitExceptions()
 */
void 
__osBoot
() {
    // Initialize PIF
    __osInitPif();
    
    // Initialize exceptions
    __osInitExceptions();

    // Add main process to event queue
    OSEvent main_event;

    main_event.callback = main;
    main_event.type = OS_EVENT_TYPE_MAIN;

    osScheduleEvent(main_event);

    // Main event loop 
    while (1) {
        OSEvent event = __osDequeueEvent(&__osMainEventQueue);

        if (event.type != OS_EVENT_TYPE_NONE) {
            (*(event.callback))();
        }
    }
}


