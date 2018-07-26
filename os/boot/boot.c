/*
 * pseultra/os/boot/boot.c
 * OS boot code
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

extern void __osInitExceptions (void);
extern OSEvent *__osDequeueEvent (void);
extern void main (void);

void __osBoot () {
    // Initialize exceptions
    __osInitExceptions();

    // Add main process to event queue
    OSEvent main_event;

    main_event.next = NULL;
    main_event.callback = main;
    main_event.type = OS_EVENT_TYPE_OTHER;

    osScheduleEvent(&main_event);

    // Main event loop 
    while (1) {
        OSEvent *event;
        while ((event = __osDequeueEvent()) != NULL) {
            // Execute callback
            (*(event->callback))();
        }
    }
}


