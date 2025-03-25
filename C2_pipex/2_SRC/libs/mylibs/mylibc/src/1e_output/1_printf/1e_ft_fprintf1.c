/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0c_ft_fprintf1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:23:43 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:31:17 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

static int	type_var(long fd, char formatSpecifier, va_list item)
{
	if (formatSpecifier == 'c')
		return (ft_putchar_fd_fpr(fd, va_arg(item, int)));
	if (formatSpecifier == 's')
		return (ft_putstr_fd_fpr(fd, va_arg(item, char *)));
	if (formatSpecifier == 'd' || formatSpecifier == 'i')
		return (ft_putnbr_fd_fpr(fd, va_arg(item, int)));
	if (formatSpecifier == 'p')
		return (ft_pointer_hexa_fpr(fd, va_arg(item, void *)));
	if (formatSpecifier == 'S')
		return (ft_putstrstr_fd_fpr(fd, va_arg(item, char **)));
	if (formatSpecifier == 'L')
		return (ft_print_ls_doubly_fd_int(fd, va_arg(item, t_list_dls *)));
	return (0);
}

static int	w_str_percent(long fd, char formatSpecifier, va_list item)
{
	int	char_count;

	char_count = 0;
	if (formatSpecifier != '%')
	{
		char_count = type_var(fd, formatSpecifier, item);
		if (char_count == -1)
			return (-1);
		return (char_count);
	}
	else
	{
		if (write (fd, &formatSpecifier, 1) != 1)
			return (-1);
		return (1);
	}
}

static int	w_str(long fd, const char *str, va_list item, int char_count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			char_count = char_count + w_str_percent(fd, str[i + 1], item);
			if (char_count == -1)
				return (-1);
			i++;
		}
		else
		{
			if (write(fd, &str[i], 1) != 1)
				return (-1);
			char_count++;
		}
		i++;
	}
	return (char_count);
}

int	ft_fprintf1(char *filename, const char *str, ...)
{
	va_list	item;
	int		char_count;
	FILE	*output_file;
	long	fd;

	output_file = fopen(filename, "a");
	if (output_file == NULL)
		return (1);
	fd = fileno(output_file);
	if (flock(fd, LOCK_EX) == -1)
	{
		perror("Failed to lock file");
		close(fd);
		return (1);
	}
	char_count = 0;
	va_start(item, str);
	char_count = w_str(fd, str, item, char_count);
	va_end(item);
	fclose(output_file);
	return (char_count);
}

/*
* "w" open for writing.Truncate file to zero length or create empty file.
* "a" open for appending.
*/
int	ft_fprintf2(char *fopenmode, char *filename, const char *str, ...)
{
	va_list	item;
	int		char_count;
	FILE	*output_file;
	long	fd;

	output_file = fopen(filename, fopenmode);
	if (output_file == NULL)
		return (1);
	if (ft_strcmp(filename, "1") == 0)
		fd = fileno(stdout);
	else
		fd = fileno(output_file);
	if (flock(fd, LOCK_EX) == -1)
	{
		perror("Failed to lock file");
		close(fd);
		return (1);
	}
	char_count = 0;
	va_start(item, str);
	char_count = w_str(fd, str, item, char_count);
	va_end(item);
	fflush(output_file);
	fclose(output_file);
	return (char_count);
}

/*
--- FORMAT SPECIFIERS ---
c:		This specifier is for printing a single character.
s:		This specifier is for printing a string of characters.
d/i:	This specifier is for printing a decimal number/integer.
p: 		This specifier is for printing a pointer.
u: 		This specifier is for printing an unsigned integer.
X: 		This specifier is for printing a hexadecimal number in uppercase.
x: 		This specifier is for printing a hexadecimal number in lowercase.
*/