/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:59:26 by dinepomu          #+#    #+#             */
/*   Updated: 2025/01/27 22:42:29 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: char *ft_strdup(const char *s1);
 * @brief: returns a pointer to a new string which is a duplicate of the 
 * 			string s1.
 * @param: 1. s1: The string to duplicate.
 * @return: A pointer to the duplicated string. NULL if insufficient memory 
 * 			was available.
 * 
 * @note:
 * 
 * @file: ft_strdup.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:59
 * ************************************************************************** *
 */

#include "mylibc.h"

char	*ft_strdup(char *filename, const char *s1)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(s1);
	dest = (char *) ft_calloc_fd(filename, len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len + 1);
	return (dest);
}
