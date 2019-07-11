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
# define FDF_H

# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "math.h"

# define WINDOW_WIDTH 1366
# define WINDOW_HEIGHT 768
# define OFFSET 200

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_H 4
# define KEY_G 5
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_T 17
# define MAIN_KEY_PLUS 24
# define MAIN_KEY_MINUS 27
# define KEY_I 34
# define KEY_P 35
# define KEY_N 45
# define KEY_ESCAPE 53
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

typedef	enum
{
	PARALLEL,
	ISO
}	t_project;

typedef	struct	s_coord
{
	int		x;
	int		y;
	int		z;
	int		old_z;
	int		color;
}				t_coord;

typedef struct	s_map
{
	int		max_x;
	int		max_y;
	t_coord ***coord_array;
	t_list	*coord_list;
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

typedef struct	s_mouse
{
	int		is_pressed;
	int		x;
	int		y;
	int		previous_x;
	int		previous_y;
}				t_mouse;

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
	int			gap;
	int			multiplier;
	int			color_info;
	int			base_color;
	t_map		*map;
	t_camera	camera;
	t_offset	offset;
	t_project	projection;
	t_mouse		mouse;
}				t_fdf;

void			read_map(char *filename);
t_list			*get_coords(int fd, int *max_x, int *y, int *color_info);
void			free_coord_list(t_list *coord_list);
void			free_coord_list_and_exit(t_list *coord_list);
void			free_coord_list_and_exit_parsed(t_list *coord_list,
	char **parsed);
void			free_parsed(char **parsed);
void			free_coord_array(t_coord ***coord_array, int max_y, int max_x);
void			free_map(t_map *map, int max_y, int max_x);
void			free_convert_to_array(t_coord ***coord_array,
	t_list **coord_list, int i, int j);
t_list			*coord_iteration(char **parsed, t_coord *maxes,
	t_list *coord_list, int *color_info);
int				is_decimal(char *str);
int				ft_ishex(char c);
int				is_hexadecimal_color(char *str);
int				check_number_of_elements(char **parsed, int x);
t_coord			***convert_to_array(t_list **coord_list, int max_x, int max_y);
void			ft_lstreverse(t_list **begin_list);
int				ft_len(char **array);
int				ft_hextoi(char *hex);
t_offset		init_offset();
t_map			*init_map(int max_x, int max_y, t_coord ***coord_array,
	t_list *coord_list);
t_mouse			init_mouse();
t_camera		init_camera();
t_fdf			*init_fdf(t_map *map, int color_info);
void			draw_with_image(int max_x, int max_y, t_map *map,
	int color_info);
void			print_menu(t_fdf *fdf);
void			draw(t_fdf	*fdf);
t_offset		calculate_offset(t_coord *first, t_coord *last, int val,
	t_fdf *fdf);
t_coord			proj(t_coord *old_coord, int gap, int midx, t_fdf *fdf);
void			line_bresen(t_coord start_coord, t_coord end_coord, t_fdf *fdf);
void			iso_projection(int *x, int *y, int z, int center);
int				get_color(int z, t_fdf *fdf);
int				get_gradient(t_coord start_coord, t_coord end_coord, int x,
	int y);
void			rotate_x(int *y, int *z, double angle);
void			rotate_y(int *x, int *z, double angle);
void			rotate_z(int *x, int *y, double angle);
int				key_press(int keycode, void *param);
int				mouse_press(int keycode, int x, int y, void *param);
int				mouse_moved(int x, int y, void *param);
int				mouse_released(int button, int x, int y, void *param);
void			redraw(t_fdf *fdf);
int				zoom(int keycode, t_fdf *fdf);
int				enlarge(int keycode, t_fdf *fdf);
int				move(int keycode, t_fdf *fdf);
int				rotate(int keycode, t_fdf *fdf);
int				set_projection(int keycode, t_fdf *fdf);
int				change_base_color(int keycode, t_fdf *fdf);
void			close_program(t_fdf *fdf);

#endif
