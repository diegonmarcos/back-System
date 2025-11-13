/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_unsign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:22:51 by dnepomuc          #+#    #+#             */
/*   Updated: 2025/01/27 21:10:41 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

size_t	ft_num_unsign(size_t num)
{
	int	char_count;

	char_count = 0;
	if (num > 9)
	{
		char_count = ft_num_unsign(num / 10);
		if (char_count == -1)
			return (-1);
		num = num % 10;
	}
	if (num <= 9)
	{
		if (ft_putchar (('0' + num)) == -1)
			return (-1);
		char_count++;
	}
	return (char_count);
}
