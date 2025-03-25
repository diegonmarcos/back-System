/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_2_ft_strchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:59:20 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/07 15:30:20 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: char *ft_strchr(const char *array_int, int c);
 * @brief: Locates the first occurrence of ’c’ (converted to a char) in the
 * @param: #1. The string to be scanned.
 * @return: The pointer to the located character, or NULL if the character does
 * 
 * @note:
 * 
 * @file: ft_strchr.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:58
 * ************************************************************************** *
 */

#include "mylibc.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

int	ft_strchr_char_duplicate(char c, char **argv, int i)
{
	i++;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "-", 1) == 0)
			i++;
		if (argv[i][0] == c)
			return (1);
		i++;
	}
	return (0);
}

int	*ft_strchr_int_duplicate(int *array_int, int size, int position)
{
	int	i;
	int	look_for;

	look_for = array_int[position];
	i = position + 1;
	while (i < size)
	{
		if (array_int[i] == look_for)
			return (&array_int[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_gnl(s, '\0')]);
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

/* 
char	*ft_strchr_char_duplicate_interation(char **array_char)
{
	int	i;

	i = 0;
	while (array_char[i])
	{
		if (ft_strchr_char_duplicate(array_char[i][0], array_char, i))
			return (array_char[i]);
		i++;
	}
	return (NULL);
}
int	*ft_strchr_int_duplicate_interation(int *array_int, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strchr_int_duplicate(array_int, size, i))
			return (ft_strchr_int_duplicate(array_int, size, i));
		i++;
	}
	return (0);
} */