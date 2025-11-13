/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.ft_piping_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:47 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/10 10:07:49 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* https://linktr.ee/diegonmarcos											  */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	set_pipe_flow(int pid, int *pipe_fd);
static void	child(char **cmd, char **env);
static void	parent(int *pipe_fd);

/**
 * @brief Implementaiton of a Unix pipeline.
 * 
 * @details 
 * @par Details:
 * - pipe_fd[2] contains the file descriptors for the pipe,
 * 		[0] for reading [1] for writing.
 * - ft_fork() creates a parente and a child process that runs concurrently.
 * - parent() sees PID != 0 and will read from the pipe and write output file.
 * - child() sees PID = 0 and will execute the first command.
 * -  0 STD_IN, 1 STD_OUT, 2 STD_ERR.
 * - dup2(fd, fd2) will duplicate the file descriptor fd to fd2,
 * 		and will close fd2 if open.
 * 
 * 
 * @param cmd 
 * @param env 
 */
void	ft_piping(char **cmd, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	ft_pipe(pipe_fd);
	pid = ft_fork();
	set_pipe_flow(pid, pipe_fd);
	if (pid)
		parent(pipe_fd);
	else
		child(cmd, env);
}

static void	set_pipe_flow(int pid, int *pipe_fd)
{
	if (pid)
		close(pipe_fd[WRITE]);
	else
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STD_OUT);
	}
}

static void	parent(int *pipe_fd)
{
	dup2(pipe_fd[READ], STD_IN);
}

static void	child(char **cmd, char **env)
{
	ft_execve(*cmd, env);
}
