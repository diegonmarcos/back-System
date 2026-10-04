/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.intro_sort0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:34:07 by dinepomu          #+#    #+#             */
/*   Updated: 2025/01/31 20:18:06 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/*
objective: Implement the intro sort algorithm.
This is the implementation of intro sort algorithm. It is a hybrid sorting 
	algorithm that provides both fast average performance and optimal worst-case
	performance. It begins with quicksort and switches to heapsort when the 
	recursion depth exceeds a level based on the number of elements being sorted.
*/

void	heap_sort(int arr[], int n)
{
	int	i;

	i = n / 2 - 1;
	while (i >= 0)
	{
		heapify(arr, n, i);
		i--;
	}
	i = n - 1;
	while (i > 0)
	{
		swap_introsort(&arr[0], &arr[i]);
		heapify(arr, i, 0);
		i--;
	}
}

void	quick_sort(int arr[], int low, int high, int depthlimit)
{
	int	pi;

	pi = partition(arr, low, high);
	if (low < high)
	{
		if (depthlimit == 0)
		{
			heap_sort(arr + low, high - low + 1);
			return ;
		}
		quick_sort(arr, low, pi - 1, depthlimit - 1);
		quick_sort(arr, pi + 1, high, depthlimit - 1);
	}
}

int	ft_log_introsort(int n)
{
	int	result;

	result = 0;
	while (n > 1)
	{
		n >>= 1;
		result++;
	}
	return (result);
}

void	intro_sort(int arr[], int n)
{
	int	depthlimit;

	depthlimit = 2 * ft_log_introsort(n);
	quick_sort(arr, 0, n - 1, depthlimit);
}

/*
int	main(void)

{
	int	arr[] = {10, 7, 8, 9, 1, 5};
	int	n = sizeof(arr) / sizeof(arr[0]);

	intro_sort(arr, n);
	printf("Sorted array: \n");
	for (int i = 0; i < n; i++) 
	{
		printf("%d ", arr[i]);
	}
	return 0;
}*/