/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0c_ft_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:00:15 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:57:43 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/**
 * @brief 0 = read, 1 = write, 2 = append
 * 
 * @param file file to open
 * @param read_or_write 0 = read, 1 = write, 2 = append
 * @return int 
 */
int	ft_open_readorwrite(char *file, int read_or_write)
{
	int	fd;

	fd = -1;
	if (read_or_write == 0)
		fd = open(file, O_RDONLY);
	else if (read_or_write == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (read_or_write == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		halt_exit_fd(1);
	if (fd == -1)
		halt_exit_fd(1);
	return (fd);
}

int	ft_open(char *file, int flags, ...)
{
	int		fd;
	va_list	args;

	fd = -1;
	va_start(args, flags);
	if (flags == O_RDONLY)
		fd = open(file, flags);
	else if (flags == O_WRONLY || flags == O_CREAT || flags == O_TRUNC)
		fd = open(file, flags, va_arg(args, int));
	else
		halt_exit_fd(1);
	va_end(args);
	if (fd == -1)
		halt_exit_fd(1);
	return (fd);
}
