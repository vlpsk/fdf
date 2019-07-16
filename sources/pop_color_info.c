/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_color_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:34:41 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/16 17:34:44 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	repopulte(t_color *color_info, t_coord *coord, int *tmp, int i)
{
	if (!(tmp = (int *)malloc(sizeof(int) * color_info->size)))
	{
		free(color_info->mid_height);
		return (0);
	}
	i = -1;
	while (++i < color_info->size)
		tmp[i] = color_info->mid_height[i];
	free(color_info->mid_height);
	if (!(color_info->mid_height = (int *)malloc(sizeof(int) * (i + 1))))
	{
		free(tmp);
		return (0);
	}
	i = -1;
	while (++i < color_info->size)
		color_info->mid_height[i] = tmp[i];
	free(tmp);
	color_info->mid_height[i] = coord->z;
	color_info->size++;
	return (1);
}

int			pop_color_info(t_color *color_info, t_coord *coord, int *tmp, int i)
{
	if (color_info->mid_height == NULL)
	{
		color_info->size = 1;
		if (!(color_info->mid_height = (int *)malloc(sizeof(int)
			* color_info->size)))
			return (0);
		color_info->mid_height[0] = coord->z;
	}
	else
	{
		if (repopulte(color_info, coord, tmp, i) == 0)
			return (0);
	}
	return (1);
}
