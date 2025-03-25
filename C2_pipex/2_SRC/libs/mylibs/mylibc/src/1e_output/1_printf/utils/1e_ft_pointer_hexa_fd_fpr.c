/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_hexa_fd_fpr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:59:35 by dnepomuc          #+#    #+#             */
/*   Updated: 2025/01/27 20:34:04 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

static int	hexa_pointer_fd(long fd, char *base, unsigned long long n, int c)
{
	unsigned long long	b;

	b = ft_strlen(base);
	if (n >= b)
	{
		c = hexa_pointer_fd(fd, base, n / b, c);
		if (c == -1)
			return (-1);
		if (write (fd, &base[n % b], 1) == -1)
			return (-1);
		c++;
	}
	else if (n < b)
	{
		if (write (fd, &base[n], 1) == -1)
			return (-1);
		c++;
	}
	return (c);
}

int	ft_pointer_hexa_fpr(long fd, void *p)
{
	unsigned long long	pointer;
	int					char_count;

	char_count = 0;
	pointer = (unsigned long long)p;
	if (!p)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	if (write(fd, "0x", 2) != 2)
		return (-1);
	char_count = hexa_pointer_fd(fd, "0123456789abcdef", pointer, char_count);
	if (char_count == (-1))
		return (-1);
	char_count += 2;
	return (char_count);
}
