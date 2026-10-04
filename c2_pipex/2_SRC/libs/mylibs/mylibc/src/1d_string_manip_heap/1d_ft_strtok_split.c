/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_ft_strtok_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:59:11 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/10 10:43:54 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

static int	ft_char_in_set(char c, char const *set);

/*
 * ************************************************************************** *
 * @syntax: char **ft_split(char const *s, char c);
 * @brief: Allocates (with malloc(3)) and returns an array of strings 
 * 			obtained by splitting ’s’ using the character ’c’ as a delimiter.
 * 			The array must be ended by a NULL pointer.
 * @param: #1. The string to be split.
 * @return: The array of new strings resulting from the split. NULL if the 
 * 			allocation fails.
 * 
 * @note:
 * 
 * @file: ft_split.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:58
 * ************************************************************************** *
 */
long	*ft_split_long(char *filename, char const *array_source,
			char delimitator, int *size)
{
	char		**array_char_split;
	long		*array_int;
	int			i;

	array_char_split = ft_split(filename, array_source, delimitator);
	*size = 0;
	while (array_char_split[*size])
		(*size)++;
	array_int = (long *)ft_calloc_fd(filename, *size, sizeof(int));
	if (!array_int)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		array_int[i] = ft_atoi_long(array_char_split[i]);
		i++;
	}
	ft_free_array_2d(array_char_split);
	return (array_int);
}

char	**ft_split(char *filename, char const *s, char c)
{
	char	**array;
	int		num_words;
	int		i;
	int		j;

	array = (char **)ft_calloc_fd(filename, ft_countwords(s, c) + 1,
			sizeof(char *));
	if (!array || !s)
		return (NULL);
	i = 0;
	j = 0;
	num_words = 0;
	while (num_words < ft_countwords(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		array[num_words] = ft_substr(filename, s, j, i - j);
		if (!array[num_words++])
			return (ft_free_array_halt(array, num_words - 1), NULL);
	}
	array[num_words] = NULL;
	return (array);
}

int	ft_countwords(char const *s, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != c)
		{
			counter++;
		}
		while (s[i] && s[i] != c)
		{
			i++;
			if (s[i] == '\0')
				return (counter);
		}
		i++;
	}
	return (counter);
}

/* ************************************************************************** *
 * @syntax: char *ft_strtrim(char const *s1, char const *set);
 * @brief: Allocates (with malloc(3)) and returns a copy of ’s1’ with the
 * @param: #1. The string to be trimmed.
 * @return: The trimmed string. NULL if the allocation fails.
 * 
 * @note:
 * 
 * @file: ft_strtrim.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 12:04
 * ************************************************************************** *
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

static int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
#include "../../4.Tester/Tester/libdnm.h"

int main()
{
	char *s = "   Born to Code in  42  ";
	char c = ' ';
	char **array = ft_split(s, c);
	int i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	return 0;
}
*/