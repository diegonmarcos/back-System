/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_0_ft_lstadd_back_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:56:23 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:07:17 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: void ft_lstadd_back(t_list_s **lst, t_list_s *new);
 * @brief: Adds the element ’new’ at the end of the list.
 * @param: #1. The address of a pointer to the first link of a list.
 * @return: None.
 * 
 * @note:
 * 
 * @file: ft_lstadd_back.c
 * @author: Diego <dinepomu@student.42>
 * @created: 10/Nov/2024 08:57
 * @updated: 10/Nov/2024 11:49
 * ************************************************************************** *
 */

#include "mylibc.h"

t_list_s	*ft_lstnew_s(void *content)
{
	t_list_s	*new_lst;

	new_lst = (t_list_s *)malloc(sizeof(t_list_s));
	if (!new_lst)
		return (NULL);
	new_lst->content = content;
	(*new_lst).next = NULL;
	return (new_lst);
}

void	ft_lstadd_back_s(t_list_s **lst, t_list_s *new)
{
	t_list_s	*tmp;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			tmp = ft_lstlast_s(*lst);
			tmp->next = new;
		}
	}
}

void	ft_lstadd_front_s(t_list_s **lst, t_list_s *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstclear_s(t_list_s **lst, void (*del)(void*))
{
	t_list_s	*tmp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_s(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

int	ft_lstsize_s(t_list_s *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
