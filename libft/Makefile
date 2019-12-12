# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 15:22:37 by wkorande          #+#    #+#              #
#    Updated: 2019/12/11 14:16:48 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

BLACK=\033[30m
RED=\033[0;31m
BOLDRED=\033[1;31m
GREEN=\033[0;32m
BOLDGREEN=\033[1;32m
YELLOW=\033[0;33m
BOLDYELLOW=\033[1;33m
BLUE=\033[0;34m
BOLDBLUE=\033[1;34m
PINK=\033[0;35m
BOLDPINK=\033[1;35m
CYAN=\033[0;36m
BOLDCYAN=\033[1;36m
WHITE=\033[37m
NORMAL=\033[0m

SRC =	ft_atoi.c\
		ft_bzero.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_itoa_base.c\
		ft_memalloc.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memdel.c\
		ft_memmove.c\
		ft_memset.c\
		ft_ndigits.c\
		ft_ndigits_base.c\
		ft_nwords.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putendl.c\
		ft_putendl_fd.c\
		ft_putnbr.c\
		ft_putnbr_fd.c\
		ft_putstr.c\
		ft_putstr_fd.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strclr.c\
		ft_strcmp.c\
		ft_strcpy.c\
		ft_strdel.c\
		ft_strdup.c\
		ft_strequ.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlen.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strncat.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_strnequ.c\
		ft_strnew.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strrev.c\
		ft_strsplit.c\
		ft_strstr.c\
		ft_strsub.c\
		ft_strtrim.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_lstnew.c\
		ft_lstdelone.c\
		ft_lstdel.c\
		ft_lstadd.c\
		ft_lstappend.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_pow.c\
		ft_min.c\
		ft_max.c\
		ft_get_next_line.c\
		ft_dtoa.c\
		ft_ndigits_base_ll.c\
		ft_itoa_ll.c\
		ft_ndigits_base_ull.c\
		ft_itoa_base_ull.c\
		ft_itoa_ull.c\
		ft_abs.c

SRCDIR = srcs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OUT = $(SRC:.c=.o)

INCL = includes

all: $(NAME)

$(NAME):
	@printf "$(BOLDYELLOW)%s$(NORMAL)\n" "Making $(NAME)"
	@gcc -Wall -Wextra -Werror -I $(INCL) -c $(SRCS)
	@ar rc $(NAME) $(OUT)
	@ranlib $(NAME)
	@printf "$(YELLOW)%s$(NORMAL)\n" "done"

clean:
	@printf "$(BOLDBLUE)%s$(NORMAL)\n" "Removing $(OUT)"
	@rm -f $(OUT)
	@printf "$(BLUE)%s$(NORMAL)\n" "done"

fclean: clean
	@printf "$(BOLDBLUE)%s$(NORMAL)\n" "Removing $(NAME)"
	@rm -f $(NAME)
	@printf "$(BLUE)%s$(NORMAL)\n" "done"

re: fclean all

.PHONY: all clean fclean re
