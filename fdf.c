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

void	create_window(int max_x, int max_y/*, t_list *coord_list*/)
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
	/*t_coord	*coord;
	int 	myZ;*/

	mlx_ptr = mlx_init();
	if (max_x > max_y)
		gap = 600 / max_x;
	else
		gap = 600 / max_y;
	win_ptr = mlx_new_window(mlx_ptr, 200 + max_x * gap , 200 + max_y * gap, "fdf");
	start_x = 100;
	start_y = 100;
	midX = max_x / 2;
	midY = max_y / 2;
	/*coord = (t_coord *)coord_list->content;
	myZ = (int)coord->z;*/
	while (start_y <= max_y * gap + 100)
	{
		start_x = 100;
		while (start_x <= max_x * gap + 100)
		{
			// Rotation on 26.57 grades
			//targetX = start_x * cos(0.46373398) - start_y * sin(0.46373398) + midX * gap;
			//targetY = start_x * sin(0.46373398) + start_y * cos(0.46373398) - midY * gap;

			targetX = (start_x - start_y) * cos(0.46373398) + midX * gap;
			targetY = -(0) + (start_x + start_y) * sin(0.46373398);

			if ((start_y - 100) % gap == 0)
				mlx_pixel_put(mlx_ptr, win_ptr, targetX, targetY, 0xFFFFFF);
			else if ((start_x - 100) % gap == 0)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, targetX, targetY, 0xFFFFFF);
				/*coord_list = coord_list->next;
				if (coord_list)
				{
					coord = (t_coord *)coord_list->content;
					myZ = (int)coord->z;
					printf("%d\n", myZ);
				}*/
			}
			start_x++;
			// printf("y:%d x:%d\n", start_y, start_x);
		}
		start_y++;
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
	*max_x = x;
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
	while (coord_list)
	{
		printf("x: %d, y: %d, z: %d\n", ((t_coord *)coord_list->content)->x, ((t_coord *)coord_list->content)->y, ((t_coord *)coord_list->content)->z);
		coord_list = coord_list->next;
	}
	//create_window(max_x, y/*, coord_list*/);
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
