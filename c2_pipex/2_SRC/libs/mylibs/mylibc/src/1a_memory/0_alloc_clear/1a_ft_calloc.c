/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:55:20 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/03 10:35:55 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: void *ft_calloc(size_t count, size_t size);
 * @brief: The calloc() function allocates memory for an array 
 * 			of nmemb elements
 * @param: count: The number of elements to allocate.
 * @return: The calloc() function returns a pointer to the allocated memory.
 * 
 * @note: 
 * 
 * @file: ft_calloc.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:44
 * ************************************************************************** *
 */

#include "mylibc.h"

void	ft_calloc_2d_sizetype(size_t *size, size_t *size_head, char var_type);
int		is_error_calloc_2d(void **array, size_t i);

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (SIZE_MAX / count < size)
		return (NULL);
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, size * count);
	return (tmp);
}

void	ft_calloc_(size_t count, size_t size, void **array)
{
	*array = ft_calloc(count, size);
}

void	ft_calloc_2d(size_t count, char var_type, void ***array)
{
	size_t	size;
	size_t	size_head;
	size_t	i;

	ft_calloc_2d_sizetype(&size, &size_head, var_type);
	ft_calloc_(count + 1, size_head, (void **)array);
	if (*array == NULL)
		return ;
	i = 0;
	while (i < count)
	{
		ft_calloc_(count, size, (void **)&((*array)[i]));
		if (is_error_calloc_2d(*array, i))
			return ;
		i++;
	}
	(*array)[count] = NULL;
}

void	ft_calloc_2d_sizetype(size_t *size, size_t *size_head, char var_type)
{
	if (var_type == 'c')
	{
		*size = sizeof(char);
		*size_head = sizeof(char *);
	}
	else if (var_type == 'i' || var_type == 'd')
	{
		*size = sizeof(int);
		*size_head = sizeof(int *);
	}
	else if (var_type == 'l')
	{
		*size = sizeof(long);
		*size_head = sizeof(long *);
	}
	else if (var_type == 'f')
	{
		*size = sizeof(float);
		*size_head = sizeof(float *);
	}
	else if (var_type == 'p')
	{
		*size = sizeof(void *);
		*size_head = sizeof(void **);
	}
}

int	is_error_calloc_2d(void **array, size_t i)
{
	size_t	j;

	j = 0;
	if (((void **)array)[i] == NULL)
	{
		j = 0;
		while (j < i)
		{
			free(((void **)array)[j]);
			j++;
		}
		free(array);
		array = NULL;
		return (1);
	}
	return (0);
}
