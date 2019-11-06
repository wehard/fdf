# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2019/11/05 15:59:51 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

OUT =

all: $(NAME)

$(NAME):
	gcc -o $(NAME) -I /usr/local/include main.c -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

debug:
	gcc -g -o $(NAME) -I /usr/local/include main.c -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(OUT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
