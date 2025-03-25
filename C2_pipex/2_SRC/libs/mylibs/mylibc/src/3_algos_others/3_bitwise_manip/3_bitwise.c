/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_bitwise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:37:28 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/05 12:35:00 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

void	print_bits(unsigned char octet)
{
	int				i;
	unsigned char	bit;

	i = 8;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}

unsigned char	reverse_bits(unsigned char octet)
{
	int				i;
	unsigned char	res;

	i = 8;
	res = 0;
	while (i--)
	{
		res = (res << 1) + (octet & 1);
		octet = octet >> 1;
	}
	return (res);
}

unsigned char	swap_bits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}

unsigned int	gray_code(unsigned int n)
{
	return (n ^ (n >> 1));
}

void	generate_gray_codes(unsigned int limit)
{
	unsigned int	i;

	i = 0;
	while (i <= limit)
	{
		print_bits(gray_code(i));
		printf("(#%d: %u)\n", i, gray_code(i));
		i++;
	}
}
/*
int	main(void)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	sum;
	unsigned int	carry;

	a = 6;
	b = 3;
	while (b != 0)
	{
		printf("b1: %u\n", b);
		sum = a ^ b;
		printf("sum: %u\n", sum);
		carry = (a & b) << 1;
		printf("carry: %u\n", carry);
		a = sum;
		printf("a: %u\n", a);
		b = carry;
		printf("b: %u\n", b);
		printf("____\n");
	}
	printf("Binary sum: %u\n", a);
	return (0);
}
*/