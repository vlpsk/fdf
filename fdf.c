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

t_list	*get_coords(char *line, int y, t_list *coord_list)
{
	int		x;
	int		z;
	char	**parsed;
	t_coord	*coord;

	parsed = ft_strsplit(line, ' ');
	x = 0;
	coord = (t_coord *)malloc(sizeof(t_coord));
	while (parsed[x] != 0)
	{
		z = ft_atoi(parsed[x]);
		coord->x = x;
		coord->y = y;
		coord->z = z;
		if (coord_list == NULL)
			coord_list = ft_lstnew(coord, sizeof(coord));
		else
			ft_lstadd(&coord_list, ft_lstnew(coord, sizeof(coord)));
		x++;
	}
	return (coord_list);
}

void	read_map(char *filename)
{
	int		fd;
	char	*line;
	int		y;
	t_list	*coord_list;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	y = 0;
	coord_list = NULL;
	while (get_next_line(fd, &line))
		coord_list = get_coords(line, y++, coord_list);
	ft_lstreverse(&coord_list);
	while (coord_list)
	{
		printf("x: %d | y: %d | z: %d\n", ((t_coord *)(coord_list->content))->x, ((t_coord *)(coord_list->content))->y, ((t_coord *)(coord_list->content))->z);
		coord_list = coord_list->next;
	}
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
