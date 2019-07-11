/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:46:56 by sgisele           #+#    #+#             */
/*   Updated: 2019/07/11 16:46:58 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *y, int *z, double angle)
{
	int		previous;

	previous = *y;
	*y = previous * cos(angle) + *z * sin(angle);
	*z = (-1) * previous * sin(angle) + *z * cos(angle);
}

void	rotate_y(int *x, int *z, double angle)
{
	int		previous;

	previous = *x;
	*x = previous * cos(angle) + *z * sin(angle);
	*z = -1 * previous * sin(angle) + *z * cos(angle);
}

void	rotate_z(int *x, int *y, double angle)
{
	int		previous;

	previous = *x;
	*x = previous * cos(angle) - *y * sin(angle);
	*y = previous * sin(angle) + *y * cos(angle);
}
