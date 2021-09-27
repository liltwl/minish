# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/14 18:34:35 by otaouil           #+#    #+#              #
#    Updated: 2019/11/28 15:16:35 by otaouil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memchr.c ft_strjoin.c ft_atoi.c ft_memcmp.c ft_strlcat.c \
ft_bzero.c ft_memcpy.c ft_strlcpy.c ft_calloc.c ft_memmove.c \
ft_strlen.c ft_cmp.c ft_memset.c	ft_strmapi.c ft_isalnum.c \
ft_power.c ft_strncmp.c ft_isalpha.c ft_putchar.c ft_strnstr.c \
ft_isascii.c ft_putchar_fd.c ft_strrchr.c ft_isdigit.c	ft_putendl_fd.c	\
ft_strtrim.c ft_isprint.c ft_putnbr_fd.c ft_substr.c ft_itoa.c	ft_putstr_fd.c	\
ft_tolower.c ft_split.c	ft_toupper.c  \
ft_strchr.c ft_strcpy.c ft_memccpy.c	ft_strdup.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	gcc  -Wall -Wextra -Werror -c  $(SRCS)
	cp $(OBJECTS) ../
clean:
	rm -f *.o
	
fclean: clean
	@rm -f $(NAME)
me:
	@echo "#    #  ####   ####  #####  #    #  ####   ####  #####  "
	@echo "##   # #    # #    # #    # ##   # #    # #    # #    # "
	@echo "# #  # #    # #    # #####  # #  # #    # #    # #####  "
	@echo "#  # # #    # #    # #    # #  # # #    # #    # #    # "
	@echo "#   ## #    # #    # #    # #   ## #    # #    # #    # "
	@echo "#    #  ####   ####  #####  #    #  ####   ####  #####  "

re: fclean all
