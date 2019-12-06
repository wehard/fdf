# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2019/12/06 14:37:06 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

SRCS = fdf.c\
	matrix.c\
	draw.c\
	map.c\
	frame_buffer.c\
	depth_buffer.c\
	event_handlers.c\
	error.c\
	ft_print_matrix.c\
	color.c\
	vertex.c\
	vec2.c\
	vec3.c

SRCDIR = src

SRC = $(addprefix $(SRCDIR)/, $(SRCS))

OUT = $(SRCS:.c=.o)

INCL = include

LIBFT=../libft

MLXLIB=mlx
MLXDIR=./minilibx


all: $(NAME)

$(NAME):
	#@make -C $(LIBFT)
	gcc -o $(NAME) -I$(INCL) -I $(LIBFT)/includes -I $(MLXDIR) $(SRC) -L$(LIBFT) -lft -L$(MLXDIR) -l$(MLXLIB) -framework OpenGL -framework AppKit

debug:
	gcc -g -o $(NAME) -I$(INCL) -I $(LIBFT)/includes -I $(MLXDIR) $(SRC) -L$(LIBFT) -lft -L$(MLXDIR) -l$(MLXLIB) -framework OpenGL -framework AppKit

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
