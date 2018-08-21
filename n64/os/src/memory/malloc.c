/*
 * pseultra/n64/os/src/memory/malloc.c
 * Memory allocation routines
 * 
 * (C) pseudophpt 2018 
 */

/**
 * @file src/memory/malloc.c
 * @brief Memory allocation routines
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This file provides routines for managing the dynamic allocation of memory, such as allocation, deallocation, and initialization of the heap. These routines use a linked list to manage a heap of memory. 
 */

#include <os_priv.h>

/*
 * Macros
 */

/** @internal @brief Size of one block header */
#define OS_HEAP_HEAD_SIZE sizeof(OSHeapLink)
/** @internal @brief Flag describing a used block */
#define OS_ALLOC_USED 0
/** @internal @brief Flag describing a free block */
#define OS_ALLOC_FREE 1

/**
 * @brief Initializes the specified heap
 * @param[out] heap Pointer to the start of the heap to initialize
 * @param[in] heap_size The size of the heap
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function initializes the specified heap by creating one linked list node describing a block which encompasses the whole heap.
 *
 * @note This function must be called before using osMalloc() or osFree()
 * 
 * @see osMalloc
 * @see osFree
 */
void
osInitHeap
(void *heap, int heap_size) {
    // Beginning of heap is a heap link
    OSHeapLink *initial_header = (OSHeapLink *)heap;

    // Heap link has no previous or next links
    initial_header->prev = NULL;
    initial_header->next = NULL;

    // Heap link is open, and has the size of the remaining heap
    initial_header->flags = OS_ALLOC_FREE;
    initial_header->size = heap_size - OS_HEAP_HEAD_SIZE;
}

/**
 * @brief Allocate a contiguous block of memory from the heap
 * @param[out] heap Pointer to the start of the heap to allocate from
 * @param[in] size Size of memory block to allocate
 * @return Pointer to allocated block of memory
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function allocates a contiguous block of memory from the heap by traversing the heap's link list until it finds a block which is both free and is large enough to support the requested block.
 *
 * @note Any calls to this function should use a heap which has been initialized with osInitHeap
 *
 * @see osInitHeap
 * @see osFree
 */
void
*osMalloc
(int size, void *heap) {
    // Beginning of heap is a heap link
    OSHeapLink *initial_header = (OSHeapLink *)heap;
    OSHeapLink *current_header = initial_header;

    int size_with_head = size + OS_HEAP_HEAD_SIZE;

    // Find open area
    while(1) {
        // Found open area
        if (size_with_head <= current_header->size && current_header->flags == OS_ALLOC_FREE) {
            // New header
            OSHeapLink *new_header = (OSHeapLink *)(((u32)current_header) + size_with_head);

            // Fill with correct information
            new_header->prev = current_header;
            new_header->next = current_header->next;

            new_header->flags = OS_ALLOC_FREE;
            new_header->size = current_header->size - size_with_head;

            // Update old header
            current_header->next = new_header;
            
            current_header->flags = OS_ALLOC_USED;
            current_header->size = size;

            // Return location
            return (void *)(((u32)current_header) + OS_HEAP_HEAD_SIZE);
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

/**
 * @brief Free a memory region allocated with osMalloc() 
 * @param [in,out] region 
 * @date 1 Aug 2018
 * @author pseudophpt
 *
 * This function frees a contiguous block of memory from the heap by marking the block as free and coalescing  it with any neighbors also marked free.
 *
 * @note Any calls to this function should use a heap which has been initialized with osInitHeap
 * @note This function should only be used on regions allocated with osMalloc(), and only once. Otherwise, undefined behavior may occur
 *
 * @see osInitHeap
 * @see osMalloc
 */
void
osFree
(void *region) {
    OSHeapLink *region_header = ((OSHeapLink *)region) - 1;

    // Regions before and ahead exist and are both free
    if ((region_header->prev != NULL && region_header->prev->flags == OS_ALLOC_FREE)
        &&
        (region_header->next != NULL && region_header->next->flags == OS_ALLOC_FREE)) {
        // Set union's next as the last block's next
        region_header->prev->next = region_header->next->next;

        if (region_header->next->next != NULL)
            region_header->next->next->prev = region_header->prev;

        // Update union's size
        region_header->prev->size += (region_header->size) + (region_header->next->size) + (OS_HEAP_HEAD_SIZE * 2);

        return;
    }

    // Only region before exists and is free
    else if (region_header->prev != NULL && region_header->prev->flags == OS_ALLOC_FREE) {
        // Set union's next as the next block
        region_header->prev->next = region_header->next;

        if (region_header->next != NULL)
            region_header->next->prev = region_header->prev;

        // Update union's size
        region_header->prev->size += (region_header->size) + OS_HEAP_HEAD_SIZE;

        return;
    }

    // Only region after exists and is free
    else if (region_header->next != NULL && region_header->next->flags == OS_ALLOC_FREE) {
        // Set next block's previous as union
        if (region_header->next->next != NULL)
            region_header->next->next->prev = region_header;

        // Update union's size
        region_header->size += (region_header->next->size) + OS_HEAP_HEAD_SIZE;

        return;
    }

    else region_header->flags = OS_ALLOC_FREE;
}
