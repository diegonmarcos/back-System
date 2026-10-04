/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_ft_fgets_gnl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:12:14 by dnepomuc          #+#    #+#             */
/*   Updated: 2025/03/13 15:35:59 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

char	*ft_new_left_str(char *left_str);
char	*ft_get_line(char *left_str);
char	*ft_read_to_left_str(int fd, char *left_str);

int	ft_fgets(char *line, int line_size, int fd)
{
	char	*ptr;

	ptr = get_next_line(fd);
	ft_memcpy(line, ptr, line_size);
	if (*line)
		return (0);
	free(ptr);
	return (ft_strlen(ptr));
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || GNL_BUFFER_SIZE <= 0)
		return (0);
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str || !*left_str)
		return (NULL);
	line = ft_strjoin_gnl(NULL, left_str, '\n');
	left_str = ft_new_left_str(left_str);
	return (line);
}

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = (char *) malloc((GNL_BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr_gnl(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, GNL_BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			free(left_str);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin_gnl(left_str, buff, '\0');
	}
	free(buff);
	if (!left_str || !*left_str)
		return (free(left_str), NULL);
	return (left_str);
}

char	*ft_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	i = ft_strlen_gnl(left_str, '\n');
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen_gnl(left_str, '\0')
				- i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	return (str[j] = '\0', free(left_str), str);
}

/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test1.txt", O_RDONLY);
	fd3 = open("corrupted_file.txt", O_RDONLY);

	i = 1;
	printf("##############FRIST FILE\n");
	while ((line = get_next_line(fd1)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	i = 0;
	printf("\n##############SECOND FILE\n");
	while ((line = get_next_line(fd2)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	i = 0;
	printf("\n##############THIRD FILE\n");
	while ((line = get_next_line(fd3)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
*/