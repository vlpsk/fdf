/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_actions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:58:02 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:58:06 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		set_projection(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_P)
	{
		fdf->projection = PARALLEL;
		fdf->camera.x_angle = -1;
		fdf->camera.y_angle = 0;
		fdf->camera.z_angle = 0;
	}
	else
	{
		fdf->projection = ISO;
		fdf->camera.x_angle = 0;
		fdf->camera.y_angle = 0;
		fdf->camera.z_angle = 0;
	}
	redraw(fdf);
	return (0);
}

int		change_base_color(int keycode, t_fdf *fdf)
{
	int		red;
	int		green;
	int		blue;

	red = fdf->base_color >> 16 & 0xFF;
	green = fdf->base_color >> 8 & 0xFF;
	blue = fdf->base_color & 0xFF;
	if (keycode == KEY_R && red > 0x0)
		red = red - 0x1;
	else if (keycode == KEY_T && red < 0xFF)
		red = red + 0x1;
	else if (keycode == KEY_G && green > 0x0)
		green = green - 0x1;
	else if (keycode == KEY_H && green < 0xFF)
		green = green + 0x1;
	else if (keycode == KEY_B && blue > 0x0)
		blue = blue - 0x1;
	else if (keycode == KEY_N && blue < 0xFF)
		blue = blue + 0x1;
	fdf->base_color = ((red << 16) | (green << 8) | blue);
	redraw(fdf);
	return (0);
}

void	close_program(t_fdf *fdf)
{
	free_map(fdf->map, fdf->map->max_y, fdf->map->max_x);
	free(fdf);
	exit(0);
}
