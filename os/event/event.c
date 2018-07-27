/*
 * pseultra/os/event/event.c
 * Event related code
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

extern void __osEnqueueEvent (OSEvent *event, OSEvent **queue);
extern OSEvent *__osDequeueEvent (void);

// A queue is a linked list of events

// Main queue from which the main game process executes
OSEvent *__osMainEventQueue = NULL;

// Interrupt queues
OSEvent *__osInterruptEventQueue [INT_RCP_COUNT];

// Schedule event for processing
void osScheduleEvent (OSEvent *event) {
    switch (event->type) {
    case OS_EVENT_TYPE_SP:
        __osEnqueueEvent(event, &__osInterruptEventQueue [INT_RCP_CAUSE_SP]);
        break;
    case OS_EVENT_TYPE_DP:
        __osEnqueueEvent(event, &__osInterruptEventQueue [INT_RCP_CAUSE_DP]);
        break;
    case OS_EVENT_TYPE_SI:
        __osEnqueueEvent(event, &__osInterruptEventQueue [INT_RCP_CAUSE_SI]);
        break;
    case OS_EVENT_TYPE_VI:
        __osEnqueueEvent(event, &__osInterruptEventQueue [INT_RCP_CAUSE_VI]);
        break;
    case OS_EVENT_TYPE_PI:
        __osEnqueueEvent(event, &__osInterruptEventQueue [INT_RCP_CAUSE_PI]);
        break;
    case OS_EVENT_TYPE_AI:
        __osEnqueueEvent(event, &__osInterruptEventQueue [INT_RCP_CAUSE_AI]);
        break;
    case OS_EVENT_TYPE_MAIN:
        __osEnqueueEvent(event, &__osMainEventQueue);
        break;
    }
}

// Put event at end of queue
void __osEnqueueEvent (OSEvent *event, OSEvent **queue) {
    // Traverse linked list
    OSEvent *current_event = *queue;

    if (current_event == NULL) {
        *queue = event;
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
