/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.ft_piping_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:47 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/11 16:19:35 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child(char **cmd, int *pipe_fd, char **env)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	ft_execve(*cmd, env);
}

static void	parent(int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
}

void	ft_piping(char **cmd, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	ft_pipe(pipe_fd);
	pid = ft_fork();
	if (!pid)
		child(cmd, pipe_fd, env);
	else
		parent(pipe_fd);
}
