/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.ft_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:19 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/25 16:13:43 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* https://linktr.ee/diegonmarcos											  */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_my_getenv_(char *cmd, char **env);
char	*ft_my_getenv(char *name, char **env);

/**
 * ft_execve - Executes a command using execve system call.
 * @cmd: The command to be executed.
 * @env: The environment variables.
 *
 * This function splits the command string into an array of arguments,
 * retrieves the executable path from the environment, and then attempts
 * to execute the command using execve. If execve fails, it writes the
 * command name to the standard error, frees the allocated memory for
 * the command arguments, and exits the process.
 */
void	ft_execve(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(NAME_M, cmd, ' ');
	path = ft_my_getenv_(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		write(2, &s_cmd[0], ft_strlen(s_cmd[0]));
		ft_free_array_2d(s_cmd);
		halt_exit_fd(0);
	}
}

/**
 * @brief Retrieves the full path of a command by searching through the 
 * system's PATH environment variable.
 *
 * This function takes a command and the environment variables, splits the
 *  PATH environment variable into
 * individual paths, and checks each path to see if the command exists and 
 * is executable. If the command is found,
 * the full path to the command is returned. If the command is not found, 
 * the original command is returned.
 * 
 * access is used to check if the file exists and is executable.
 *
 * @param cmd The command to search for.
 * @param env The environment variables.
 * @return The full path to the command if found, otherwise the original 
 * command.
 */
char	*ft_my_getenv_(char *cmd, char **env)
{
	int		i;
	char	*getenv_path;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(NAME_M, ft_my_getenv("PATH", env), ':');
	s_cmd = ft_split(NAME_M, cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(NAME_M, allpath[i], "/");
		getenv_path = ft_strjoin(NAME_M, path_part, s_cmd[0]);
		free(path_part);
		if (access(getenv_path, F_OK | X_OK) == 0)
		{
			ft_free_array_2d(s_cmd);
			return (getenv_path);
		}
		free(getenv_path);
	}
	ft_free_array_2d(allpath);
	ft_free_array_2d(s_cmd);
	return (cmd);
}

/**
 * ft_my_getenv - Retrieves the value of an environment variable.
 * @name: The name of the environment variable to find.
 * @env: The array of environment variables.
 *
 * This function searches through the provided environment variables to find
 * the one that matches the given name. If a match is found, it returns the
 * value of the environment variable. If no match is found, it returns NULL.
 *
 * Return: The value of the environment variable if found, otherwise NULL.
 */
char	*ft_my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(NAME_M, env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}
