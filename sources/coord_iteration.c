/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_iteration.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 20:05:19 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 20:05:21 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	with_color(char **split_value, t_coord *coord, int *color_info)
{
	if (is_decimal(split_value[0]))
	{
		coord->z = ft_atoi(split_value[0]);
		coord->old_z = coord->z;
		return (1);
	}
	else
		return (0);
	if (is_hexadecimal_color(split_value[1]))
	{
		coord->color = ft_hextoi(split_value[1]);
		*color_info = 1;
		return (1);
	}
	else
		return (0);
}

static	int	without_color(char **split_value, t_coord *coord)
{
	if (is_decimal(split_value[0]))
	{
		coord->z = ft_atoi(split_value[0]);
		coord->old_z = coord->z;
		coord->color = 0xF44242;
		return (1);
	}
	else
		return (0);
}

static	int	parse_coord(char **split_value, t_coord *coord, int *color_info)
{
	if (ft_len(split_value) == 2)
	{
		if (with_color(split_value, coord, color_info) == 0)
			return (0);
		else
			return (1);
	}
	else if (ft_len(split_value) == 1)
	{
		if (without_color(split_value, coord) == 0)
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

t_list		*coord_iteration(char **parsed, t_coord *maxes, t_list *coord_list,
	int *color_info)
{
	t_coord	*coord;
	char	**split_value;

	while (parsed[maxes->x] != 0)
	{
		if (!(coord = (t_coord *)malloc(sizeof(t_coord))))
			return (NULL);
		coord->x = maxes->x;
		coord->y = maxes->y;
		split_value = ft_strsplit(parsed[maxes->x], ',');
		if (parse_coord(split_value, coord, color_info) == 0)
			return (NULL);
		if (coord_list == NULL)
			coord_list = ft_lstnew(coord, sizeof(t_coord));
		else
			ft_lstadd(&coord_list, ft_lstnew(coord, sizeof(t_coord)));
		free(coord);
		free_parsed(split_value);
		maxes->x = maxes->x + 1;
	}
	return (coord_list);
}
