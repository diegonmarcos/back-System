/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:47 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/10 10:08:04 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* https://linktr.ee/diegonmarcos											  */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		fd_in;
	int		fd_out;

	error_handling_pipex_bonus(argc, argv[1]);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		i = 3;
		fd_out = ft_open_readorwrite(argv[argc - 1], 2);
		ft_piping_heredoc(argv);
	}
	else
	{
		i = 2;
		fd_in = ft_open_readorwrite(argv[1], 0);
		fd_out = ft_open_readorwrite(argv[argc - 1], 1);
		dup2(fd_in, 0);
	}
	while (i < argc - 2)
		ft_piping(&argv[i++], env);
	dup2(fd_out, 1);
	ft_execve(argv[argc - 2], env);
}
