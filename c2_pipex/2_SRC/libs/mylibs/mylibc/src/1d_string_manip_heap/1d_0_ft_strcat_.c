/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_ft_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:59:40 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/07 15:32:49 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: char *ft_strjoin(const char *s1, const char *s2);
 * @brief: Concatenates two strings.
 * @param: 1. s1 - The prefix string.
 * @return:	The new string. NULL if the allocation fails.
 * 
 * @note:
 * 
 * @file: ft_strjoin.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 12:00
 * ************************************************************************** *
 */

#include "mylibc.h"

char	*ft_strjoin(char *filename, const char *s1, const char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	res = (char *) ft_calloc_fd(filename, (ft_strlen(s1) + ft_strlen(s2) + 1),
			sizeof(char));
	if (!res)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = 0;
	return (res);
}

char	*ft_strjoin_gnl(char *left_str, char *buff, int c)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = (char *) malloc(sizeof(char) * ((ft_strlen_gnl(left_str, '\0')
					+ ft_strlen_gnl(buff, c)) + 2));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i])
			str[i] = left_str[i];
	while (buff[j] && buff[j] != c)
		str[i++] = buff[j++];
	if (buff[j] == c)
		str[i++] = c;
	return (str[i] = '\0', free(left_str), str);
}
