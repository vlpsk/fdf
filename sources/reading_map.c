/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:39:33 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 15:39:41 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	populate_list(t_list **coord_list, char **parsed,
	t_coord *maxes, t_color *color_info)
{
	if (*coord_list)
	{
		if (check_number_of_elements(parsed, maxes->x))
		{
			maxes->x = 0;
			if (!(*coord_list = coord_iteration(parsed, maxes, *coord_list,
				color_info)))
				free_coord_list_and_exit_parsed(*coord_list, parsed,
					color_info);
		}
		else
			free_coord_list_and_exit_parsed(*coord_list, parsed, color_info);
	}
	else
	{
		maxes->x = 0;
		if (!(*coord_list = coord_iteration(parsed, maxes, *coord_list,
			color_info)))
			free_coord_list_and_exit_parsed(*coord_list, parsed, color_info);
	}
}

t_list			*get_coords(int fd, int *max_x, int *y, t_color *color_info)
{
	t_coord	maxes;
	char	**parsed;
	t_list	*coord_list;
	char	*line;

	coord_list = NULL;
	maxes.x = 0;
	maxes.y = 0;
	while (get_next_line(fd, &line))
	{
		parsed = ft_strsplit(line, ' ');
		populate_list(&coord_list, parsed, &maxes, color_info);
		maxes.y = maxes.y + 1;
		free_parsed(parsed);
		free(line);
	}
	*max_x = maxes.x - 1;
	*y = maxes.y - 1;
	return (coord_list);
}

static	t_map	*create_map(int *max_x, int *max_y, t_color *color_info, int fd)
{
	t_list	*coord_list;
	t_coord	***coord_array;
	t_map	*map;

	coord_list = get_coords(fd, max_x, max_y, color_info);
	ft_lstreverse(&coord_list);
	coord_array = convert_to_array(&coord_list, *max_x, *max_y);
	if (!(map = init_map(*max_x, *max_y, coord_array, coord_list)))
	{
		free(color_info);
		free_coord_list(coord_list);
		free_coord_array(coord_array, *max_y, *max_x);
		return (NULL);
	}
	return (map);
}

static	int		check_if_dir(int fd)
{
	char	buff[1];
	int		res;

	res = read(fd, buff, 0);
	return (res);
}

void			read_map(char *filename)
{
	int		fd;
	int		max_y;
	int		max_x;
	t_color	*color_info;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("error: invalid file name");
		return ;
	}
	if (check_if_dir(fd) < 0)
		not_file();
	max_y = 0;
	max_x = 0;
	if (!(color_info = (t_color *)malloc(sizeof(t_color))))
		mem_alloc_failed();
	color_info->color_info = 0;
	color_info->mid_height = NULL;
	color_info->size = 0;
	if (!(map = create_map(&max_x, &max_y, color_info, fd)))
		mem_alloc_failed();
	draw_with_image(max_x, max_y, map, color_info);
}
