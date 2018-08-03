/*
 * pseultra/n64/os/src/event/event.c
 * Event related code
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/event/event.c
 * @brief Event handling routines
 * @date 1 Aug 2018
 * @author pseudophpt
 * @todo Add methods for the creation of event queues, which initialize the start and end positions
 *
 * This file provides routines for the creation and scheduling of events 
 */

#include <os_priv.h>

/** @internal @brief Queue of events from which the main loop executes */
OSEventQueue __osMainEventQueue;

/** @internal @brief Queues of events to be added to the main event queue when a certain interrupt occurs */
OSEventQueue __osInterruptEventQueue [INT_RCP_COUNT];

/**
 * @brief Schedules an event for processing
 * @param[in] event Event to schedule
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function schedules an event for processing by placing it on the queue which corresponds to the OSEvent type value. If one of the RCP interrupt types are specified, they are placed on the corresponding queue to be copied to the main queue when that interrupt fires. If the main type is specified, the event is immediately schedules on the main event queue.
 *
 */
void 
osScheduleEvent 
(OSEvent event) {
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

/**
 * @internal
 * @brief Adds an event to the specified event queue 
 * @param[in] event Event to schedule
 * @param[in,out] queue Pointer to the event queue to enqueue to
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function places the event specified at the end of the event queue
 *
 * @see __osDequeueEvent
 */
void 
__osEnqueueEvent 
(OSEvent event, OSEventQueue *queue) {
    // Is there space? If not, return
    if ((queue->end + 1) % OS_EVENT_QUEUE_SIZE == queue->start) {
        return;
    }

    // Put new event in queue
    queue->queue[queue->end] = event;
    
    // Update queue end
    queue->end = (queue->end + 1) % OS_EVENT_QUEUE_SIZE;
}

/**
 * @internal
 * @brief Removes an event from the specified event queue 
 * @param[in,out] queue Pointer to the event queue to dequeue from
 * @return Event at the front of the queue
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function removes an event from the front of the event queue and returns it. If the queue holds no events, it will return an event with type OS_EVENT_TYPE_NONE.
 *
 * @see __osEnqueueEvent
 */
OSEvent 
__osDequeueEvent
(OSEventQueue *queue) {
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

/**
 * @internal
 * @brief Removes the events from a source queue and places them at the end of a destination queue 
 * @param[in,out] src 
 * @param[in,out] dest
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function removes the events from a source queue, specified in the src parameter, and places them at the end of the destination queue.  
 */
void 
__osCopyEventQueue
(OSEventQueue *src, OSEventQueue *dest) {
    while (src->start != src->end) {
        __osEnqueueEvent(__osDequeueEvent(src), dest);
    }
}
