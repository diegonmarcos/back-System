/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.ft_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:19 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/12 15:50:47 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* https://linktr.ee/diegonmarcos											  */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_my_getenv_(char *cmd, char **env);
char	*ft_my_getenv(char *name, char **env);

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
