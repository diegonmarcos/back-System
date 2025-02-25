/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.ft_piping_heredoc_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:47 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/12 11:37:16 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child(char **cmd, int *pipe_fd)
{
	char	*lines[20];
	char	**lines_interator;

	close(pipe_fd[0]);
	ft_bzero(lines, sizeof(lines));
	get_next_line2(0, lines);
	lines_interator = lines;
	while (*lines)
	{
		if (ft_strncmp(*lines_interator, cmd[2], ft_strlen(cmd[2])) != 0)
		{
			ft_dprintf(pipe_fd[1], "%s", *lines);
			free(*lines_interator);
		}
		else
		{
			free(*lines_interator);
			exit(0);
		}
		ft_dprintf(pipe_fd[1], "%s", *lines);
		free(*lines_interator);
		lines_interator++;
	}
}

static void	parent(int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	wait(NULL);
}

void	ft_piping_heredoc(char **cmd)
{
	int		pipe_fd[2];
	pid_t	pid;

	ft_pipe(pipe_fd);
	pid = ft_fork();
	if (!pid)
		child(cmd, pipe_fd);
	else
		parent(pipe_fd);
}
