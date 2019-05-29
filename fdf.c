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

void	get_coords(char *line, int y)
{
	int		x;
	int		z;
	char	**parsed;

	parsed = ft_strsplit(line, ' ');
	x = 0;
	while (parsed[x])
	{
		z = ft_atoi(parsed[x]);
		printf("x: %d | y: %d | z: %d\n", x, y, z);
	}
}

void	read_map(char *filename)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	y = 0;
	while (get_next_line(fd, &line))
		get_coords(line, y++);
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
