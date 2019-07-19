/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:46:03 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 15:46:07 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	del_list(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

void		free_coord_list(t_list *coord_list)
{
	void	(*f)(void *, size_t);

	f = del_list;
	if (coord_list)
		ft_lstdel(&coord_list, f);
	ft_putendl("map error");
}

void		free_coord_list_and_exit(t_list *coord_list)
{
	void	(*f)(void *, size_t);

	f = del_list;
	if (coord_list)
		ft_lstdel(&coord_list, f);
	ft_putendl("map error");
	exit(1);
}

void		free_coord_list_and_exit_parsed(t_list *coord_list, char **parsed,
	t_color *color_info)
{
	void	(*f)(void *, size_t);

	f = del_list;
	if (color_info->mid_height)
		free(color_info->mid_height);
	free(color_info);
	if (coord_list)
		ft_lstdel(&coord_list, f);
	free_parsed(parsed);
	ft_putendl("map error");
	exit(1);
}

void		free_map(t_map *map, int max_y, int max_x)
{
	void	(*f)(void *, size_t);

	f = del_list;
	if (map->coord_list)
		ft_lstdel(&(map->coord_list), f);
	free_coord_array(map->coord_array, max_y, max_x);
	free(map);
}
