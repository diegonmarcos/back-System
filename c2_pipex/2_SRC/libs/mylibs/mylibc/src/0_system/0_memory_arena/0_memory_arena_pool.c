/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_memory_arena_pool.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:15:16 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/09 08:59:50 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/* #include <sys/mman.h>
#include <pthread.h>

typedef struct
{
    void *memory;       // Pointer to the start of the arena
    size_t size;        // Total size of the arena
    size_t used;        // How much memory has been allocated
    pthread_mutex_t lock; // Lock for thread safety
} Arena;


Arena *arena_create(size_t size)
{
    Arena *arena = malloc(sizeof(Arena));
    if (!arena) return NULL;
    
    arena->memory = mmap(NULL, size, PROT_READ|PROT_WRITE, 
                          MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (arena->memory == MAP_FAILED) {
        free(arena);
        return NULL;
    }
    
    arena->size = size;
    arena->used = 0;
    pthread_mutex_init(&arena->lock, NULL);
    
    return arena;
}


void *arena_alloc(Arena *arena, size_t size) 
{
    size = (size + 7) & ~7;
    
    pthread_mutex_lock(&arena->lock);
    
    if (arena->used + size > arena->size)
	{
        pthread_mutex_unlock(&arena->lock);
        return NULL;  // Out of memory
    }
    
    void *ptr = arena->memory + arena->used;
    arena->used += size;
    
    pthread_mutex_unlock(&arena->lock);
    return ptr;
}


void arena_destroy(Arena *arena)
{
    munmap(arena->memory, arena->size);
    pthread_mutex_destroy(&arena->lock);
    free(arena);
} */