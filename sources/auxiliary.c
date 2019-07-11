/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:59:58 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:00:01 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	t_coord	**populate_coords(t_list **coord_list, t_coord **coords,
	int max_x, int *j)
{
	*j = -1;
	while (++(*j) <= max_x)
		if (coord_list)
		{
			coords[*j] = (t_coord *)((*coord_list)->content);
			*coord_list = (*coord_list)->next;
		}
	return (coords);
}

t_coord			***convert_to_array(t_list **coord_list, int max_x, int max_y)
{
	t_coord	***coord_array;
	t_coord	**coords;
	int		i;
	int		j;
	t_list	*begin_list;

	i = -1;
	begin_list = *coord_list;
	if (!(coord_array = (t_coord ***)malloc(sizeof(t_coord **) * (max_y + 1))))
		return (NULL);
	j = 0;
	while (++i <= max_y)
	{
		if (!(coords = (t_coord **)malloc(sizeof(t_coord *) * (max_x + 1))))
			free_convert_to_array(coord_array, coord_list, i, j);
		coord_array[i] = populate_coords(coord_list, coords, max_x, &j);
	}
	*coord_list = begin_list;
	return (coord_array);
}

void			ft_lstreverse(t_list **begin_list)
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

int				ft_len(char **array)
{
	int count;

	count = 0;
	while (array[count] != 0)
		count++;
	return (count);
}

int				ft_hextoi(char *hex)
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
