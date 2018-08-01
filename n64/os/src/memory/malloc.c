/*
 * pseultra/os/memory/malloc.c
 * Memory allocation routines
 * 
 * (C) pseudophpt 2018 
 */

#include <os.h>

/* Initializes heap */
void osInitHeap (void *heap, int heap_size) {
    // Beginning of heap is a heap link
    OSHeapLink *initial_header = (OSHeapLink *)heap;

    // Heap link has no previous or next links
    initial_header->prev = NULL;
    initial_header->next = NULL;

    // Heap link is open, and has the size of the remaining heap
    initial_header->flags = ALLOC_FREE;
    initial_header->size = heap_size - HEAP_HEAD_SIZE;
}

/* Allocates memory from the heap */
void *osMalloc (int size, void *heap) {
    // Beginning of heap is a heap link
    OSHeapLink *initial_header = (OSHeapLink *)heap;
    OSHeapLink *current_header = initial_header;

    int size_with_head = size + HEAP_HEAD_SIZE;

    // Find open area
    while(1) {
        // Found open area
        if (size_with_head <= current_header->size && current_header->flags == ALLOC_FREE) {
            // New header
            OSHeapLink *new_header = (OSHeapLink *)(((u32)current_header) + size_with_head);

            // Fill with correct information
            new_header->prev = current_header;
            new_header->next = current_header->next;

            new_header->flags = ALLOC_FREE;
            new_header->size = current_header->size - size_with_head;

            // Update old header
            current_header->next = new_header;
            
            current_header->flags = ALLOC_USED;
            current_header->size = size;

            // Return location
            return (void *)(((u32)current_header) + HEAP_HEAD_SIZE);
        }

        // There's another block, go to it
        else if (current_header->next != NULL) {
            // Set the current header to the next one
            current_header = current_header->next;
        }

        // No more blocks
        else return NULL;
    }
}

void osFree (void *region) {
    OSHeapLink *region_header = ((OSHeapLink *)region) - 1;

    // Regions before and ahead exist and are both free
    if ((region_header->prev != NULL && region_header->prev->flags == ALLOC_FREE)
        &&
        (region_header->next != NULL && region_header->next->flags == ALLOC_FREE)) {
        // Set union's next as the last block's next
        region_header->prev->next = region_header->next->next;

        if (region_header->next->next != NULL)
            region_header->next->next->prev = region_header->prev;

        // Update union's size
        region_header->prev->size += (region_header->size) + (region_header->next->size) + (HEAP_HEAD_SIZE * 2);

        return;
    }

    // Only region before exists and is free
    else if (region_header->prev != NULL && region_header->prev->flags == ALLOC_FREE) {
        // Set union's next as the next block
        region_header->prev->next = region_header->next;

        if (region_header->next != NULL)
            region_header->next->prev = region_header->prev;

        // Update union's size
        region_header->prev->size += (region_header->size) + HEAP_HEAD_SIZE;

        return;
    }

    // Only region after exists and is free
    else if (region_header->next != NULL && region_header->next->flags == ALLOC_FREE) {
        // Set next block's previous as union
        if (region_header->next->next != NULL)
            region_header->next->next->prev = region_header;

        // Update union's size
        region_header->size += (region_header->next->size) + HEAP_HEAD_SIZE;

        return;
    }

    else region_header->flags = ALLOC_FREE;
}
