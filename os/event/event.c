/*
 * pseultra/os/event/event.c
 * Event related code
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

// Linked list of events
OSEvent *__osMainEventQueue = NULL;

// Place event on the main queue
void osScheduleEvent (OSEvent *event) {
    // Traverse linked list
    OSEvent *current_event = __osMainEventQueue;

    if (current_event == NULL) {
        __osMainEventQueue = event;
        return;
    }

    while (current_event->next != NULL) {
        current_event = current_event->next;
    }

    // Insert
    current_event->next = event;
}

// Get event on front of the queue and remove it
OSEvent *__osDequeueEvent (void) {
    if (__osMainEventQueue == NULL) {
        return NULL;
    }

    OSEvent *front_event = __osMainEventQueue;
    __osMainEventQueue = __osMainEventQueue->next;
    return front_event;
}
