/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_2_ft_memchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:58:02 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/08 09:51:25 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: void *ft_memchr(const void *s, int c, size_t n);
 * @brief: scans the initial n bytes of the memory area pointed to by s for 
 * 			the first instance of c.
 * @param: s: pointer to the memory area to be scanned.
 * @return: returns a pointer to the matching byte or NULL if the character 
 * 			does not occur in the given memory area.
 * 
 * @note:
 * 
 * @file: ft_memchr.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:54
 * ************************************************************************** *
 */

#include "mylibc.h"

int	ft_contains(int num, char **argv, int i)
{
	i++;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == num)
			return (1);
		i++;
	}
	return (0);
}

/*
 * ************************************************************************** *
 * @syntax: char *ft_strnstr(const char *haystack, const char *needle, 
 * 								size_t len);
 * @brief: Locates the first occurrence of the null-terminated string needle 
 * 			in the string haystack, where not more than len characters are 
 * 			searched.
 * @param: haystack: The string to be searched.
 * @return: The function returns a pointer to the first occurrence in haystack
 * 			of any of the entire sequence of characters specified in needle, 
 * 			or a null pointer if the sequence is not present in haystack.
 * 
 * @note:
 * 
 * @file: ft_strnstr.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 12:02
 * ************************************************************************** *
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	if (!haystack && len == 0)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (*haystack && len >= needle_len)
	{
		if (!ft_strncmp(haystack, needle, needle_len))
		{
			return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}

/*
 * ************************************************************************** *
 * @syntax: char *ft_strrchr(const char *s, int c);
 * @brief: locates the last occurrence of c (converted to a char) in the 
 * 			string pointed to by s.
 * @param: 1. s: The string to be searched.
 * @return: A pointer to the located character, or NULL if the character does 
 * 			not appear in the string.
 * 
 * @note:
 * 
 * @file: ft_strrchr.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 12:03
 * ************************************************************************** *
 */
char	*ft_strrchr(const char *s, int c)
{
	char			*res;
	char			cc;

	cc = (char)c;
	res = NULL;
	while (*s)
	{
		if (*s == cc)
			res = (char *)s;
		s++;
	}
	if (*s == cc)
		res = (char *)s;
	return (res);
}

void	*ft_memmem(const void *haystack, size_t haystacklen, \
		const void *needle, size_t needlelen)
{
	const char	*begin = (const char *)haystack ;
	const char	*end = (const char *)haystack + haystacklen - needlelen;
	const char	*p = (const char *)needle;

	begin = (const char *)haystack ;
	end = (const char *)haystack + haystacklen - needlelen;
	p = (const char *)needle;
	if (needlelen == 0)
		return ((void *)haystack);
	if (haystacklen < needlelen)
		return (NULL);
	while (begin <= end)
	{
		if (*begin == *p && ft_memcmp(begin, p, needlelen) == 0)
			return ((void *)begin);
		begin++;
	}
	return (NULL);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*str;
	size_t				i;
	unsigned char		uc;

	str = (unsigned char *) s;
	uc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == uc)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
