/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   push_swap_dbg_lib_others.c						 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dinepomu <dinepomu@student.42berlin.de>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/19 10:33:50 by dinepomu		  #+#	#+#			 */
/*   Updated: 2025/01/27 13:16:46 by dinepomu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

//##############################################################################
// HEADER
//##############################################################################

// LIBRARIES
#include "mylibc.h"

//##############################################################################
// MEMORY ALLOCATION
//##############################################################################
/*
Free the linked list
*/
void	ft_free_ls_simple(t_list_s *stack)
{
	t_list_s	*current;
	t_list_s	*temp;

	if (stack == NULL)
		return ;
	current = stack;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

t_list_s	*ft_lstlast_s(t_list_s *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}
