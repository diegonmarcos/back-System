/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_ft_sscanf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:17:47 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/12 17:10:55 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

/* static void	handle_conversion(char specifier, char *split, \
		void **pointers, int *num_pointers);

static void	handle_format(const char *format, char **split, void **pointers, \
				int *num_pointers)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (format[j] != '\0' && split[i] != NULL)
	{
		if (format[j] == '%' && format[j + 1] != '\0')
		{
			handle_conversion(format[j + 1], split[i], pointers, num_pointers);
			j++;
		}
		i++;
		j++;
	}
}

static void	handle_conversion(char specifier, char *split, void **pointers, \
				int *num_pointers)
{
	int		*int_ptr;
	char	*str_ptr;

	if (specifier == 'd')
	{
		int_ptr = (int *)malloc(sizeof(int));
		if (int_ptr == NULL)
			return ;
		*int_ptr = ft_atoi(split);
		pointers[*num_pointers] = (void *)int_ptr;
		(*num_pointers)++;
	}
	else if (specifier == 's')
	{
		str_ptr = strdup(split);
		if (str_ptr == NULL)
			return ;
		pointers[*num_pointers] = (void *)str_ptr;
		(*num_pointers)++;
	}
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_sscanf(char *line, const char *format, void **pointers, \
			int *num_pointers)
{
	char	**split;

	split = ft_split(line, format, ' ');
	if (split == NULL)
	{
		write(2, "Split Error\n", 12);
		return ;
	}
	handle_format(format, split, pointers, num_pointers);
	free_split(split);
} */
