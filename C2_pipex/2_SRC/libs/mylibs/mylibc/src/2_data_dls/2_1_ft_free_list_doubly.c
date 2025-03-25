/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list_doubly.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:16:05 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/03 17:16:58 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/*
Free the circular doubly linked list
*/
void	ft_free_ls_doubly(t_list_dls *stack)
{
	t_list_dls	*current;
	t_list_dls	*temp;
	int			switch_flag;

	if (stack == NULL)
		return ;
	switch_flag = 1;
	current = stack;
	while (current != stack || switch_flag)
	{
		temp = current;
		current = current->next;
		free(temp);
		switch_flag = 0;
	}
}
