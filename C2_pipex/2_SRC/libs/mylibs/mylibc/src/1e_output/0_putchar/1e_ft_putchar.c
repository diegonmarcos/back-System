/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1e_ft_putchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:06:20 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/16 17:43:26 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/*
 * ************************************************************************** *
 * @syntax: void ft_putchar_fd(char c, int fd);
 * @brief: Outputs the character 'c' to the given file descriptor.
 * @param: 1. c : the character to output.
 * @return: none
 * 
 * @note:
 * 
 * @file: ft_putchar_fd.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:58
 * ************************************************************************** *
 */
int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putchar_int(int c)
{
	if (write (1, &c, 1) != 1)
		return (-1);
	return (1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_putchar_fd_fpr(long fd, int c)
{
	if (write (fd, &c, 1) != 1)
		return (-1);
	return (1);
}
