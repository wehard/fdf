# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2019/11/06 22:38:02 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

SRC = main.c\
	vec3.c

OBJ =

LIBFT=../libft

all: $(NAME)

$(NAME):
	gcc -o $(NAME) -I /usr/local/include -I $(LIBFT)/includes $(SRC) -L$(LIBFT) -lft -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

debug:
	gcc -g -o $(NAME) -I /usr/local/include -I $(LIBFT)/includes $(SRC) -L$(LIBFT) -lft -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

linux: libft
	@echo "Creating LINUX executable $(NAME) ..."
	@gcc -g -o $(NAME) -I $(LIBFT)/includes -I /usr/local/include $(SRC) -L $(LIBFT) -lft -L minilibx -lmlx_Linux -lXext -lX11

libft:
	@make -C $(LIBFT) fclean
	@make -C $(LIBFT)

clean:
	@echo "Removing object files ..."
	@rm -f $(OBJ)

fclean : clean
	@echo "Removing $(NAME) ..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all debug linux clean fclean re
