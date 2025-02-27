/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.ft_piping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:19 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/27 16:00:49 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_pipe_flow(int pid, char **cmd, int *pipe_fd, char **env);
static void	data_client(char **cmd, char **env);
static void	data_server(char **cmd, char **env);

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
	set_pipe_flow(pid, cmd, pipe_fd, env);
	if (pid)
		data_client(cmd, env);
	else
		data_server(cmd, env);
}

static void	set_pipe_flow(int pid, char **cmd, int *pipe_fd, char **env)
{
	int	fd;

	if (pid)
	{
		close(pipe_fd[0]);
		fd = ft_open_readorwrite(cmd[1], 0);
		dup2(fd, 0);
		dup2(pipe_fd[1], 1);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		fd = ft_open_readorwrite(cmd[4], 1);
		dup2(fd, 1);
	}
}

static void	data_client(char **cmd, char **env)
{
	ft_execve(cmd[2], env);
}

static void	data_server(char **cmd, char **env)
{
	ft_execve(cmd[3], env);
}
