/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1c_ft_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:15:14 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/12 14:30:10 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

int	ft_round(double num)
{
	int	rounded;

	rounded = (int)num;
	if (num - rounded >= .5)
		rounded++;
	return (rounded);
}

int	ft_abs(int number)
{
	if (number < 0)
		number *= -1;
	return (number);
}
