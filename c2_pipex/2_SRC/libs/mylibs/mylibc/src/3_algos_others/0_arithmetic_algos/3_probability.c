/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_probability.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:40:04 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:26:22 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

long	ft_factorial(long nb)
{
	if (nb < 0)
		return (0);
	if (nb == 0)
		return (1);
	return (nb * ft_factorial(nb - 1));
}
