/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:13:10 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/03 13:34:51 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

int	ft_is_sorted_array_int(int	*arr, int size)
{
	int	i;

	i = -1;
	while (i++ < size - 1)
	{
		if (arr[i] > arr[i + 1])
			return (0);
	}
	return (1);
}

int	ft_is_sorted_array_char(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_atoi(arr[i]) < ft_atoi(arr[i - 1]))
			return (0);
		i++;
	}
	return (1);
}
