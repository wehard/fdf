# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2019/12/04 18:09:02 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

SRC = main.c\
	point.c\
	matrix.c\
	draw.c\
	map.c\
	frame_buffer.c\
	event_handlers.c\
	error.c\
	ft_print_matrix.c\
	color.c

OBJ =

LIBFT=../libft

MLXLIB=mlx
MLXDIR=./minilibx


all: $(NAME)

$(NAME):
	#@make -C $(LIBFT)
	gcc -o $(NAME) -I $(LIBFT)/includes -I $(MLXDIR) $(SRC) -L$(LIBFT) -lft -L$(MLXDIR) -l$(MLXLIB) -framework OpenGL -framework AppKit

debug:
	gcc -g -o $(NAME) -I $(LIBFT)/includes -I $(MLXDIR) $(SRC) -L$(LIBFT) -lft -L$(MLXDIR) -l$(MLXLIB) -framework OpenGL -framework AppKit

linux: libft
	@echo "Creating LINUX executable $(NAME) ..."
	@gcc -g -o $(NAME) -I $(LIBFT)/includes -I minilibx $(SRC) -L $(LIBFT) -lft -L minilibx -lmlx_Linux -lXext -lX11 -lm

libft:
	@make -C $(LIBFT) fclean
	@make -C $(LIBFT)

clean:
	#@make clean -C $(LIBFT)
	@echo "Removing object files ..."
	@rm -f $(OBJ)

fclean : clean
	#@make fclean -C $(LIBFT)
	@echo "Removing $(NAME) ..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all debug linux clean fclean re
