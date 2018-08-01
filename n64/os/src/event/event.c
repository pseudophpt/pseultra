/*
 * pseultra/n64/os/src/event/event.c
 * Event related code
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

void __osEnqueueEvent (OSEvent event, OSEventQueue *queue);
OSEvent __osDequeueEvent (OSEventQueue *queue);
void __osCopyEventQueue (OSEventQueue *src, OSEventQueue *dest);

// Main queue from which the main game process executes
OSEventQueue __osMainEventQueue;

// Interrupt queues
OSEventQueue __osInterruptEventQueue [INT_RCP_COUNT];

// Schedule event for processing
void osScheduleEvent (OSEvent event) {
    switch (event.type) {
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
void __osEnqueueEvent (OSEvent event, OSEventQueue *queue) {
    // Is there space? If not, return
    if ((queue->end + 1) % OS_EVENT_QUEUE_SIZE == queue->start) {
        return;
    }

    // Put new event in queue
    queue->queue[queue->end] = event;
    
    // Update queue end
    queue->end = (queue->end + 1) % OS_EVENT_QUEUE_SIZE;
}

// Get event on front of the queue and remove it
OSEvent __osDequeueEvent (OSEventQueue *queue) {
    // Is there an event in the queue?
    if (queue->end == queue->start) {
        OSEvent no_event;
        no_event.type = OS_EVENT_TYPE_NONE;

        return no_event;
    }

    // Take event from front
    OSEvent event = queue->queue[queue->start];

    // Increment start
    queue->start = (queue->start + 1) % OS_EVENT_QUEUE_SIZE;

    return event;
}

// Copy one queue to the end of another
void __osCopyEventQueue (OSEventQueue *src, OSEventQueue *dest) {
    while (src->start != src->end) {
        __osEnqueueEvent(__osDequeueEvent(src), dest);
    }
}
