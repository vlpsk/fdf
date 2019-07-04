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

int		get_color(int z)
{
	int color;

	if (z > 0) 
		color = 0xF44259;
	else
		color = 0xFFFFFF;
	return (color);
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
	pixel_put(fdf, end_coord.x, end_coord.y, get_color(end_coord.z));
	while (x != end_coord.x || y != end_coord.y)
	{
		//mlx_pixel_put(mlx_ptr, win_ptr, x, y, get_gradient(start_coord, end_coord, x, y));
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
	*y = -(z) + (*x + *y) * sin(0.523599);
}

void	apply_rotation(int *x, int *y, int *z, t_camera camera)
{
	*x = *x;
	*y = *y * cos(camera.x_angle) + *z * sin(camera.x_angle);
	*z = (-1) * *y * sin(camera.x_angle) + *z * cos(camera.x_angle);
	*x = *x * cos(camera.y_angle) + *z * sin(camera.y_angle);
	*y = *y;
	*z = (-1) * *x * sin(camera.y_angle) + *z * cos(camera.y_angle);
	*x = *x * cos(camera.z_angle) - *y * sin(camera.z_angle);
	*y = *x * sin(camera.z_angle) + *y * cos(camera.z_angle);
	*z = *z;
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
	apply_rotation(&x, &y, &z, fdf->camera);
	//printf("after rotation: x: %d, y: %d, z %d\n", x, y, z);
	iso_projection(&x, &y, z, midX * gap);
	coord.x = x - (fdf->offset).offset_x + (fdf->camera).move_x;
	coord.y = y - (fdf->offset).offset_y + (fdf->camera).move_y;
	coord.z = z;
	coord.color = old_coord->color;
	return (coord);
}

t_camera	init_camera()
{
	t_camera	camera;

	camera.move_x = 0;
	camera.move_y = 0;
	camera.x_angle = 0.0;
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

	map = (t_map *)malloc(sizeof(t_map));
	map->max_x = max_x;
	map->max_y = max_y;
	map->coord_array = coord_array;
	return (map);
}

t_fdf	*init_fdf(int max_x, int max_y, t_coord ***coord_array)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
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
	fdf->map = init_map(max_x, max_y, coord_array);
	fdf->camera = init_camera();
	fdf->offset = init_offset();
	return (fdf);
}

t_offset	calculate_offset(t_coord *center, int val, int gap, t_fdf *fdf)
{
	t_offset	offset;
	int			x;
	int			y;
	int			z;

	x = center->x * gap;
	y = center->y * gap;
	z = center->z * (fdf->multiplier);
	//printf("before projection: x: %d, y: %d\n", x, y);
	//printf("before rotation: x: %d, y: %d, z %d\n", x, y, z);
	apply_rotation(&x, &y, &z, fdf->camera);
	//printf("after rotation: x: %d, y: %d, z %d\n", x, y, z);
	iso_projection(&x, &y, z, val);
	//printf("after projection: x: %d, y: %d\n", x, y);
	offset.offset_x = x - WINDOW_WIDTH / 2;
	offset.offset_y = y - WINDOW_HEIGHT / 2;
	printf("offset_x: %d, offset_y: %d\n", offset.offset_x, offset.offset_y);
	return (offset);
}

void	print_menu(t_fdf *fdf)
{
	int y;

	y = 0;
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 200, y += 20, 0xFFFFFF, "How to Use");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 35, 0xFFFFFF, "Zoom: scroll");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30, 0xFFFFFF, "Flatten: +/-");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30, 0xFFFFFF, "Move: arrows");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30, 0xFFFFFF, "Rotate:");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "X-Axis: W/S");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "Y-Axis: Q/E");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20, 0xFFFFFF, "Z-Axis: A/D");
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
	fdf->offset = calculate_offset((fdf->map->coord_array)[midY][midX], midX * gap, gap, fdf);
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
		(fdf->camera).z_angle = (fdf->camera).z_angle + 0.02;
	else if (keycode == KEY_A)
		(fdf->camera).z_angle = (fdf->camera).z_angle - 0.02;
	else if (keycode == KEY_W)
		(fdf->camera).x_angle = (fdf->camera).x_angle + 0.02;
	else if (keycode == KEY_S)
		(fdf->camera).x_angle = (fdf->camera).x_angle - 0.02;
	else if (keycode == KEY_E)
		(fdf->camera).y_angle = (fdf->camera).y_angle + 0.02;
	else if (keycode == KEY_Q)
		(fdf->camera).y_angle = (fdf->camera).y_angle - 0.02;
	redraw(fdf);
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_ESCAPE)
		exit(1);
	if (keycode ==  KEY_PLUS || keycode == KEY_MINUS)
		zoom(keycode, fdf);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_DOWN || keycode == KEY_UP)
		move(keycode, fdf);
	else if (keycode == MAIN_KEY_PLUS || keycode == MAIN_KEY_MINUS)
		enlarge(keycode, fdf);
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D || keycode == KEY_W ||
		keycode == KEY_Q || keycode == KEY_E)
		rotate(keycode, fdf);
	return (0);
}

int 	mouse_press(int keycode, int x, int y, void *param)
{
	t_fdf	*fdf;
	t_coord	pressed;

	pressed.x = x;
	pressed.y = y;
	fdf = (t_fdf *)param;
	if (keycode == 4 || keycode == 5)
	{
		printf("%s\n", "I scrolled");
		zoom(keycode, fdf);
	}
	return (0);
}

void	draw_with_image(int max_x, int max_y, t_coord ***coord_array)
{
	t_fdf	*fdf;
	
	fdf = init_fdf(max_x, max_y, coord_array);
	draw(fdf);
	print_menu(fdf);
	mlx_key_hook(fdf->window, key_press, (void *)fdf);
	mlx_mouse_hook(fdf->window, mouse_press, (void *)fdf);
	//mlx_hook(fdf->window, 5, 0L, mouse_press, (void *)fdf);
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

t_list	*get_coords(int fd, int *max_x, int *y)
{
	int		x;
	char	**parsed;
	char	**split_value;
	t_coord	*coord;
	t_list	*coord_list;
	char	*line;

	coord_list = NULL;
	while (get_next_line(fd, &line))
	{
		x = 0;
		parsed = ft_strsplit(line, ' ');
		while (parsed[x] != 0)
		{
			coord = (t_coord *)malloc(sizeof(t_coord));
			coord->x = x;
			coord->y = *y;
			split_value = ft_strsplit(parsed[x], ',');
			if (ft_len(split_value) == 2)
			{
				coord->z = ft_atoi(parsed[x]);
				coord->color = ft_hextoi(split_value[1]);
			}
			else
			{
				coord->z = ft_atoi(parsed[x]);
				coord->color = get_color(ft_atoi(parsed[x]));
			}
			if (coord_list == NULL)
				coord_list = ft_lstnew(coord, sizeof(t_coord));
			else
				ft_lstadd(&coord_list, ft_lstnew(coord, sizeof(t_coord)));
			x++;
		}
		*y = *y + 1;
	}
	*max_x = x - 1;
	*y = *y - 1;
	return (coord_list);
}

t_coord ***convert_to_array(t_list *coord_list, int max_x, int max_y)
{
	t_coord	***coord_array;
	t_coord	**coords;
	int		i;
	int		j;

	i = 0;
	printf("max_x: %d, max_y: %d\n", max_x, max_y);
	coord_array = (t_coord ***)malloc(sizeof(t_coord **) * (max_y + 1));
	while (i <= max_y)
	{
		j = 0;
		coords = (t_coord **)malloc(sizeof(t_coord *) * (max_x + 1));
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
	return (coord_array);
}

void	read_map(char *filename)
{
	int		fd;
	int		max_y;
	int		max_x;
	t_list	*coord_list;
	t_coord	***coord_array;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	max_y = 0;
	coord_list = NULL;
	max_x = 0;
	coord_list = get_coords(fd, &max_x, &max_y);
	ft_lstreverse(&coord_list);
	coord_array = convert_to_array(coord_list, max_x, max_y);
	//create_window(max_x, y, coord_list);
	//draw_bresen_lines(max_x, max_y, coord_list);
	//draw_bresen_lines_array(max_x, max_y, coord_array);
	draw_with_image(max_x, max_y, coord_array);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		{
			ft_putendl("usage: ./fdf source_file");
			return (1);
		}
		else
			read_map(argv[1]);
		return (0);
}
