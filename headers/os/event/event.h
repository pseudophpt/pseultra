/*
 * pseultra/headers/os/event/event.h
 * Event header 
 * 
 * (C) pseudophpt 2018 
 */

#ifndef OS_EVENT_EVENT_H_GUARD
#define OS_EVENT_EVENT_H_GUARD

typedef struct OSEvent_t {
    struct OSEvent_t *next; // Next event
    void (*callback) (void); // Execute this event
    u8 type; // Type of event
} OSEvent;

#define OS_EVENT_TYPE_SP 0 
#define OS_EVENT_TYPE_DP 1
#define OS_EVENT_TYPE_SI 2 
#define OS_EVENT_TYPE_VI 3 
#define OS_EVENT_TYPE_PI 4 
#define OS_EVENT_TYPE_AI 5 
#define OS_EVENT_TYPE_OTHER 8 // User scheduled events

// Functions
void osScheduleEvent (OSEvent *event);

#endif
