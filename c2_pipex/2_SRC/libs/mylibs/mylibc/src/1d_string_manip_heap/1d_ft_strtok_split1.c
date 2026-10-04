/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_ft_strtok_split1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:00:43 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/25 07:57:41 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: char *ft_substr(const char *s, unsigned int start, size_t len);
 * @brief: Allocates (malloc(3)) and returns a substring from the string ’s’.
 * @param: #1. The string from which to create the substring.
 * @return: The substring. NULL if the allocation fails.
 * 
 * @note:
 * 
 * @file: ft_substr.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 12:04
 * ************************************************************************** *
 */

#include "mylibc.h"

/**
 * @brief Extracts a substring from a given string.
 *
 * This function allocates (with ft_calloc_fd) and returns a substring
 * from the string 's'. The substring begins at index 'start' and is of
 * maximum size 'len'.
 *
 * @param filename The name of the file to be used with 
 * ft_calloc_fd and ft_strdup.
 * @param s The original string from which the substring will be extracted.
 * @param start The starting index of the substring in the original string.
 * @param len The maximum length of the substring to be extracted.
 * @return A pointer to the newly allocated substring, or NULL if 
 * the allocation fails.
 */
char	*ft_substr(char *filename, const char *s, unsigned int start,
					size_t len)
{
	char		*str;
	size_t		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(filename, ""));
	if (len > (s_len - (size_t)start))
		len = (s_len - (size_t)start);
	str = ft_calloc_fd(filename, len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

/*
#include <stdio.h>

int main ()
{
	char str[] = "Born to code 42";
	printf("%s", ft_substr(str, 5, 7));
	return 0;
}
*/