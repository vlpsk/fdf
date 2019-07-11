/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:50:13 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:50:15 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == KEY_ESCAPE)
		close_program(fdf);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		zoom(keycode, fdf);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT ||
		keycode == KEY_DOWN || keycode == KEY_UP)
		move(keycode, fdf);
	else if (keycode == MAIN_KEY_PLUS || keycode == MAIN_KEY_MINUS)
		enlarge(keycode, fdf);
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D ||
		keycode == KEY_W || keycode == KEY_Q || keycode == KEY_E)
		rotate(keycode, fdf);
	else if (keycode == KEY_P || keycode == KEY_I)
		set_projection(keycode, fdf);
	else if (keycode == KEY_R || keycode == KEY_G || keycode == KEY_B ||
		keycode == KEY_T || keycode == KEY_H || keycode == KEY_N)
		change_base_color(keycode, fdf);
	return (0);
}

int		mouse_press(int keycode, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (keycode == 4 || keycode == 5)
	{
		zoom(keycode, fdf);
		fdf->mouse.x = x;
		fdf->mouse.y = y;
	}
	else if (keycode == 1 || keycode == 2)
		fdf->mouse.is_pressed = 1;
	return (0);
}

int		mouse_moved(int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	fdf->mouse.previous_x = fdf->mouse.x;
	fdf->mouse.previous_y = fdf->mouse.y;
	fdf->mouse.x = x;
	fdf->mouse.y = y;
	if (fdf->mouse.is_pressed)
	{
		fdf->camera.x_angle += (x - fdf->mouse.previous_x) * 0.02;
		fdf->camera.y_angle += (y - fdf->mouse.previous_y) * 0.02;
		redraw(fdf);
	}
	return (0);
}

int		mouse_released(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)button;
	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	fdf->mouse.is_pressed = 0;
	return (0);
}
