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

void	line_bresen(int x0, int y0, int x1, int y1, void *mlx_ptr, void *win_ptr)
{
	int	error;
	int	diry;
	int dirx;
	int	x;
	int	y;

	printf("x0: %d, y0: %d, x1: %d, y1: %d\n", x0, y0, x1, y1);
	diry = y1 - y0;
	if (diry > 0)
		diry = 1;
	else if (diry < 0)
		diry = -1;
	dirx = x0 < x1 ? 1 : -1;
	x = x0;
	y = y0;
	error = abs(x1 - x0) - abs(y1 - y0);
	/*while (x <= x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xF44259);
		error = error + abs(x1 - x0) / abs(y1 - y0);
		if (2 * error >= abs(x1 - x0))
		{
			y = y + diry;
			error = error - abs(x1 - x0);
		}
		x++;
	}*/
	while (x != x1  || y != y1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xF44259);
		if (2 * error > -1 * abs(y1 - y0))
		{
			error -= abs(y1 - y0);
			x += dirx;
		}
		if (2 * error < abs(x1 - x0))
		{
			error += abs(x1 - x0);
			y += diry;
		}
	}

}

int		get_color(int z)
{
	int color;

	if (z > 0) 
		color = 0xF44259;
	else
		color = 0xFFFFFF;
	return (color);
}

void	iso_projection(int *x, int *y, int z, int center)
{
	*x = (*x - *y) * cos(0.46373398) + center;
	*y = -(z * 5) + (*x + *y) * sin(0.46373398);
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
			// Rotation on 26.57 grades
			//targetX = start_x * cos(0.46373398) - start_y * sin(0.46373398) + midX * gap;
			//targetY = start_x * sin(0.46373398) + start_y * cos(0.46373398) - midY * gap;

			targetX = (start_x - start_y) * cos(0.46373398) + midX * gap;
			targetY = -(myZ * 5) + (start_x + start_y) * sin(0.46373398);
			//targetX = start_x;
			//targetY = start_y;
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

void	draw_bresen_lines(int max_x, int max_y, t_list *coord_list)
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

t_list	*get_coords(int fd, int *max_x, int *y)
{
	int		x;
	char	**parsed;
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
			coord->z = ft_atoi(parsed[x]);
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

void	read_map(char *filename)
{
	int		fd;
	int		y;
	int		max_x;
	t_list	*coord_list;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	y = 0;
	coord_list = NULL;
	max_x = 0;
	coord_list = get_coords(fd, &max_x, &y);
	ft_lstreverse(&coord_list);
	//create_window(max_x, y, coord_list);
	draw_bresen_lines(max_x, y, coord_list);
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
