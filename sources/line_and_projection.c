/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:39:12 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:39:14 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	pixel_put(t_fdf *fdf, int x, int y, int color)
{
	int i;

	i = 0;
	if (!(x > WINDOW_WIDTH - 300 && y < 300))
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
			fdf->addresses[i] = color;
			fdf->addresses[++i] = color >> 8;
			fdf->addresses[++i] = color >> 16;
		}
	}
}

void			iso_projection(int *x, int *y, int z, int center)
{
	*x = (*x - *y) * cos(0.523599) + center;
	*y = -1 * z + (*x + *y) * sin(0.523599);
}

t_coord			proj(t_coord *old_coord, int gap, int midx, t_fdf *fdf)
{
	t_coord	coord;
	int		x;
	int		y;
	int		z;

	x = old_coord->x * gap;
	y = old_coord->y * gap;
	z = old_coord->z * fdf->multiplier;
	rotate_x(&y, &z, fdf->camera.x_angle);
	rotate_y(&x, &z, fdf->camera.y_angle);
	rotate_z(&x, &y, fdf->camera.z_angle);
	if (fdf->projection == ISO)
		iso_projection(&x, &y, z, midx * gap);
	coord.x = x + (fdf->offset).offset_x + (fdf->camera).move_x;
	coord.y = y + (fdf->offset).offset_y + (fdf->camera).move_y;
	coord.z = z;
	coord.color = old_coord->color;
	coord.old_z = old_coord->old_z;
	return (coord);
}

static	void	bresen_alg(t_coord start_coord, t_coord end_coord, t_fdf *fdf)
{
	int	x;
	int	y;
	int	err;
	int	diry;
	int dirx;

	diry = start_coord.y < end_coord.y ? 1 : -1;
	dirx = start_coord.x < end_coord.x ? 1 : -1;
	x = start_coord.x;
	y = start_coord.y;
	err = abs(end_coord.x - start_coord.x) - abs(end_coord.y - start_coord.y);
	while (x != end_coord.x || y != end_coord.y)
	{
		pixel_put(fdf, x, y, get_gradient(start_coord, end_coord, x, y));
		if (2 * err > -1 * abs(end_coord.y - start_coord.y) && x != end_coord.x)
		{
			err -= abs(end_coord.y - start_coord.y);
			x += dirx;
		}
		if (2 * err < abs(end_coord.x - start_coord.x) && y != end_coord.y)
		{
			err += abs(end_coord.x - start_coord.x);
			y += diry;
		}
	}
}

void			line_bresen(t_coord start_coord, t_coord end_coord, t_fdf *fdf)
{
	if (fdf->color_info == 0)
	{
		start_coord.color = get_color(start_coord.old_z, fdf);
		end_coord.color = get_color(end_coord.old_z, fdf);
	}
	pixel_put(fdf, end_coord.x, end_coord.y, end_coord.color);
	bresen_alg(start_coord, end_coord, fdf);
}
