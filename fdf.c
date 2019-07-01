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

void	create_window(int max_x, int max_y, t_list *coord_list)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		gap;
	int	 	start_x;
	int		start_y;
	int		targetX;
	int		targetY;
	int 	midX;
	int 	midY;
	t_coord	*coord;
	int 	myZ;

	mlx_ptr = mlx_init();
	printf("max_x: %d\n", max_x);
	if (max_x > max_y)
		gap = 600 / max_x;
	else
		gap = 600 / max_y;
	win_ptr = mlx_new_window(mlx_ptr, 200 + max_x * gap , 200 + max_y * gap, "fdf");
	start_x = 100;
	start_y = 100;
	midX = max_x / 2;
	midY = max_y / 2;
	coord = (t_coord *)coord_list->content;
	myZ = (int)coord->z;
	while (start_y <= max_y * gap + 100)
	{
		start_x = 100;
		while (start_x <= max_x * gap + 100)
		{
			targetX = (start_x - start_y) * cos(0.46373398) + midX * gap;
			targetY = -(myZ * 5) + (start_x + start_y) * sin(0.46373398);
			if ((start_x - 100) % gap == 0)
				mlx_pixel_put(mlx_ptr, win_ptr, targetX, targetY, get_color(myZ));
			else if ((start_y - 100) % gap == 0) 
				mlx_pixel_put(mlx_ptr, win_ptr, targetX, targetY, get_color(myZ));
			if ((start_y - 100) % gap == 0 && (start_x - 100) % gap == 0)
			{
				if (coord_list)
				{
					coord_list = coord_list->next;
					if (coord_list)
					{
						coord = (t_coord *)coord_list->content;
						if (myZ != (int)coord->z)
						{
							myZ = (int)coord->z;
							//line_bresen(targetX, targetY, coord->x * gap, coord->y * gap, mlx_ptr, win_ptr);
						}
					}
				}
			}
			start_x++;
			// printf("y:%d x:%d\n", start_y, start_x);

		}
		start_y++;
	}
	mlx_loop(mlx_ptr);
}

/*void	draw_bresen_lines(int max_x, int max_y, t_list *coord_list)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		gap;
	int	 	start_x;
	int		start_y;
	int 	midX;
	int 	midY;
	t_coord	*coord;
	int 	z;
	int 	x1;
	int 	y1;
	int		i;
	int		j;

	mlx_ptr = mlx_init();
	printf("max_x: %d\n", max_x);
	if (max_x > max_y)
		gap = 600 / max_x;
	else
		gap = 600 / max_y;
	win_ptr = mlx_new_window(mlx_ptr, 200 + max_x * gap , 200 + max_y * gap, "fdf");
	start_x = 100;
	start_y = 100;
	midX = max_x / 2;
	midY = max_y / 2;
	i = 0;
	j = 0;
	while (coord_list)
	{
		coord = (t_coord *)coord_list->content;
		start_x = 100 + coord->x * gap;
		start_y = 100 + coord->y * gap;
		z = (int)coord->z;
		coord_list = coord_list->next;
		if (coord_list)
		{
			coord = (t_coord *)coord_list->content;
			x1 = 100 + coord->x * gap;
			y1 = 100 + coord->y * gap;
			iso_projection(&start_x, &start_y, z, midX * gap);
			iso_projection(&x1, &y1, coord->z, midX * gap);
			line_bresen(start_x, start_y, x1, y1, mlx_ptr, win_ptr);
		}
	}
	mlx_loop(mlx_ptr);
}*/

t_coord	get_projected_coord(t_coord *old_coord, int gap, int midX, int offset_y)
{
	t_coord	coord;
	int		x;
	int		y;
	int		z;

	x = old_coord->x * gap;
	y = old_coord->y * gap;
	z = old_coord->z;
	iso_projection(&x, &y, z, midX * gap);
	coord.x = x + midX * gap;
	coord.y = y - offset_y;
	coord.z = z;
	coord.color = old_coord->color;
	return (coord);
}

int		get_offset_y(t_coord *last_coord, int center)
{
	int offset;
	int projected_y;
	int projected_x;

	projected_x = last_coord->x;
	projected_y = last_coord->y;
	iso_projection(&projected_x, &projected_y, last_coord->z, center);
	if (projected_y > WINDOW_HEIGHT)
		offset = WINDOW_HEIGHT - projected_y;
	else
		offset = 0;
	return (offset);

}

/*void	draw_bresen_lines_array(int max_x, int max_y, t_coord ***coord_array)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		gap;
	int 	midX;
	int 	midY;
	int		i;
	int		j;
	t_coord	start_coord;
	t_coord	end_coord;
	int 	offset_y;

	mlx_ptr = mlx_init();
	printf("max_x: %d\n", max_x);
	if (max_x > max_y)
		gap = (WINDOW_WIDTH / 2) / max_x;
	else
		gap = (WINDOW_WIDTH / 2) / max_y;
	printf("gap: %d\n", gap);
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH , WINDOW_HEIGHT, "fdf");
	midX = max_x / 2;
	midY = max_y / 2;
	offset_y = get_offset_y(coord_array[max_y][max_x], midX * gap);
	i = 0;
	while (i <= max_y)
	{
		j = 0;
		while (j <= max_x)
		{
			start_coord = get_projected_coord(coord_array[i][j], gap, midX, offset_y);
			if (j <= max_x - 1)
			{
				end_coord = get_projected_coord(coord_array[i][j + 1], gap, midX, offset_y);
				line_bresen(start_coord, end_coord, mlx_ptr, win_ptr);
			}
			if (i <= max_y - 1)
			{
				end_coord = get_projected_coord(coord_array[i + 1][j], gap, midX, offset_y);
				line_bresen(start_coord, end_coord, mlx_ptr, win_ptr);
			}
			j++;
		}
		i++;
	}
	mlx_loop(mlx_ptr);
}*/

t_fdf	*init_fdf()
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
	return (fdf);
}

void	draw_with_image(int max_x, int max_y, t_coord ***coord_array)
{
	t_fdf	*fdf;
	int 	midX;
	int 	midY;
	int		i;
	int		j;
	t_coord	start_coord;
	t_coord	end_coord;
	int 	offset_y;
	int		gap;

	fdf = init_fdf();
	if (max_x > max_y)
		gap = (WINDOW_WIDTH / 2/* - 2 * OFFSET*/) / max_x;
	else
		gap = (WINDOW_WIDTH / 2/* - 2 * OFFSET*/) / max_y;
	midX = max_x / 2;
	midY = max_y / 2;
	offset_y = get_offset_y(coord_array[max_y][max_x], midX * gap);
	i = 0;
	while (i <= max_y)
	{
		j = 0;
		while (j <= max_x)
		{
			start_coord = get_projected_coord(coord_array[i][j], gap, midX, offset_y);
			if (j <= max_x - 1)
			{
				end_coord = get_projected_coord(coord_array[i][j + 1], gap, midX, offset_y);
				line_bresen(start_coord, end_coord, fdf);
			}
			if (i <= max_y - 1)
			{
				end_coord = get_projected_coord(coord_array[i + 1][j], gap, midX, offset_y);
				line_bresen(start_coord, end_coord, fdf);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->window, fdf->image, 0, 0);
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
