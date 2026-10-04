/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_0_ft_lstdelone_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:57:07 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:09:03 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ************************************************************************** *
 * @syntax: void ft_lstdelone(t_list_s *lst, void (*del)(void*));
 * @brief: Takes as a parameter an element and frees the memory of the 
 * 			element’s
 * @param: #1. The element to free.
 * @return: None.
 * 
 * @note:
 * 
 * @file: ft_lstdelone.c
 * @author: Diego <dinepomu@student.42>
 * @created: 10/Nov/2024 08:57
 * @updated: 10/Nov/2024 11:51
 * ************************************************************************** *
 */

#include "mylibc.h"

void	ft_lstdelone_s(t_list_s *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstiter_s(t_list_s *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

t_list_s	*ft_lstmap_s(t_list_s *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list_s	*new_lst;
	t_list_s	*new_elem;
	void		*content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_elem = ft_lstnew_s(content);
		if (!new_elem)
		{
			ft_lstclear_s(&new_lst, del);
			del(content);
			return (NULL);
		}
		ft_lstadd_back_s(&new_lst, new_elem);
		lst = lst->next;
	}
	return (new_lst);
}
