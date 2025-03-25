/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_statistics2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:14:35 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:26:32 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"
/* 
long	ft_iqr(long *array, long size)
{
	long	iqr;
	long	q1;
	long	q3;

	q1 = ft_quartile(array, size, 1);
	q3 = ft_quartile(array, size, 3);
	iqr = q3 - q1;
	return (iqr);
}

long	ft_skewness(long *array, long size)
{
	long	skewness;
	long	mean;
	long	standard_deviation;
	long	sum;
	long	i;

	mean = ft_mean(array, size);
	standard_deviation = ft_standard_deviation(array, size);
	sum = 0;
	i = 0;
	while (i < size)
	{
		sum += ft_pow(array[i] - mean, 3);
		i++;
	}
	skewness = sum / (size * ft_pow(standard_deviation, 3));
	return (skewness);
}

long	ft_kurtosis(long *array, long size)
{
	long	kurtosis;
	long	mean;
	long	standard_deviation;
	long	sum;
	long	i;

	mean = ft_mean(array, size);
	standard_deviation = ft_standard_deviation(array, size);
	sum = 0;
	i = 0;
	while (i < size)
	{
		sum += ft_pow(array[i] - mean, 4);
		i++;
	}
	kurtosis = sum / (size * ft_pow(standard_deviation, 4));
	return (kurtosis);
}

long	ft_covariance(long *array1, long *array2, long size)
{
	long	covariance;
	long	mean1;
	long	mean2;
	long	sum;
	long	i;

	mean1 = ft_mean(array1, size);
	mean2 = ft_mean(array2, size);
	sum = 0;
	i = 0;
	while (i < size)
	{
		sum += (array1[i] - mean1) * (array2[i] - mean2);
		i++;
	}
	covariance = sum / size;
	return (covariance);
}

long	ft_correlation(long *array1, long *array2, long size)
{
	long	correlation;
	long	covariance;
	long	standard_deviation1;
	long	standard_deviation2;

	covariance = ft_covariance(array1, array2, size);
	standard_deviation1 = ft_standard_deviation(array1, size);
	standard_deviation2 = ft_standard_deviation(array2, size);
	correlation = covariance / (standard_deviation1 * standard_deviation2);
	return (correlation);
}

long	ft_z_score(long value, long *array, long size)
{
	long	z_score;
	long	mean;
	long	standard_deviation;

	mean = ft_mean(array, size);
	standard_deviation = ft_standard_deviation(array, size);
	z_score = (value - mean) / standard_deviation;
	return (z_score);
}
 */
