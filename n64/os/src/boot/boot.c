/*
 * pseultra/n64/os/src/boot/boot.c
 * OS boot code
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

extern OSEventQueue __osMainEventQueue;

extern void __osInitExceptions (void);
extern OSEvent __osDequeueEvent (OSEventQueue *queue);
extern void main (void);

void __osBoot () {
    // Initialize exceptions
    __osInitExceptions();

    // Add main process to event queue
    OSEvent main_event;

    main_event.callback = main;
    main_event.type = OS_EVENT_TYPE_MAIN;

    osScheduleEvent(main_event);

    // Main event loop 
    while (1) {
/*        OSEvent event = __osDequeueEvent(&__osMainEventQueue);
        while (event.type == OS_EVENT_TYPE_NONE) {
            // Execute callback
            (*(event.callback))();
        
            // Get another event
            event = __osDequeueEvent(&__osMainEventQueue);
        }*/
        OSEvent event = __osDequeueEvent(&__osMainEventQueue);

        if (event.type != OS_EVENT_TYPE_NONE) {
            (*(event.callback))();
        }
    }
}


