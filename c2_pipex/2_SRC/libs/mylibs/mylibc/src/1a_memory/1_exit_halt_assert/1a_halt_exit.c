/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halt_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:15:53 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/10 08:12:47 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

void	halt_exit_fd(int status)
{
	if (status == 1)
	{
		perror("System error");
		ft_fprintf(stderr, "Errno value: %d\n", errno);
		exit(status);
	}
	exit(status);
}

void	halt_exit_(int status)
{
	if (status == 1)
	{
		write(2, "Error\n", 6);
		exit(status);
	}
	exit(status);
}
