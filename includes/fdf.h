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

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define MAIN_KEY_PLUS 24
# define MAIN_KEY_MINUS 27
# define KEY_ESCAPE 53
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

typedef	struct	s_coord
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_coord;

typedef struct	s_map
{
	int		max_x;
	int		max_y;
	t_coord ***coord_array;
}				t_map;

typedef	struct	s_offset
{
	int		offset_x;
	int		offset_y;
}				t_offset;

typedef struct	s_camera
{
	int		move_x;
	int		move_y;
	double	x_angle;
	double	y_angle;
	double	z_angle;
}				t_camera;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*window;
	void		*image;
	char		*addresses;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			zoom;
	int			multiplier;
	t_map		*map;
	t_camera	camera;
	t_offset	offset;
}				t_fdf;


#endif
