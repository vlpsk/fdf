/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:40:36 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 17:40:39 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	print_menu_2(t_fdf *fdf, int y)
{
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30,
		0xFFFFFF, "Rotate:");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20,
		0xFFFFFF, "Mouse Press and Drag");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 275, y += 20,
		0xFFFFFF, "or:");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20,
		0xFFFFFF, "X-Axis: W/S");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20,
		0xFFFFFF, "Y-Axis: Q/E");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20,
		0xFFFFFF, "Z-Axis: A/D");
}

static	void	print_color_menu(t_fdf *fdf)
{
	int y;

	y = WINDOW_HEIGHT - 200;
	mlx_string_put(fdf->mlx_ptr, fdf->window, 25, y,
		0xFFFFFF, "Change color");
	mlx_string_put(fdf->mlx_ptr, fdf->window, 25, y += 30,
		0xFFFFFF, "decrement/increment");
	mlx_string_put(fdf->mlx_ptr, fdf->window, 50, y += 20,
		0xFFFFFF, "Red: R/T");
	mlx_string_put(fdf->mlx_ptr, fdf->window, 50, y += 20,
		0xFFFFFF, "Green: G/H");
	mlx_string_put(fdf->mlx_ptr, fdf->window, 50, y += 20,
		0xFFFFFF, "Blue: B/N");
}

void			print_menu(t_fdf *fdf)
{
	int y;

	y = 0;
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 200, y += 20,
		0xFFFFFF, "How to Use");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30,
		0xFFFFFF, "Projection:");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20,
		0xFFFFFF, "Parallel: P");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 250, y += 20,
		0xFFFFFF, "ISO: I");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 35,
		0xFFFFFF, "Zoom: scroll");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30,
		0xFFFFFF, "Flatten: +/-");
	mlx_string_put(fdf->mlx_ptr, fdf->window, WINDOW_WIDTH - 300, y += 30,
		0xFFFFFF, "Move: arrows");
	print_menu_2(fdf, y);
	print_color_menu(fdf);
}
