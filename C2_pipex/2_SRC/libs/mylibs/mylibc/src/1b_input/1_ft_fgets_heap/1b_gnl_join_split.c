/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_gnl_join_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:12:14 by dnepomuc          #+#    #+#             */
/*   Updated: 2025/03/13 14:54:36 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

char	*get_next_line_join(int fd)
{
	char	*array;
	char	*ptr;
	char	*temp;

	array = ft_strdup(NAME_M, "");
	if (!array)
		halt_exit_(1);
	ptr = get_next_line(fd);
	while (ptr)
	{
		temp = array;
		array = ft_strjoin(NAME_M, array, ptr);
		free(temp);
		free(ptr);
		ptr = get_next_line(fd);
	}
	return (array);
}

int	get_next_line_split(int fd, char **lines)
{
	char	*ptr;
	int		i;

	ptr = get_next_line(fd);
	i = 0;
	while (ptr)
	{
		lines[i++] = ptr;
		ptr = get_next_line(fd);
	}
	return (i);
}

/* int	get_next_line_split(int fd, char **line)
{
	static char	*left_str;
	int			status;
	int			i;

	left_str = NULL;
	i = 0;
	while (1)
	{
		if (fd < 0 || BUFFER_SIZE <= 0 || !line)
			return (1);
		status = ft_read_to_left_str2(fd, &left_str);
		if (status == 1)
			return (1);
		if (status == 0 && (!left_str || !*left_str))
		{
			line[i] = NULL;
			return (0);
		}
		line[i] = ft_get_line(left_str);
		left_str = ft_new_left_str(left_str);
		i++;
	}
	return (2);
}

int	ft_read_to_left_str2(int fd, char **left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (1);
	rd_bytes = 1;
	while (!ft_strchr_gnl(*left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			free(*left_str);
			*left_str = NULL;
			return (1);
		}
		buff[rd_bytes] = '\0';
		*left_str = ft_strjoin_gnl(*left_str, buff, '\0');
	}
	free(buff);
	if (rd_bytes == 0)
		return (0);
	return (2);
} */
