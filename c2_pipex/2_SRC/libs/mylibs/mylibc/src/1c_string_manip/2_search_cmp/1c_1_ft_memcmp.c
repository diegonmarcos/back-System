/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_1_ft_memcmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:58:10 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/08 09:46:14 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/*
 * ************************************************************************** *
 * @syntax: int ft_strncmp(const char *s1, const char *s2, size_t n);
 * @brief: compares the first n bytes of s1 and s2.
 * @param: 1. s1: string to be compared.
 * @return: 2. s2: string to be compared.
 * 
 * @note:
 * 
 * @file: ft_strncmp.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 12:02
 * ************************************************************************** *
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp_duplicate(char *str, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(str, array[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp_duplicate_inter(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
 * ************************************************************************** *
 * @syntax: int ft_memcmp(const void *s1, const void *s2, size_t n);
 * @brief: compares byte string s1 against byte string s2.
 * @param: 1. s1: pointer to the first memory block to be compared.
 * @return: 2. s2: pointer to the second memory block to be compared.
 * 
 * @note:
 * 
 * @file: ft_memcmp.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:55
 * ************************************************************************** *
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1 = (const unsigned char *)s1;
	const unsigned char	*str2 = (const unsigned char *)s2;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}
