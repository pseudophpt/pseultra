/*
 * pseultra/headers/os/memory/malloc.h
 * Memory allocation
 * 
 * (C) pseudophpt 2018 
 */

#ifndef MALLOC_H_GUARD
#define MALLOC_H_GUARD

// Memory allocation linked list
struct HeapLink_t {
	struct HeapLink_t *prev;
	struct HeapLink_t *next;
	u8 flags; // 0 for used, 1 for FREE
	u32 size;
};

typedef struct HeapLink_t HeapLink;

#define HEAP_HEAD_SIZE sizeof(HeapLink)

#define ALLOC_USED 0
#define ALLOC_FREE 1

// Functions
void osInitHeap (void *heap, int heap_size);
void *osMalloc (int size, void *heap);
void osFree (void *region);

#endif
