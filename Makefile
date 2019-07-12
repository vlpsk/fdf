# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgisele <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/31 16:01:29 by sgisele           #+#    #+#              #
#    Updated: 2019/05/31 16:01:31 by sgisele          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft
MINILIBX_DIR = minilibx_macos
FLAGS = -g -Wall -Wextra -Werror
INCLUDES = -I ./includes
LIBRARIES = -lmlx -lft -L $(LIBFT_DIR) -L $(MINILIBX_DIR) -framework OpenGL \
			-framework AppKit
SRC_DIR = sources
SRC = main.c
NAME = fdf

all: $(NAME)

$(NAME):
	make -C $(LIBFT_DIR)/ re
	make -C $(MINILIBX_DIR)/ re
	gcc $(SRC_DIR)/auxiliary.c $(SRC_DIR)/color.c $(SRC_DIR)/control_actions.c \
		$(SRC_DIR)/control_actions_2.c $(SRC_DIR)/controls.c \
		$(SRC_DIR)/coord_iteration.c $(SRC_DIR)/draw.c $(SRC_DIR)/free_memory.c \
		$(SRC_DIR)/free_memory_2.c $(SRC_DIR)/inits.c \
		$(SRC_DIR)/line_and_projection.c $(SRC_DIR)/main.c \
		$(SRC_DIR)/map_checks.c $(SRC_DIR)/print_menu.c \
		$(SRC_DIR)/reading_map.c $(SRC_DIR)/rotation.c \
		$(FLAGS) $(INCLUDES) $(LIBRARIES) -o $(NAME)

clean:
	/bin/rm -f *.o
	/bin/rm -f *.*~
	make -C $(LIBFT_DIR)/ clean
	make -C $(MINILIBX_DIR)/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT_DIR)/ fclean

re: fclean all

