/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.intro_sort1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:34:07 by dinepomu          #+#    #+#             */
/*   Updated: 2025/01/31 20:19:39 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

void	swap_introsort(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(int arr[], int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j <= high - 1)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap_introsort(&arr[i], &arr[j]);
		}
		j++;
	}
	swap_introsort(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	heapify(int arr[], int n, int i)
{
	int	largest;
	int	l;
	int	r;

	largest = i;
	l = 2 * i + 1;
	r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		swap_introsort(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}
