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

FLAGS = -Wall -Wextra -Werror -I ./includes -L ./libs -lft  -lmlx -framework OpenGL -framework AppKit

SRC = fdf.c

NAME = fdf

all: $(NAME)

$(NAME):
	gcc $(SRC) $(FLAGS) -o $(NAME)

clean:
	/bin/rm -f *.o
	/bin/rm -f *.*~

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
