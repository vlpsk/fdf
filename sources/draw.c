/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:30:08 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:30:13 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	t_coord	project_offset(t_coord *first, int val, int gap, t_fdf *fdf)
{
	t_coord		start;
	int			x;
	int			y;
	int			z;

	x = first->x * gap;
	y = first->y * gap;
	z = first->z * (fdf->multiplier);
	rotate_x(&y, &z, fdf->camera.x_angle);
	rotate_y(&x, &z, fdf->camera.y_angle);
	rotate_z(&x, &y, fdf->camera.z_angle);
	if (fdf->projection == ISO)
		iso_projection(&x, &y, z, val);
	start.x = x;
	start.y = y;
	start.z = z;
	start.old_z = z;
	start.color = 0xFFFFFF;
	return (start);
}

void			draw_with_image(int max_x, int max_y, t_map *map,
	int color_info)
{
	t_fdf	*fdf;

	if (!(fdf = init_fdf(map, color_info)))
	{
		free_map(map, max_y, max_x);
		exit(0);
	}
	draw(fdf);
	print_menu(fdf);
	mlx_key_hook(fdf->window, key_press, (void *)fdf);
	mlx_hook(fdf->window, 6, 0L, mouse_moved, (void *)fdf);
	mlx_hook(fdf->window, 5, 0L, mouse_released, (void *)fdf);
	mlx_hook(fdf->window, 4, 0L, mouse_press, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
}

static	void	draw_iteration(t_fdf *fdf, int midx, int gap,
	t_coord ***coord_array)
{
	int			i;
	int			j;
	t_coord		start_coord;
	t_coord		end_coord;

	i = -1;
	while (++i <= fdf->map->max_y)
	{
		j = -1;
		while (++j <= fdf->map->max_x)
		{
			start_coord = proj(coord_array[i][j], gap, midx, fdf);
			if (j <= fdf->map->max_x - 1)
			{
				end_coord = proj(coord_array[i][j + 1], gap, midx, fdf);
				line_bresen(start_coord, end_coord, fdf);
			}
			if (i <= fdf->map->max_y - 1)
			{
				end_coord = proj(coord_array[i + 1][j], gap, midx, fdf);
				line_bresen(start_coord, end_coord, fdf);
			}
		}
	}
}

void			draw(t_fdf *fdf)
{
	int			midx;
	int			midy;
	int			gap;
	t_coord		***coord_array;

	coord_array = fdf->map->coord_array;
	if (fdf->map->max_x > fdf->map->max_y)
		fdf->gap = (WINDOW_WIDTH / 2) / fdf->map->max_x * fdf->zoom;
	else
		fdf->gap = (WINDOW_WIDTH / 2) / fdf->map->max_y * fdf->zoom;
	gap = fdf->gap;
	midx = (fdf->map->max_x) / 2;
	midy = (fdf->map->max_y) / 2;
	fdf->offset = calculate_offset((fdf->map->coord_array)[0][0],
		(fdf->map->coord_array)[fdf->map->max_y][fdf->map->max_x], midx * gap,
		fdf);
	draw_iteration(fdf, midx, gap, coord_array);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->window, fdf->image, 0, 0);
}

t_offset		calculate_offset(t_coord *first, t_coord *last, int val,
	t_fdf *fdf)
{
	t_offset	offset;
	t_coord		start;
	t_coord		end;

	start = project_offset(first, val, fdf->gap, fdf);
	end = project_offset(last, val, fdf->gap, fdf);
	offset.offset_x = WINDOW_WIDTH / 2 - (start.x + ((end.x - start.x) / 2));
	offset.offset_y = WINDOW_HEIGHT / 2 - (start.y + ((end.y - start.y) / 2));
	return (offset);
}
