/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_ft_scanf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:59:20 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/12 17:10:11 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>

/**
 * 	- fgetc is a function that reads the next character from the specified 
 * stream and advances the position indicator for the stream.
 * 	- ungetc is a function that pushes the specified character back to the 
 * specified stream.
 * 
 * 	- skip_input_space is a function that reads characters from the specified 
 * stream until a non-whitespace character is found.
 * 
 * 	- scan_char is a function that reads a character from the specified stream 
 * and stores it in the location pointed to by c.
 * 	- scan_int is a function that reads an integer from the specified stream 
 * and stores it in the location pointed to by d.
 * 	- scan_string is a function that reads a string from the specified stream 
 * and stores it in the location pointed to by s.
 * 	- receive_input is a function that reads the next input item from the 
 * specified stream and stores it in the location pointed to by ap.
 * 
 * 	- receive_input is a function that reads the next input item from the 
 * specified stream and stores it in the location pointed to by ap.
 * 
 * 	- ft_scanf is a function that reads input from the standard input stream
 *  stdin  under the control of a format string that specifies the format of
 *  the input.
 */

/* void	skip_input_space(FILE *fd)
{
	int	c;
	while (isspace(c = fgetc(fd)))
		;
	if (c != EOF)
		ungetc(c, fd);
}

int	scan_char(FILE *fd, va_list ap)
{
	char	*c = va_arg(ap, char *);
	int		ch = fgetc(fd);

	if (ch == EOF)
		return (-1);
	*c = (char)ch;
	return (1);
}

int	scan_int(FILE *fd, va_list ap)
{
	int	*d = va_arg(ap, int *);
	int	num = 0, sign = 1, c;

	c = fgetc(fd);
	if (c == '-')
	{
		sign = -1;
		c = fgetc(fd);
	}
	if (!isdigit(c))
	{
		if (c != EOF)
			ungetc(c, fd);
		return (-1);
	}
	while (isdigit(c))
	{
		num = num * 10 + (c - '0');
		c = fgetc(fd);
	}
	if (c != EOF)
		ungetc(c, fd);
	*d = num * sign;
	return (1);
}

int	scan_string(FILE *fd, va_list ap)
{
	char	*s = va_arg(ap, char *);
	int		c;

	while (isspace(c = fgetc(fd)))
		;
	if (c == EOF)
		return (-1);
	while (!isspace(c) && c != EOF)
	{
		*s++ = (char)c;
		c = fgetc(fd);
	}
	if (c != EOF)
		ungetc(c, fd);
	*s = '\0';
	return (1);
}

int	receive_input(const char **format, FILE *fd, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(fd, ap);
		case 'd':
			skip_input_space(fd);
			return scan_int(fd, ap);
		case 's':
			skip_input_space(fd);
			return scan_string(fd, ap);
		default:
			return -1;
	}
}

int	ft_scanf(const char *format, ...)
{
	int		i = 0;
	int		result = 0;
	va_list ap;
	FILE	*fd = stdin;

	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (receive_input(&(format[i]), fd, ap) == -1)
				break ;
			else
				result++;
		}
		i++;
	}
	va_end(ap);
	return (result);
} */

/* 
void	ft_scanf(char *filename, char *line, void **pointers, int *num_pointers)
{
	char	**split;
	int		i;

	split = ft_split(filename, line, ';');
	if (split == NULL)
		write(2, "Split Error\n", 12);
	i = 0;
	while (split[i] != NULL)
	{
		pointers[*num_pointers] = (void *)ft_atoi_base(split[i], 16);
		(*num_pointers)++;
		free(split[i]);
		i++;
	}
	free(split);
} */
