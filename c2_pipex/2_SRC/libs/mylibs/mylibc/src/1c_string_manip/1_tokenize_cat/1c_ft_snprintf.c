/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1c_ft_snprintf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:08:54 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/17 13:21:00 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

static void	handle_integer_specifier(t_list_snprintf *list)
{
	int		num;
	char	*num_string;
	size_t	num_len;

	num = va_arg(list->args, int);
	num_string = ft_itoa(num);
	num_len = ft_strlen(num_string);
	if (list->remaining >= num_len)
	{
		ft_memcpy(list->str_p, num_string, num_len);
		list->str_p += num_len;
		list->remaining -= num_len;
	}
	list->len += num_len;
	free(num_string);
}

static void	handle_string_specifier(t_list_snprintf *list)
{
	const char	*s;
	size_t		s_len;
	size_t		copy_len;

	s = va_arg(list->args, const char *);
	s_len = ft_strlen(s);
	if (list->remaining > 0)
	{
		if (s_len < list->remaining)
			copy_len = s_len;
		else
			copy_len = list->remaining - 1;
		ft_memcpy(list->str_p, s, copy_len);
		list->str_p += copy_len;
		list->remaining -= copy_len;
	}
	list->len += s_len;
}

static void	handle_format_specifier(const char **p, t_list_snprintf *list)
{
	if (**p == 'd')
		handle_integer_specifier(list);
	else if (**p == 's')
		handle_string_specifier(list);
	else if (**p == 'c')
	{
		if (list->remaining > 1)
		{
			*list->str_p++ = (char)va_arg(list->args, int);
			list->remaining--;
		}
		list->len++;
	}
}

static void	process_format(t_list_snprintf *list)
{
	const char	*p;

	p = list->format;
	while (*p != '\0')
	{
		if (*p == '%' && *(p + 1) != '\0')
		{
			p++;
			handle_format_specifier(&p, list);
		}
		else
		{
			if (list->remaining > 0)
			{
				*list->str_p++ = *p;
				list->remaining--;
			}
			list->len++;
		}
		p++;
	}
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	t_list_snprintf	list;

	list.format = format;
	list.str_p = str;
	list.remaining = size;
	list.len = 0;
	va_start(list.args, format);
	process_format(&list);
	va_end(list.args);
	if (list.remaining > 0)
		*list.str_p = '\0';
	else if (size > 0)
		str[size - 1] = '\0';
	return (list.len);
}

/* int	main (void)
{
	char	str[100];
	int		len;

	len = ft_snprintf(str, sizeof(str), "%d, Hello ,%c, %s, \
				%d_crazyfolks", 42, 'D', "world", 42);
	ft_printf("len: %d\n", len);
	ft_printf("str: %s\n", str);
	return (0);
}
 */