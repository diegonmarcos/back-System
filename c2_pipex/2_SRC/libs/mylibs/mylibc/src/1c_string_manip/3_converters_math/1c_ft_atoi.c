/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:54:23 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/02 20:35:05 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: int ft_atoi(const char *ptr)
 * @brief: This function converts the initial portion of the string pointed 
 * 			to by ptr to int representation.
 * @param: Takes a pointer to a string.
 * @return: Returns the converted int representation of the string.
 * 
 * @note: 
 * 
 * @file: ft_atoi.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:41
 * ************************************************************************** *
 */

#include "mylibc.h"

int	ft_atoi(const char *ptr)
{
	int		i;
	int		neg;
	int		result;

	i = 0;
	neg = 1;
	result = 0;
	while (ptr[i] == ' ' || (ptr[i] >= 9 && ptr[i] <= 13))
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			neg = -1;
		i++;
	}
	while (ptr[i] != '\0' && ptr[i] >= '0' && ptr[i] <= '9')
	{
		result = (result * 10) + (ptr[i] - '0');
		i++;
	}
	return (result * neg);
}

long	ft_atoi_long(const char *ptr)
{
	int		i;
	int		neg;
	long	result;

	i = 0;
	neg = 1;
	result = 0;
	while (ptr[i] == ' ' || (ptr[i] >= 9 && ptr[i] <= 13))
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			neg = -1;
		i++;
	}
	while (ptr[i] != '\0' && ptr[i] >= '0' && ptr[i] <= '9')
	{
		result = (result * 10) + (ptr[i] - '0');
		i++;
	}
	return (result * neg);
}

long	*ft_atoi_long_array(const char **ptr)
{
	long	*array_long;
	int		i;
	int		size;

	size = 0;
	while (ptr[size])
		size++;
	array_long = (long *)malloc(sizeof(long) * size);
	i = 0;
	if (!array_long)
		return (NULL);
	while (ptr[i])
	{
		array_long[i] = ft_atoi_long(ptr[i]);
		i++;
	}
	return (array_long);
}

int	ft_atoi_safe(const char *ptr)
{
	long	number;

	number = ft_atoi(ptr);
	if (ft_isnum(ptr))
	{
		if (number >= INT_MIN && number <= 2147483647)
			return (number);
	}
	halt_exit_(1);
	return (1);
}
// INT_MAX = 2147483647

/* if (result > 214748364 || (result == 214748364 && ptr[i] > '7'))
			halt_exit_(1);

 */
/*#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    int i;
    char *s;
 
    s = " -9885";
    i = atoi(s);      //i = -9885 
 
    printf("i = %d\n",i);
}*/
