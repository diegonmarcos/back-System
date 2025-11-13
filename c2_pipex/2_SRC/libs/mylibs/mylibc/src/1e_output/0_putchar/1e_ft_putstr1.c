/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0c_ft_putstr1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:11:24 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:32:25 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/*
 * ************************************************************************** *
 * @syntax: void ft_putstr_fd(char *str, int fd);
 * @brief: Outputs the string 'str' to the given file descriptor.
 * @param: 1. The string to output.
 * @return: None.
 * 
 * @note:
 * 
 * @file: ft_putstr_fd.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:57
 * ************************************************************************** *
 */
int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putstr_str(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i][0])
	{
		j = 0;
		while (str[i][j])
		{
			ft_putchar(str[i][j]);
			j++;
			count++;
		}
		if (str[i + 1])
			ft_putchar('\n');
		i++;
	}
	return (count);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_putstr_fd_fpr(long fd, char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		if (write (fd, "(null)", 6) != 6)
			return (-1);
		return (6);
	}
	while (s[i])
	{
		if (write(fd, &s[i], 1) != 1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putstrstr_fd_fpr(long fd, char **str)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (str[i])
	{
		len = ft_putstr_fd_fpr(fd, str[i]);
		write(fd, "\n", 1);
		if (len == -1)
			return (-1);
		count += len;
		i++;
	}
	return (count);
}

/*
 * ************************************************************************** *
 * @syntax: void ft_putendl_fd(char *str, int fd);
 * @brief: Outputs the string 'str' to the given file descriptor, 
 * 			followed by a newline.
 * @param: 1. str : the string to output.
 * @return: none
 * 
 * @note:
 * 
 * @file: ft_putendl_fd.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:57
 * ************************************************************************** *
 */
/* void	ft_putendl_fd(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
} */
