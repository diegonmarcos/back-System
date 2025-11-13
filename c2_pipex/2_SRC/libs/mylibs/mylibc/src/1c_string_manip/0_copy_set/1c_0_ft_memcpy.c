/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1c_0_ft_memcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:58:17 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/16 17:02:15 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < dstsize)
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (src_len);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (s < d && d < s + n)
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/*
 * ************************************************************************** *
 * @syntax: void *ft_memcpy(void *dst, const void *src, size_t n);
 * @brief: copies n bytes from memory area src to memory area dst.
 * @param: 1. dst - pointer to the destination array where the content is 
 * 			to be copied.
 * @return: pointer to the destination array.
 * 
 * @note: Faster then memmove but less safe: memcpy simply copies data from 
 * 			the source to the destination without considering potential 
 * 			overlaps. This makes it faster but can lead to unexpected results
 * 			if the source and destination memory blocks overlap.
 * 
 * @file: ft_memcpy.c
 * @author: Diego <dinepomu@student.42>
 * @created: 03/Aug/2024 12:07
 * @updated: 10/Nov/2024 11:55
 * ************************************************************************** *
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == (void *)0 && src == NULL)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (n > 0)
	{
		*(tmp_dst++) = *(tmp_src++);
		n--;
	}
	return (dst);
}

void	*ft_memcpy_(void *dst, const void *src)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == (void *)0 && src == NULL)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (*tmp_src)
		*(tmp_dst++) = *(tmp_src++);
	return (dst);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == (void *)0 && src == NULL)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (n > 0)
	{
		*(tmp_dst++) = *(tmp_src);
		if (*(tmp_src++) == (unsigned char)c)
			return (tmp_dst);
		n--;
	}
	return (NULL);
}
/*
int main()
{
	char src[] = "Hello World!";
	char dst[13];
	ft_memcpy(dst, src, 13);
	printf("%s\n", dst);
	return (0);
}
*/