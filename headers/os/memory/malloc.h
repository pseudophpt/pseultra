/*
 * pseultra/headers/os/memory/malloc.h
 * Memory allocation
 * 
 * (C) pseudophpt 2018 
 */

#ifndef OS_MEMORY_MALLOC_H_GUARD
#define OS_MEMORY_MALLOC_H_GUARD

// Memory allocation linked list
struct OSHeapLink_t {
	struct OSHeapLink_t *prev;
	struct OSHeapLink_t *next;
	u8 flags; // 0 for used, 1 for FREE
	u32 size;
};

typedef struct OSHeapLink_t OSHeapLink;

#define HEAP_HEAD_SIZE sizeof(OSHeapLink)

#define ALLOC_USED 0
#define ALLOC_FREE 1

// Functions
void osInitHeap (void *heap, int heap_size);
void *osMalloc (int size, void *heap);
void osFree (void *region);

#endif
