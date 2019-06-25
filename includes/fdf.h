/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgisele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:04:50 by sgisele           #+#    #+#             */
/*   Updated: 2019/05/29 18:04:52 by sgisele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define OFFSET 200

typedef	struct	s_coord
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_coord;


#endif
