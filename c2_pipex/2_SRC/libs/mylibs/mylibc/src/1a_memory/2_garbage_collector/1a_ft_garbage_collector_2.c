/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:57:56 by dinepomu          #+#    #+#             */
/*   Updated: 2025/01/31 20:17:57 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/*
#define MAX_ALLOCATIONS 1024
typedef struct s_list_garbage
{
	void	*allocated_pointers[MAX_ALLOCATIONS];
	int		blocks_count;
}			t_list_garbage;


void	ft_free_gb(void *ptr, t_list_garbage *list_garbage);
void	ft_free_gb_all(t_list_garbage *list_garbage);
void	ft_struct_initializator(t_list_garbage *my_list);
int		add_allocation(void *ptr, t_list_garbage *list_garbage);
void	remove_allocation(void *ptr, t_list_garbage *list_garbage);
void	remove_allocation(void *ptr, t_list_garbage *list_garbage);
int		is_allocated(void *ptr, t_list_garbage *list_garbage);
void	*ft_malloc_gb(size_t size, t_list_garbage *list_garbage);
*/

// Function to add a new allocation to the tracking array
int	add_allocation(void *ptr, t_list_garbage *list_garbage)
{
	int	i;

	i = 0;
	while (i < MAX_ALLOCATIONS)
	{
		if (list_garbage->allocated_pointers[i] == NULL)
		{
			list_garbage->allocated_pointers[i] = ptr;
			list_garbage->blocks_count++;
			return (1);
		}
		i++;
	}
	return (0);
}

// Function to remove an allocation from the tracking array
void	remove_allocation(void *ptr, t_list_garbage *list_garbage)
{
	int	i;

	i = 0;
	while (i < MAX_ALLOCATIONS)
	{
		if (list_garbage->allocated_pointers[i] == ptr)
		{
			list_garbage->allocated_pointers[i] = NULL;
			list_garbage->blocks_count--;
			return ;
		}
		i++;
	}
}

// Function to check if an address is currently tracked as allocated
int	is_allocated(void *ptr, t_list_garbage *list_garbage)
{
	int	i;

	i = 0;
	while (i < MAX_ALLOCATIONS)
	{
		if (list_garbage->allocated_pointers[i] == ptr)
			return (1);
		i++;
	}
	return (0);
}

// Wrapper for malloc that also tracks the allocation
void	*ft_malloc_gb(size_t size, t_list_garbage *list_garbage)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
	{
		if (!add_allocation(ptr, list_garbage))
		{
			fprintf(stderr, "Error: Allocation tracking array is full!\n");
			free(ptr);
			return (NULL);
		}
	}
	return (ptr);
}
