/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.error_handling_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:14:51 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/11 16:19:49 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_handling_pipex_bonus(int ac, char *av)
{
	if (ac < 5)
		halt_exit_(1);
	if (ft_strcmp(&av[1], "here_doc") == 0 && ac < 6)
		halt_exit_(1);
	if (ac > 20)
		halt_exit_(1);
}
