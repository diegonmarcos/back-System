/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.ft_piping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:19 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/11 16:18:17 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(char **cmd, int *pipe_fd, char **env)
{
	int	fd;

	fd = ft_open_readorwrite(cmd[1], 0);
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	ft_execve(cmd[2], env);
}

static void	parent(char **cmd, int *pipe_fd, char **env)
{
	int	fd;

	fd = ft_open_readorwrite(cmd[4], 1);
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	ft_execve(cmd[3], env);
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
		parent(cmd, pipe_fd, env);
}
