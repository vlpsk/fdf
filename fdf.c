/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:57:02 by sgisele           #+#    #+#             */
/*   Updated: 2019/05/29 17:57:04 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include "math.h"

int		get_color(int z, t_fdf *fdf)
{
	int color;

	if (z > 0) 
		color = 0xFBA257;
	else if (z < 0)
		color = 0x4874BF;
	else
		color = fdf->base_color;
	return (color);
}

void 	free_coord_array(t_coord ***coord_array, int max_y, int max_x)
{
	int i;
	int j;

	i = 0;
	while (i <= max_y)
	{
		j = 0;
		while (j <= max_x)
		{
			free(coord_array[i][j]);
			j++;
		}
		free(coord_array[i]);
		i++;
	}
	free(coord_array);
}

int		get_light(int start, int end, double percentage)
{
	int	light;

	light = (int)((1 - percentage) * start + percentage * end);
	return (light);
}

double	get_percent(int start, int end, int current)
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

int		get_gradient(t_coord start_coord, t_coord end_coord, int x, int y)
{
	double	percentage;
	int		red;
	int		green;
	int		blue;

	if (abs(end_coord.x - start_coord.x) > abs(end_coord.y - start_coord.y))
		percentage = get_percent(start_coord.x, end_coord.x, x);
	else
		percentage = get_percent(start_coord.y, end_coord.y, y);
	red = get_light((start_coord.color >> 16) & 0xFF, (end_coord.color >> 16) & 0xFF, percentage);
	green = get_light((start_coord.color >> 8) & 0xFF, (end_coord.color >> 8) & 0xFF, percentage);
	blue = get_light(start_coord.color & 0xFF, end_coord.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void	pixel_put(t_fdf *fdf, int x, int y, int color)
{
	int i;

	i = 0;
	if (!(x > WINDOW_WIDTH - 300 && y < 300))
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
			//printf("i: %d\n", i);
			//printf("addresses: %zu\n", ft_strlen(fdf->addresses));
			fdf->addresses[i] = color;
			fdf->addresses[++i] = color >> 8;
			fdf->addresses[++i] = color >> 16;
		}
	}
}

void	line_bresen(t_coord start_coord, t_coord end_coord, /*void *mlx_ptr, void *win_ptr,*/ t_fdf *fdf)
{
	int	error;
	int	diry;
	int dirx;
	int	x;
	int	y;

	//printf("x0: %d, y0: %d, x1: %d, y1: %d\n", start_coord.x, start_coord.y, end_coord.x, end_coord.y);
	diry = end_coord.y - start_coord.y;
	if (diry > 0)
		diry = 1;
	else if (diry < 0)
		diry = -1;
	dirx = start_coord.x < end_coord.x ? 1 : -1;
	x = start_coord.x;
	y = start_coord.y;
	error = abs(end_coord.x - start_coord.x) - abs(end_coord.y - start_coord.y);
	//mlx_pixel_put(mlx_ptr, win_ptr, end_coord.x, end_coord.y, get_color(start_coord.z));
	/*if (fdf->color_info)
		pixel_put(fdf, end_coord.x, end_coord.y, end_coord.color);
	else
		pixel_put(fdf, end_coord.x, end_coord.y, fdf->base_color);*/
	if (fdf->color_info == 0)
	{
		start_coord.color = get_color(start_coord.old_z, fdf);
		end_coord.color = get_color(end_coord.old_z, fdf);
	}
	pixel_put(fdf, end_coord.x, end_coord.y, end_coord.color);
	while (x != end_coord.x || y != end_coord.y)
	{
		//mlx_pixel_put(mlx_ptr, win_ptr, x, y, get_gradient(start_coord, end_coord, x, y));
		/*if (fdf->color_info)
			pixel_put(fdf, x, y, get_gradient(start_coord, end_coord, x, y));
		else
			pixel_put(fdf, x, y, fdf->base_color);*/
		pixel_put(fdf, x, y, get_gradient(start_coord, end_coord, x, y));
		if (2 * error > -1 * abs(end_coord.y - start_coord.y) && x != end_coord.x)
		{
			error -= abs(end_coord.y - start_coord.y);
			x += dirx;
		}
		if (2 * error < abs(end_coord.x - start_coord.x) && y != end_coord.y)
		{
			error += abs(end_coord.x - start_coord.x);
			y += diry;
		}
	}
}

void	iso_projection(int *x, int *y, int z, int center)
{
	*x = (*x - *y) * cos(0.523599) + center;
	*y = -1 * z + (*x + *y) * sin(0.523599);
}

void	parallel_projection(int *x, int *y, int z)
{
	*x = *x;
	*y = *y * cos(0) + z * sin(0);
}

void 	rotate_x(int *y, int *z, double angle)
{
	int		previous;

	previous = *y;
	*y = previous * cos(angle) + *z * sin(angle);
	*z = (-1) * previous * sin(angle) + *z * cos(angle);
}

void	rotate_y(int *x, int *z, double angle)
{
	int		previous;

	previous = *x;
	*x = previous * cos(angle) + *z * sin(angle);
	*z = -1 * previous * sin(angle) + *z * cos(angle);
}

void	rotate_z(int *x, int *y, double angle)
{
	int		previous;

	previous = *x;
	*x = previous * cos(angle) - *y * sin(angle);
	*y = previous * sin(angle) + *y * cos(angle);
}


t_coord	get_projected_coord(t_coord *old_coord, int gap, int midX, t_fdf *fdf)
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
	//printf("after rotation: x: %d, y: %d, z %d\n", x, y, z);
	if (fdf->projection == ISO)
		iso_projection(&x, &y, z, midX * gap);
	coord.x = x + (fdf->offset).offset_x + (fdf->camera).move_x;
	coord.y = y + (fdf->offset).offset_y + (fdf->camera).move_y;
	coord.z = z;
	coord.color = old_coord->color;
	coord.old_z = old_coord->old_z;
	return (coord);
}

t_camera	init_camera()
{
	t_camera	camera;

	camera.move_x = 0;
	camera.move_y = 0;
	camera.x_angle = -1;
	camera.y_angle = 0.0;
	camera.z_angle = 0.0;
	return (camera);
}

t_offset	init_offset()
{
	t_offset	offset;

	offset.offset_x = 0;
	offset.offset_y = 0;
	return (offset);
}

t_map	*init_map(int max_x, int max_y, t_coord ***coord_array)
{
	t_map	*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	map->max_x = max_x;
	map->max_y = max_y;
	map->coord_array = coord_array;
	return (map);
}

t_mouse	init_mouse()
{
	t_mouse	mouse;

	mouse.is_pressed = 0;
	mouse.x = 0;
	mouse.y = 0;
	mouse.previous_x = 0;
	mouse.previous_y = 0;
	return (mouse);
}

t_fdf	*init_fdf(int max_x, int max_y, t_coord ***coord_array, int color_info)
{
	t_fdf	*fdf;

	if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf))))
		return (NULL);
	fdf->mlx_ptr = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	fdf->image = mlx_new_image(fdf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->bits_per_pixel = 24;
	fdf->size_line = WINDOW_WIDTH;
	fdf->endian = 0;
	fdf->addresses = mlx_get_data_addr(fdf->image, &(fdf->bits_per_pixel), &(fdf->size_line),
		&(fdf->endian));
	fdf->zoom = 1;
	fdf->multiplier = 1;
	fdf->color_info = color_info;
	fdf->base_color = (fdf->color_info) ? 0xFFFFFF : 0xF44242;
	if (!(fdf->map = init_map(max_x, max_y, coord_array)))
	{
		free(fdf);
		return (NULL);
	}
	fdf->camera = init_camera();
	fdf->offset = init_offset();
	fdf->projection = PARALLEL;
	fdf->mouse = init_mouse();
	return (fdf);
}

t_coord		project_offset(t_coord *first, int val, int gap, t_fdf *fdf)
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

t_offset	calculate_offset(t_coord *first, t_coord *last, int val, int gap, t_fdf *fdf)
{
	t_offset	offset;
	t_coord		start;
	t_coord		end;

	start = project_offset(first, val, gap, fdf);
	end = project_offset(last, val, gap, fdf);
	printf("start.x: %d, end.x: %d\n", start.x, end.x);
	offset.offset_x = WINDOW_WIDTH / 2 - (start.x + ((end.x - start.x) / 2));
	printf("Center.x = %d, image.x = %d, offset.x = %d\n", WINDOW_WIDTH / 2, (start.x + ((end.x - start.x) / 2)), offset.offset_x);
	offset.offset_y = WINDOW_HEIGHT / 2 - (start.y + ((end.y - start.y) / 2));
	//offset.offset_y = 0;
	return (offset);
}

void	print_menu(t_fdf *fdf)
{
	int y;

	y = 0;
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 200, y += 20, 0xFFFFFF, "How to Use");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30, 0xFFFFFF, "Projection:");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "Parallel: P");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "ISO: I");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 35, 0xFFFFFF, "Zoom: scroll");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30, 0xFFFFFF, "Flatten: +/-");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30, 0xFFFFFF, "Move: arrows");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30, 0xFFFFFF, "Rotate:");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "Mouse Press and Drag");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 275, y += 20, 0xFFFFFF, "or:");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "X-Axis: W/S");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "Y-Axis: Q/E");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "Z-Axis: A/D");
	y = WINDOW_HEIGHT - 200;
	mlx_string_put(fdf->mlx_ptr, fdf->window, 25, y, 0xFFFFFF, "Change color");
	mlx_string_put(fdf->mlx_ptr, fdf->window, 25, y += 30, 0xFFFFFF, "decrement/increment");
	mlx_string_put(fdf->mlx_ptr, fdf->window, 50, y += 20, 0xFFFFFF, "Red: R/T");
	mlx_string_put(fdf->mlx_ptr, fdf->window, 50, y += 20, 0xFFFFFF, "Green: G/H");
	mlx_string_put(fdf->mlx_ptr, fdf->window, 50, y += 20, 0xFFFFFF, "Blue: B/N");
}

void	draw(t_fdf	*fdf)
{
	int 		midX;
	int 		midY;
	int			i;
	int			j;
	t_coord		start_coord;
	t_coord		end_coord;
	int			gap;
	
	if (fdf->map->max_x > fdf->map->max_y)
		gap = (WINDOW_WIDTH / 2) / fdf->map->max_x * fdf->zoom;
	else
		gap = (WINDOW_WIDTH / 2) / fdf->map->max_y * fdf->zoom;
	midX = (fdf->map->max_x) / 2;
	midY = (fdf->map->max_y) / 2;
	fdf->offset = calculate_offset((fdf->map->coord_array)[0][0], (fdf->map->coord_array)[fdf->map->max_y][fdf->map->max_x], midX * gap, gap, fdf);
	i = 0;
	while (i <= fdf->map->max_y)
	{
		j = 0;
		while (j <= fdf->map->max_x)
		{
			start_coord = get_projected_coord((fdf->map->coord_array)[i][j], gap, midX, fdf);
			if (j <= fdf->map->max_x - 1)
			{
				end_coord = get_projected_coord((fdf->map->coord_array)[i][j + 1], gap, midX, fdf);
				line_bresen(start_coord, end_coord, fdf);
			}
			if (i <= fdf->map->max_y - 1)
			{
				end_coord = get_projected_coord((fdf->map->coord_array)[i + 1][j], gap, midX, fdf);
				line_bresen(start_coord, end_coord, fdf);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->window, fdf->image, 0, 0);
}

void	redraw(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->image);
	fdf->image = mlx_new_image(fdf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->addresses = mlx_get_data_addr(fdf->image, &(fdf->bits_per_pixel), &(fdf->size_line),
		&(fdf->endian));
	draw(fdf);
	print_menu(fdf);
}

int		zoom(int keycode, t_fdf *fdf)
{
	if (keycode == 4)
		(fdf->zoom)++;
	else if ((keycode == 5) && (fdf->zoom) > 1)
		(fdf->zoom)--;
	ft_putnbr(fdf->zoom);
	redraw(fdf);
	return (0);
}

int		enlarge(int keycode, t_fdf *fdf)
{
	if (keycode == MAIN_KEY_PLUS || keycode ==  KEY_PLUS)
		(fdf->multiplier)++;
	else if ((keycode == MAIN_KEY_MINUS || keycode == KEY_MINUS) && (fdf->multiplier) > 1)
		(fdf->multiplier)--;
	redraw(fdf);
	return (0);
}

int		move(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_RIGHT)
		(fdf->camera).move_x = (fdf->camera).move_x - 10;
	else if (keycode == KEY_LEFT)
		(fdf->camera).move_x = (fdf->camera).move_x + 10;
	else if (keycode == KEY_DOWN)
		(fdf->camera).move_y = (fdf->camera).move_y - 10;
	else if (keycode == KEY_UP)
		(fdf->camera).move_y = (fdf->camera).move_y + 10;
	redraw(fdf);
	return (0);
}

int 	rotate(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_D)
		(fdf->camera).y_angle = (fdf->camera).y_angle + 0.02;
	else if (keycode == KEY_A)
		(fdf->camera).y_angle = (fdf->camera).y_angle - 0.02;
	else if (keycode == KEY_W)
		(fdf->camera).x_angle = (fdf->camera).x_angle + 0.02;
	else if (keycode == KEY_S)
		(fdf->camera).x_angle = (fdf->camera).x_angle - 0.02;
	else if (keycode == KEY_E)
		(fdf->camera).z_angle = (fdf->camera).z_angle + 0.02;
	else if (keycode == KEY_Q)
		(fdf->camera).z_angle = (fdf->camera).z_angle - 0.02;
	redraw(fdf);
	return (0);
}

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

int 	change_base_color(int keycode, t_fdf *fdf)
{
	int		red;
	int 	green;
	int 	blue;

	red = fdf->base_color >> 16 & 0xFF;
	green = fdf->base_color >> 8 & 0xFF;
	blue = fdf->base_color & 0xFF;
	printf("red: %d, green: %d, blue: %d\n", red, green, blue);
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
	printf("AFTER red: %d, green: %d, blue: %d\n", red, green, blue);
	fdf->base_color = ((red << 16) | (green << 8) | blue);
	redraw(fdf);
	return (0);
}

void	close_program(t_fdf *fdf)
{
	free_coord_array(fdf->map->coord_array, fdf->map->max_y, fdf->map->max_x);
	free(fdf->map);
	free(fdf);
	exit(0);
}

int		key_press(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_ESCAPE)
		close_program(fdf);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		zoom(keycode, fdf);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_DOWN || keycode == KEY_UP)
		move(keycode, fdf);
	else if (keycode == MAIN_KEY_PLUS || keycode == MAIN_KEY_MINUS)
		enlarge(keycode, fdf);
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D || keycode == KEY_W ||
		keycode == KEY_Q || keycode == KEY_E)
		rotate(keycode, fdf);
	else if (keycode == KEY_P || keycode == KEY_I)
		set_projection(keycode, fdf);
	else if (keycode == KEY_R || keycode == KEY_G || keycode == KEY_B || keycode == KEY_T ||
		keycode == KEY_H || keycode == KEY_N)
		change_base_color(keycode, fdf);
	return (0);
}

int 	mouse_press(int keycode, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (keycode == 4 || keycode == 5)
	{
		zoom(keycode, fdf);
		fdf->mouse.x = x;
		fdf->mouse.y = y;
	}
	else if (keycode == 1 || keycode == 2)
		fdf->mouse.is_pressed = 1;
	return (0);
}

int		mouse_moved(int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	fdf->mouse.previous_x = fdf->mouse.x;
	fdf->mouse.previous_y = fdf->mouse.y;
	fdf->mouse.x = x;
	fdf->mouse.y = y;
	if (fdf->mouse.is_pressed)
	{
		fdf->camera.x_angle += (x - fdf->mouse.previous_x) * 0.02;
		fdf->camera.y_angle += (y - fdf->mouse.previous_y) * 0.02;
		redraw(fdf);
	}
	return (0);
}

int		mouse_released(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)button;
	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	fdf->mouse.is_pressed = 0;
	return (0);
}

void	draw_with_image(int max_x, int max_y, t_coord ***coord_array, int color_info)
{
	t_fdf	*fdf;
	
	if (!(fdf = init_fdf(max_x, max_y, coord_array, color_info)))
	{
		free_coord_array(coord_array, max_y, max_x);
		exit(0);
	}
	draw(fdf);
	print_menu(fdf);
	mlx_key_hook(fdf->window, key_press, (void *)fdf);
	//mlx_mouse_hook(fdf->window, mouse_press, (void *)fdf);
	//mlx_hook(fdf->window, 5, 0L, mouse_press, (void *)fdf);
	mlx_hook(fdf->window, 6, 0L, mouse_moved, (void *)fdf);
	mlx_hook(fdf->window, 5, 0L, mouse_released, (void *)fdf);
	mlx_hook(fdf->window, 4, 0L, mouse_press, (void *)fdf);
	mlx_loop(fdf->mlx_ptr);
}

void	ft_lstreverse(t_list **begin_list)
{
	t_list *first;
	t_list *second;
	t_list *begin;

	begin = *begin_list;
	if (begin == NULL || begin->next == NULL)
		return ;
	first = begin->next;
	second = first->next;
	begin->next = NULL;
	if (second == NULL)
	{
		first->next = begin;
		*begin_list = first;
		return ;
	}
	while (second)
	{
		first->next = begin;
		begin = first;
		first = second;
		second = second->next;
	}
	first->next = begin;
	*begin_list = first;
}

int		ft_len(char **array)
{
	int count;

	count = 0;
	while (array[count] != 0)
		count++;
	return (count);
}

int		ft_hextoi(char *hex)
{
	int	i;
	int	val;
	int	byte;

	val = 0;
	i = 0;
	while (hex[i])
	{
		if (hex[i] == '0' && hex[i + 1] == 'x')
			i = i + 2;
		else
		{
			byte = hex[i];
			if (byte >= '0' && byte <= '9')
				byte = byte - '0';
			else if (byte >= 'a' && byte <= 'f')
				byte = byte - 'a' + 10;
			else if (byte >= 'A' && byte <= 'F')
				byte = byte - 'A' + 10;
			val = (val << 4) | (byte & 0xF);
			i++;
		}
	}
	return (val);
}

int		is_decimal(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_ishex(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
		return (1);
	else
		return (0);
}

int		is_hexadecimal_color(char *str)
{
	int i;

	i = 0;
	if (str[0] == '0' && str[1] == 'x')
	{
		if (ft_strlen(str) > 8)
			return (0);
		i = 2;
	}
	else
	{
		if (ft_strlen(str) > 6)
			return (0);
	}
	while (str[i] != '\0')
	{
		if (ft_ishex(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	free_parsed(char **parsed)
{
	int i;

	i = 0;
	while (parsed[i] != 0)
	{
		free(parsed[i]);
		i++;
	}
	free(parsed);
}

t_list	*coord_iteration(char **parsed, int *x, int *y, t_list *coord_list, int *color_info)
{
	t_coord	*coord;
	char	**split_value;

	while (parsed[*x] != 0)
	{
		if (!(coord = (t_coord *)malloc(sizeof(t_coord))))
			return (NULL);
		coord->x = *x;
		coord->y = *y;
		split_value = ft_strsplit(parsed[*x], ',');
		if (ft_len(split_value) == 2)
		{
			if (is_decimal(split_value[0]))
			{
				coord->z = ft_atoi(split_value[0]);
				coord->old_z = coord->z;
			}
			else
				return (NULL);
			if (is_hexadecimal_color(split_value[1]))
			{
				coord->color = ft_hextoi(split_value[1]);
				*color_info = 1;
			}
			else
				return (NULL);
		}
		else
		{
			if (is_decimal(parsed[*x]))
			{
				coord->z = ft_atoi(parsed[*x]);
				coord->old_z = coord->z;
			}
			else
				return (NULL);
			coord->color = 0xF44242;
		}
		if (coord_list == NULL)
			coord_list = ft_lstnew(coord, sizeof(t_coord));
		else
			ft_lstadd(&coord_list, ft_lstnew(coord, sizeof(t_coord)));
		free_parsed(split_value);
		*x = *x + 1;
	}
	return (coord_list);
}

int 	check_number_of_elements(char **parsed, int x)
{
	if (ft_len(parsed) != x)
		return (0);
	else
		return (1);
}

void	del_list(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

void	free_coord_list_and_exit(t_list *coord_list)
{
	void	(*f)(void *, size_t);

	f = del_list;
	ft_lstdel(&coord_list, f);
	ft_putendl("map error");
	exit(0);
}

void	free_coord_list_and_exit_parsed(t_list *coord_list, char **parsed)
{
	void	(*f)(void *, size_t);

	f = del_list;
	ft_lstdel(&coord_list, f);
	free_parsed(parsed);
	ft_putendl("map error");
	exit(0);
}

t_list	*get_coords(int fd, int *max_x, int *y, int *color_info)
{
	int		x;
	char	**parsed;
	t_list	*coord_list;
	char	*line;

	coord_list = NULL;
	while (get_next_line(fd, &line))
	{
		parsed = ft_strsplit(line, ' ');
		if (coord_list)
		{
			printf("x: %d, array_len: %d\n", x, ft_len(parsed));
			if (check_number_of_elements(parsed, x))
			{
				x = 0;
				if (!(coord_list = coord_iteration(parsed, &x, y, coord_list, color_info)))
					free_coord_list_and_exit_parsed(coord_list, parsed);
			}
			else
				free_coord_list_and_exit_parsed(coord_list, parsed);
		}
		else
		{
			x = 0;
			if (!(coord_list = coord_iteration(parsed, &x, y, coord_list, color_info)))
				free_coord_list_and_exit_parsed(coord_list, parsed);
		}
		*y = *y + 1;
		free_parsed(parsed);
	}
	*max_x = x - 1;
	*y = *y - 1;
	return (coord_list);
}

t_coord ***convert_to_array(t_list *coord_list, int max_x, int max_y)
{
	//void	(*f)(void *, size_t);
	t_coord	***coord_array;
	t_coord	**coords;
	int		i;
	int		j;
	t_list	*begin_list;

	i = 0;
	//f = del_list;
	begin_list = coord_list;
	printf("max_x: %d, max_y: %d\n", max_x, max_y);
	if (!(coord_array = (t_coord ***)malloc(sizeof(t_coord **) * (max_y + 1))))
		return (NULL);
	while (i <= max_y)
	{
		if (!(coords = (t_coord **)malloc(sizeof(t_coord *) * (max_x + 1))))
		{
			free_coord_array(coord_array, i, j);
			free_coord_list_and_exit(coord_list);
		}
		j = 0;
		while (j <= max_x)
		{
			if (coord_list)
			{
				coords[j] = (t_coord *)coord_list->content;
				coord_list = coord_list->next;
			}
			j++;
		}
		coord_array[i] = coords;
		i++;
	}
	//ft_lstdel(&coord_list, f);
	coord_list = begin_list;
	//ft_lstdel(&coord_list, f);
	return (coord_array);
}

void	read_map(char *filename)
{
	int		fd;
	int		max_y;
	int		max_x;
	int		color_info;
	t_list	*coord_list;
	t_coord	***coord_array;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	max_y = 0;
	coord_list = NULL;
	max_x = 0;
	color_info = 0;
	coord_list = get_coords(fd, &max_x, &max_y, &color_info);
	ft_lstreverse(&coord_list);
	coord_array = convert_to_array(coord_list, max_x, max_y);
	//create_window(max_x, y, coord_list);
	//draw_bresen_lines(max_x, max_y, coord_list);
	//draw_bresen_lines_array(max_x, max_y, coord_array);
	draw_with_image(max_x, max_y, coord_array, color_info);
}

char		*ft_scan(char *buff, char *str, char *tmp)
{
	int		index;

	index = 0;
	while (read(0, buff, 1))
	{
		if (index != 0)
		{
			free(tmp);
			tmp = (char *)malloc(sizeof(char) * index);
			tmp = str;
			free(str);
		}
		str = (char *)malloc(sizeof(char) * (index + 1));
		if (tmp != NULL)
			str = tmp;
		if (buff[0] == '\n' || buff[0] == EOF || buff[0] == '\r')
			break ;
		str[index] = buff[0];
		str[index + 1] = '\0';
		index++;
	}
	if (buff[0] != '\n')
		write(1, "\n", 1);
	return (str);
}

int		main(int argc, char **argv)
{

	/*if (argc != 2)
	{
		ft_putendl("usage: ./fdf source_file");
		return (1);
	}
	else
		read_map(argv[1]);
	return (0);*/

	char scanbuff[1];
	char *str;
	char *tmp;

	if (argc < 2)
	{
		str = NULL;
		tmp = NULL;
		str = ft_scan(scanbuff, str, tmp);
		read_map(str);
	}
	else if (argc == 2)
		read_map(argv[1]);
	else
	{
		ft_putendl("usage: ./fdf source_file");
		return (1);
	}
}
