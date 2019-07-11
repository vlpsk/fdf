/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:54:05 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:54:08 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	redraw(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->image);
	fdf->image = mlx_new_image(fdf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->addresses = mlx_get_data_addr(fdf->image, &(fdf->bits_per_pixel),
		&(fdf->size_line), &(fdf->endian));
	draw(fdf);
	print_menu(fdf);
}

int		zoom(int keycode, t_fdf *fdf)
{
	if (keycode == 4)
		(fdf->zoom)++;
	else if ((keycode == 5) && (fdf->zoom) > 1)
		(fdf->zoom)--;
	redraw(fdf);
	return (0);
}

int		enlarge(int keycode, t_fdf *fdf)
{
	if (keycode == MAIN_KEY_PLUS || keycode == KEY_PLUS)
		(fdf->multiplier)++;
	else if ((keycode == MAIN_KEY_MINUS || keycode == KEY_MINUS) &&
		(fdf->multiplier) > 1)
		(fdf->multiplier)--;
	redraw(fdf);
	return (0);
}

int		move(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_RIGHT)
		(fdf->camera).move_x = (fdf->camera).move_x - 10;
	else if (keycode == KEY_LEFT)
		(fdf->camera).move_x = (fdf->camera).move_x + 10;
	else if (keycode == KEY_DOWN)
		(fdf->camera).move_y = (fdf->camera).move_y - 10;
	else if (keycode == KEY_UP)
		(fdf->camera).move_y = (fdf->camera).move_y + 10;
	redraw(fdf);
	return (0);
}

int		rotate(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_D)
		(fdf->camera).y_angle = (fdf->camera).y_angle + 0.02;
	else if (keycode == KEY_A)
		(fdf->camera).y_angle = (fdf->camera).y_angle - 0.02;
	else if (keycode == KEY_W)
		(fdf->camera).x_angle = (fdf->camera).x_angle + 0.02;
	else if (keycode == KEY_S)
		(fdf->camera).x_angle = (fdf->camera).x_angle - 0.02;
	else if (keycode == KEY_E)
		(fdf->camera).z_angle = (fdf->camera).z_angle + 0.02;
	else if (keycode == KEY_Q)
		(fdf->camera).z_angle = (fdf->camera).z_angle - 0.02;
	redraw(fdf);
	return (0);
}
