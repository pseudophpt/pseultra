/*
 * pseultra/headers/os/event/event.h
 * Event header 
 * 
 * (C) pseudophpt 2018 
 */

#ifndef OS_EVENT_EVENT_H_GUARD
#define OS_EVENT_EVENT_H_GUARD

typedef struct OSEvent_t {
    void (*callback) (void); // Execute this event
    u8 type; // Type of event
} OSEvent;

#define OS_EVENT_TYPE_SP 0 
#define OS_EVENT_TYPE_DP 1
#define OS_EVENT_TYPE_SI 2 
#define OS_EVENT_TYPE_VI 3 
#define OS_EVENT_TYPE_PI 4 
#define OS_EVENT_TYPE_AI 5 
#define OS_EVENT_TYPE_MAIN 8 // User scheduled events
#define OS_EVENT_TYPE_NONE 255 // No event (used if no event could be dequeued)

#define OS_EVENT_QUEUE_SIZE 32

typedef struct OSEventQueue_t {
    OSEvent queue [OS_EVENT_QUEUE_SIZE];
    
    int start; // Index of first element
    int end; // Index after last element
} OSEventQueue;

// Functions
void osScheduleEvent (OSEvent event);

#endif
