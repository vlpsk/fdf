cmake_minimum_required(VERSION 3.13)
project(fdf C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(minilibx_macos)
include_directories(minilibx_macos/includes)

add_executable(fdf
        includes/fdf.h
        includes/libft.h
        includes/mlx.h
        learning/main.c
        minilibx_macos/includes/mlx.h
        minilibx_macos/font.c
        minilibx_macos/mlx_init_loop.m
        minilibx_macos/mlx_int.h
        minilibx_macos/mlx_int_str_to_wordtab.c
        minilibx_macos/mlx_new_image.m
        minilibx_macos/mlx_new_window.h
        minilibx_macos/mlx_new_window.m
        minilibx_macos/mlx_rgb.c
        minilibx_macos/mlx_shaders.c
        minilibx_macos/mlx_xpm.c
        fdf.c)
