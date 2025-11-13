/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0b_ft_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:09:17 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:29:56 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

void	ft_free_array_2d(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	ft_free_array_int(int **array_int, int size)
{
	int	i;

	if (array_int == NULL)
		return ;
	i = 0;
	while (i < size - 1)
	{
		free(array_int[i]);
		i++;
	}
	free(array_int);
}

// Used on ft_split.c
void	ft_free_array_halt(char **farray, int failed)
{
	while (failed > 0)
	{
		free(farray[failed - 1]);
		failed--;
	}
	free(farray);
}
