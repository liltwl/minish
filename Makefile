NAME = minishell

LIBDIR = ft_libft

LIB = ft_libft/*.c

MINIFILES = minish.c minishell.c env_tools.c expander.c tools.c convert_list.c parser_tools.c print_functions.c \
echo.c syntax_error.c parser.c outils.c list_type.c cmd.c path.c \
clear.c

FLAGS = -Wall -Wextra -Werror -fsanitize=address

all : $(NAME)

$(NAME) :
	@gcc $(MINIFILES) $(LIB) -o $(NAME) -L/usr/include -fsanitize=address -lreadline  -g
fclean:
	@rm -rf minishell

re: fclean all