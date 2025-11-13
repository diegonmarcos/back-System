/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0a_ft_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:39:29 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:28:38 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

void	ft_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		halt_exit_fd(-1);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		halt_exit_fd(1);
	return (pid);
}
