/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_raster_scan_bresenham.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:28:54 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/16 17:02:24 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylibc.h"

void	bresenham_line(t_bresenham *b, void (*put_pixel)(int, int));
void	example_put_pixel(int x, int y);
void	bresenham_step(t_bresenham *b);

void	bresenham_line(t_bresenham *b, void (*put_pixel)(int, int))
{
	b->dx = abs(b->x1 - b->x0);
	b->dy = abs(b->y1 - b->y0);
	b->sx = -1;
	if (b->x0 < b->x1)
		b->sx = 1;
	b->sy = -1;
	if (b->y0 < b->y1)
		b->sy = 1;
	b->err = b->dx - b->dy;
	while (1)
	{
		put_pixel(b->x0, b->y0);
		if (b->x0 == b->x1 && b->y0 == b->y1)
			break ;
		bresenham_step(b);
	}
}

void	bresenham_step(t_bresenham *b)
{
	int	err2;

	err2 = 2 * b->err;
	if (err2 > -b->dy)
	{
		b->err -= b->dy;
		b->x0 += b->sx;
	}
	if (err2 < b->dx)
	{
		b->err += b->dx;
		b->y0 += b->sy;
	}
}

void	example_put_pixel(int x, int y)
{
	(void)x;
	(void)y;
}

/* int	main(void)
{
	t_bresenham	b1 = {10, 10, 100, 50, 0, 0, 0, 0, 0};
	t_bresenham	b2 = {100, 50, 10, 10, 0, 0, 0, 0, 0};
	t_bresenham	b3 = {10, 10, 10, 100, 0, 0, 0, 0, 0};

	bresenham_line(&b1, example_put_pixel);
	bresenham_line(&b2, example_put_pixel);
	bresenham_line(&b3, example_put_pixel);

	return (0);
} */
