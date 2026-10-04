/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0b_ft_calloc_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:35:48 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 13:01:58 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

// This will output two files, because one need to be cleaned to 
//avoid memory leakks over twice freed, and other for checking the
//allocating history
// filename as a char 0 will not print!
void	*ft_calloc_fd(char *filename, size_t count, size_t sizeofvar)
{
	char	*ptr;

	ptr = (char *)ft_calloc(count, sizeofvar);
	if (ptr == NULL)
		halt_exit_(1);
	if (!ft_strncmp(filename, "+1", 2))
		ptr = (char *)ft_calloc(count + 1, sizeofvar);
	return (ptr);
}
/* 
	int		fd;
	int		fd2;
	char	filename2[100];
	if (ft_strncmp(filename, "0", 1))
	{
		fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			write(1, "Error Opening File\n", 20);
		ft_memncpy_null_local(filename2, filename, ft_strlen(filename) - 3);
		fd2 = open(filename2, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd2 == -1)
			write(1, "Error Opening File\n", 20);
		if (ft_fprintf1(filename, "%p;\n", ptr) < 0)
			write(1, "Error Writing File\n", 20);
		if (ft_fprintf1(filename2, "%p;\n", ptr) < 0)
			write(1, "Error Writing File\n", 20);
		close(fd);
		close(fd2);
	}
 */