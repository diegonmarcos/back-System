/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.ft_piping_heredoc_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:47 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/10 10:07:54 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* https://linktr.ee/diegonmarcos											  */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	set_pipe_flow(int pid, int *pipe_fd);
static void	child(char **cmd, int *pipe_fd);
static void	parent(void);

void	ft_piping_heredoc(char **cmd)
{
	int		pipe_fd[2];
	pid_t	pid;

	ft_pipe(pipe_fd);
	pid = ft_fork();
	set_pipe_flow(pid, pipe_fd);
	if (pid)
		parent();
	else
		child(cmd, pipe_fd);
}

static void	set_pipe_flow(int pid, int *pipe_fd)
{
	if (pid)
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], READ);
	}
	else
		close(pipe_fd[READ]);
}

static void	parent(void)
{
	wait(NULL);
}

static void	child(char **cmd, int *pipe_fd)
{
	char	*lines[20];
	char	**lines_interator;

	ft_bzero(lines, sizeof(lines));
	get_next_line2(0, lines);
	lines_interator = lines;
	while (*lines)
	{
		if (ft_strncmp(*lines_interator, cmd[2], ft_strlen(cmd[2])) != 0)
		{
			ft_dprintf(pipe_fd[WRITE], "%s", *lines);
			free(*lines_interator);
		}
		else
		{
			free(*lines_interator);
			exit(0);
		}
		ft_dprintf(pipe_fd[WRITE], "%s", *lines);
		free(*lines_interator);
		lines_interator++;
	}
}
