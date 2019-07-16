/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 20:34:29 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 20:34:31 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	free_coord_array(t_coord ***coord_array, int max_y, int max_x)
{
	int i;

	i = 0;
	(void)max_x;
	while (i <= max_y)
	{
		free(coord_array[i]);
		i++;
	}
	free(coord_array);
}

void	free_convert_to_array(t_coord ***coord_array, t_list **coord_list,
	int i, int j)
{
	free_coord_array(coord_array, i, j);
	free_coord_list_and_exit(*coord_list);
}

void	mem_alloc_failed(void)
{
	ft_putendl("error: memory allocation failed");
	exit(1);
}

void	not_file(void)
{
	ft_putendl("error: programm requires file, not directory");
	exit(1);
}
