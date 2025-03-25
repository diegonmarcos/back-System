/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_ft_sed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:05:24 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/12 17:07:41 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/* int		ft_sed(char *file, char *s1, char *s2);
int		process_line(int fd2, char *line, char *s1, char *s2);

int	ft_sed(char *file, char *s1, char *s2)
{
	int		fd;
	int		fd2;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	fd2 = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
		return (1);
	while (get_next_line(fd))
	{
		if (process_line(fd2, line, s1, s2))
		{
			free(line);
			close(fd);
			close(fd2);
			return (1);
		}
		free(line);
	}
	close(fd);
	close(fd2);
	rename("tmp", file);
	return (0);
}

int	procces_line(int fd2, char *line, char *s1, char *s2)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strstr(line, s1);
	if (tmp)
	{
		tmp2 = ft_strreplace(line, s1, s2);
		if (!tmp2)
			return (1);
		write(fd2, tmp2, ft_strlen(tmp2));
		free(tmp2);
	}
	return (0);
} */

/* int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	if (ft_sed(argv[1], argv[2], argv[3]))
	{
		write(2, "Error: failed to open file\n", 28);
		return (1);
	}
	return (0);
} */
