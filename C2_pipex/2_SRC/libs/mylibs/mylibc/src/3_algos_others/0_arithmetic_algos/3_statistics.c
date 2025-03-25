/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_statistics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:14:35 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:37:22 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

long	ft_min(long a, long b)
{
	if (a < b)
		return (a);
	return (b);
}

long	ft_mean(long *array, long size)
{
	long	mean;
	long	sum;
	long	i;

	sum = 0;
	i = 0;
	while (i < size)
	{
		sum += array[i];
		i++;
	}
	mean = sum / size;
	return (mean);
}
