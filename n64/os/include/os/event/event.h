/*
 * pseultra/n64/os/include/os/event/event.h
 * Event header 
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file include/os/event/event.h
 * @brief Event handling headers
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides definitions for structs and constants related to the handling of OS events
 */

#ifndef OS_EVENT_EVENT_H_GUARD
#define OS_EVENT_EVENT_H_GUARD

/*
 * Macros
 */

/** @brief Type for an event which is added to the main queue on an SP interrupt */
#define OS_EVENT_TYPE_SP 0 
/** @brief Type for an event which is added to the main queue on a DP interrupt */
#define OS_EVENT_TYPE_DP 1
/** @brief Type for an event which is added to the main queue on an SI interrupt */
#define OS_EVENT_TYPE_SI 2 
/** @brief Type for an event which is added to the main queue on a VI interrupt */
#define OS_EVENT_TYPE_VI 3 
/** @brief Type for an event which is added to the main queue on a PI interrupt */
#define OS_EVENT_TYPE_PI 4 
/** @brief Type for an event which is added to the main queue on an AI interrupt */
#define OS_EVENT_TYPE_AI 5 
/** @brief Type for an event which is added to the main queue directly */
#define OS_EVENT_TYPE_MAIN 8 // User scheduled events
/** @brief Type for an event which is never executed */
#define OS_EVENT_TYPE_NONE 255 // No event (used if no event could be dequeued)
/** @brief Size for OS defined event queues */
#define OS_EVENT_QUEUE_SIZE 32

/*
 * Structs
 */

#ifndef __asm__

/** @brief Struct describing an OS event */
typedef struct OSEvent_t {
    /** @brief Callback associated with the execution of this event */
    void (*callback) (void); 
    /** @brief Type of event */
    u8 type; 
} OSEvent;

/** @brief Struct describing a circular FIFO queue of OS events */
typedef struct OSEventQueue_t {
    /** @brief An array of events on the queue */
    OSEvent queue [OS_EVENT_QUEUE_SIZE];
    /** @brief The index of the first element on the queue */ 
    int start;
    /** @brief The index after the last element on the queue */
    int end; 
} OSEventQueue;

#endif

/*
 * Public functions
 */

#ifdef __asm__
.extern osScheduleEvent
#else
void osScheduleEvent (OSEvent event);
#endif

/*
 * Public variables
 */

#ifdef __os_internal__

/*
 * Internal functions
 */

#ifdef __asm__
.extern __osEnqueueEvent
#else
void __osEnqueueEvent (OSEvent event, OSEventQueue *queue);
#endif

#ifdef __asm__
.extern __osDequeueEvent
#else
OSEvent __osDequeueEvent (OSEventQueue *queue);
#endif

#ifdef __asm__
.extern __osCopyEventQueue 
#else
void __osCopyEventQueue (OSEventQueue *src, OSEventQueue *dest);
#endif

/*
 * Internal variables
 */

#ifdef __asm__
.extern __osMainEventQueue
#else
extern OSEventQueue __osMainEventQueue;
#endif

#ifdef __asm__
.extern __osInterruptEventQueue
#else
extern OSEventQueue __osInterruptEventQueue [];
#endif

#endif

#endif
