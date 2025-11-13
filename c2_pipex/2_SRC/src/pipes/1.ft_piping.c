/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.ft_piping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:19 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/26 17:14:10 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* https://linktr.ee/diegonmarcos											  */
/* ************************************************************************** */

#include "pipex.h"

static void	set_pipe_flow(int pid, char **cmd, int *pipe_fd);
static void	p_client(char **cmd, char **env);
static void	p_server(char **cmd, char **env);

/** @brief Implementation of a Unix pipeline.
 *
 * 	@details
 * 	@par Details:
 * 	- pipe_fd[2] contains the file descriptors for the pipe,
 * 		[0] for reading [1] for writing.
 * 	- ft_fork() creates a parente and a child process that runs concurrently.
 * 	- parent() sees PID != 0 and will read from the pipe and write output file.
 * 	- child() sees PID = 0 and will execute the first command.
 * 	-  0 STD_IN, 1 STD_OUT, 2 STD_ERR.
 *  - dup2(fd, fd2) will duplicate the file descriptor fd to fd2, 
 * 		and will close fd2 if open.
 * 
 * 	@par Usage:
 * 	- @b [parm1] is a list of commdands
 * 	- @b [parm2] is a list of environment variables
 */

void	ft_piping(char **cmd, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	ft_pipe(pipe_fd);
	pid = ft_fork();
	set_pipe_flow(pid, cmd, pipe_fd);
	if (pid)
		p_client(cmd, env);
	else
		p_server(cmd, env);
}

/**
 * ./pipex [dup2] {infile.txt} [dup2] {"grep -x "PATH=.*""} [dup2] {"cat"} 
 * [dup2] {outfile.txt}
 * ./pipex {infile.txt} {"grep -x "PATH=.*""} {"cat"} {outfile.txt}
 * env | grep -x "PATH=.*" | cat > outfile.txt
 */
static void	set_pipe_flow(int pid, char **cmd, int *pipe_fd)
{
	int	fd;

	if (pid)
	{
		close(pipe_fd[READ]);
		fd = ft_open_readorwrite(cmd[1], 0);
		dup2(fd, STD_IN);
		dup2(pipe_fd[WRITE], STD_OUT);
	}
	else
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STD_IN);
		fd = ft_open_readorwrite(cmd[4], 1);
		dup2(fd, 1);
	}
}

static void	p_client(char **cmd, char **env)
{
	ft_execve(cmd[2], env);
}

static void	p_server(char **cmd, char **env)
{
	ft_execve(cmd[3], env);
}
