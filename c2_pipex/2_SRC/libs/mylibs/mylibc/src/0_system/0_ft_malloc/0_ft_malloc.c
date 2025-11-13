/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_ft_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:33:50 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/19 09:10:10 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/* void *ft_malloc(size_t requested_size) 
{
    // Step 1: Handle edge cases
    if (requested_size == 0)
        return NULL;
    
    // Step 2: Adjust the size to ensure proper alignment (typically 8 bytes)
    size_t aligned_size = align_to_multiple(requested_size, 8);
    
    // Step 3: Search the free list for a suitable block
    struct block_header *current = head;
    struct block_header *suitable_block = NULL;
    
    while (current != NULL)
	{
        if (current->is_free && current->size >= aligned_size)
		{
            suitable_block = current;
            break;  // Found a block that's big enough
        }
        current = current->next;
    }
    
    // Step 4: If no suitable block was found, request more memory from the OS
    if (suitable_block == NULL)
	{
        suitable_block = request_memory_from_os(aligned_size + \
		sizeof(struct block_header));
        if (suitable_block == NULL) {
            return NULL;  // Memory allocation failed
        }
        
        // Set up the new block's metadata
        suitable_block->size = aligned_size;
        suitable_block->is_free = 0;
        suitable_block->next = NULL;
        
        // If we have existing blocks, add this to the end of the list
        if (head == NULL)
            head = suitable_block;
		else
		{
            // Find the last block and append
            current = head;
            while (current->next != NULL)
			{
                current = current->next;
            }
            current->next = suitable_block;
        }
    } 
	else
	{
        // Step 5: Found a suitable block - mark it as allocated
        suitable_block->is_free = 0;
        
        // Step 6: Split the block if it's much larger than needed
        split_block_if_needed(suitable_block, aligned_size);
    }
    
    // Step 7: Return a pointer to the usable area (right after the header)
    return (void *)(suitable_block + 1);
}

// Helper function to request memory from the operating system
struct block_header *request_memory_from_os(size_t size) 
{
    // Round up size to a multiple of the page size for efficiency
    size_t page_size = 4096;  // Common page size, but could be \
	determined at runtime
    size_t adjusted_size = ((size + page_size - 1) / page_size) * page_size;
    
    // For small allocations, extend the heap
    if (adjusted_size < 128 * 1024) {  // 128KB threshold is common
        void *block = sbrk(adjusted_size);
        if (block == (void *)-1) {
            return NULL;  // sbrk failed
        }
        return block;
    } else {
        // For large allocations, use mmap
        void *block = mmap(NULL, adjusted_size, PROT_READ | PROT_WRITE, 
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (block == MAP_FAILED) {
            return NULL;  // mmap failed
        }
        return block;
    }
}

// Split a block if it's significantly larger than needed
void split_block_if_needed(struct block_header *block, size_t size)
{
    // Only split if the leftover chunk would be large enough to be useful
    // (header size + minimum block size, often 16-32 bytes)
    size_t min_block_size = 32;
    
    if (block->size >= size + sizeof(struct block_header) + min_block_size)
	{
        // Create a new block header after the allocated portion
        struct block_header *new_block = (struct block_header *)\
		((char *)(block + 1) + size);
        
        // Set up the new block
        new_block->size = block->size - size - sizeof(struct block_header);
        new_block->is_free = 1;
        new_block->next = block->next;
        
        // Update the original block
        block->size = size;
        block->next = new_block;
    }
}
 */