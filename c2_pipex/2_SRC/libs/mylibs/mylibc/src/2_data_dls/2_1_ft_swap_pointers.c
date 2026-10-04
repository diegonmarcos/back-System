/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_pointers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:34:33 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/03 17:16:03 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

void	ft_swap_pointers(t_list_dls **a, t_list_dls **b)
{
	t_list_dls	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
