/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_1_linked_list_doubly2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:08:36 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:27:14 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/*
Find the minimum value node in a circular linked list 
	(excluding a given index)
*/
t_list_dls	*find_min_node(t_list_dls *stack)
{
	t_list_dls	*min_node;
	t_list_dls	*current;
	int			swicth_flag;

	min_node = NULL;
	current = stack;
	swicth_flag = 1;
	if (!stack)
		return (NULL);
	while (swicth_flag || current != stack)
	{
		if (min_node == NULL || current->value < min_node->value)
			min_node = current;
		current = current->next;
		swicth_flag = 0;
	}
	return (min_node);
}

int	find_min_node1(t_list_dls *stack)
{
	t_list_dls	*min_node;
	t_list_dls	*current;
	int			swicth_flag;

	min_node = NULL;
	current = stack;
	swicth_flag = 1;
	if (!stack)
		return (0);
	while (swicth_flag || current != stack)
	{
		if (min_node == NULL || current->value < min_node->value)
		{
			min_node = current;
		}
		current = current->next;
		swicth_flag = 0;
	}
	return (min_node->value);
}

/*
** Function check if the stack is sorted
*/
int	is_sorted_linked_list(t_list_dls *stack)
{
	t_list_dls	*current;

	if (stack == NULL)
		return (1);
	current = stack;
	while (current->next != stack)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

int	max_node_finder(t_list_dls **stack)
{
	int			max_node;
	int			rotations;
	t_list_dls	*current;

	rotations = 0;
	max_node = (*stack)->index;
	current = *stack;
	while (rotations < ft_lstsize(*stack))
	{
		if (current->index > max_node)
			max_node = current->index;
		current = current->next;
		rotations++;
	}
	return (max_node);
}
