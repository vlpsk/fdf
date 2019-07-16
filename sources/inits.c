/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:07:02 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:07:04 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_offset	init_offset(void)
{
	t_offset	offset;

	offset.offset_x = 0;
	offset.offset_y = 0;
	return (offset);
}

t_map		*init_map(int max_x, int max_y, t_coord ***coord_array,
	t_list *coord_list)
{
	t_map	*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->max_x = max_x;
	map->max_y = max_y;
	map->coord_array = coord_array;
	map->coord_list = coord_list;
	return (map);
}

t_mouse		init_mouse(void)
{
	t_mouse	mouse;

	mouse.is_pressed = 0;
	mouse.x = 0;
	mouse.y = 0;
	mouse.previous_x = 0;
	mouse.previous_y = 0;
	return (mouse);
}

t_camera	init_camera(void)
{
	t_camera	camera;

	camera.move_x = 0;
	camera.move_y = 0;
	camera.x_angle = -1;
	camera.y_angle = 0.0;
	camera.z_angle = 0.0;
	return (camera);
}

t_fdf		*init_fdf(t_map *map, t_color *color_info)
{
	t_fdf	*fdf;

	if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf))))
		return (NULL);
	fdf->mlx_ptr = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
		"fdf");
	fdf->image = mlx_new_image(fdf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->bits_per_pixel = 24;
	fdf->size_line = WINDOW_WIDTH;
	fdf->endian = 0;
	fdf->addresses = mlx_get_data_addr(fdf->image, &(fdf->bits_per_pixel),
		&(fdf->size_line), &(fdf->endian));
	fdf->zoom = 1;
	fdf->gap = 0;
	fdf->multiplier = 1;
	fdf->color_info = color_info;
	fdf->base_color = (fdf->color_info->color_info) ? 0xFFFFFF : BASE_COLOR;
	fdf->map = map;
	fdf->camera = init_camera();
	fdf->offset = init_offset();
	fdf->projection = PARALLEL;
	fdf->mouse = init_mouse();
	return (fdf);
}
