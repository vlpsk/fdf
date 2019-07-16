/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:44:56 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:44:59 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int		get_light(int start, int end, double percentage)
{
	int	light;

	light = (int)((1 - percentage) * start + percentage * end);
	return (light);
}

static	double	get_percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	else
		return (placement / distance);
}

int				get_color(int z, t_fdf *fdf)
{
	int color;
	int	mid;

	mid = fdf->color_info->mid_height[(fdf->color_info->size / 2) - 1];
	if (z > mid)
		color = UP_COLOR;
	else if (z < mid)
		color = DOWN_COLOR;
	else
		color = fdf->base_color;
	return (color);
}

int				get_gradient(t_coord start_coord, t_coord end_coord, int x,
	int y)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	if (abs(end_coord.x - start_coord.x) > abs(end_coord.y - start_coord.y))
		percentage = get_percent(start_coord.x, end_coord.x, x);
	else
		percentage = get_percent(start_coord.y, end_coord.y, y);
	red = get_light((start_coord.color >> 16) & 0xFF,
		(end_coord.color >> 16) & 0xFF, percentage);
	green = get_light((start_coord.color >> 8) & 0xFF,
		(end_coord.color >> 8) & 0xFF, percentage);
	blue = get_light(start_coord.color & 0xFF, end_coord.color & 0xFF,
		percentage);
	return ((red << 16) | (green << 8) | blue);
}
