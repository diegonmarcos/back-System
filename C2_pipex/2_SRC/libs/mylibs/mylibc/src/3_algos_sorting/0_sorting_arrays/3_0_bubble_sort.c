/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.bubble_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:27:24 by dinepomu          #+#    #+#             */
/*   Updated: 2025/01/27 20:45:44 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	bubble_sort(int arr[], int n)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
/*
int	main(void)
{
	int	arr[] = {64, 34, 25, 12, 22, 11, 90};
	int	n;
	int	i;

	n = sizeof(arr) / sizeof(arr[0]);
	bubble_sort(arr, n);
	printf("Sorted array: \n");
	i = 0;
	while (i < n)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	return (0);
}*/