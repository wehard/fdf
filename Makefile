# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2019/12/12 14:40:24 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

SRCS = fdf.c\
	matrix.c\
	matrix_operations.c\
	matrix_rotation.c\
	matrix_scale.c\
	matrix_translation.c\
	matrix_projection.c\
	draw_line.c\
	map.c\
	map_helper.c\
	draw_map.c\
	frame_buffer.c\
	error.c\
	color.c\
	vertex.c\
	vec2.c\
	vec3.c\
	control.c\
	project.c\
	fdf_data.c\
	info.c

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
	@gcc -g -o $(NAME) -I$(INCL) -I $(LIBFT)/includes -I minilibx $(SRC) -L $(LIBFT) -lft -L minilibx -lmlx_Linux -lXext -lX11 -lm

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
