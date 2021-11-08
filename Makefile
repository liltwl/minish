NAME = minishell

LIBDIR = ft_libft

LIB = ft_libft/*.c

MINIFILES = minishell.c\
			env_tools.c\
			expander.c\
			tools.c\
			convert_list.c\
			parser_tools.c\
			print_functions.c \
			syntax_error.c\
			parser.c\
			outils.c\
			list_type.c\
			cmd.c\
			path.c\
			clear.c

NOBFILES = b2ools.c\
			do_echo.c\
			builtintools.c\
			do_cd.c\
			do_env.c\
			do_exit.c\
			do_export.c\
			do_unset.c\
			export_tools.c\
			pipe.c

NOB =  $(addprefix ./noobnoob/, $(NOBFILES))

FLAGS = -Wall -Wextra -Werror -fsanitize=address -I$(HOME)/goinfre/homebrew/opt/readline/include -L$(HOME)/goinfre/homebrew/opt/readline/lib

all : $(NAME)

$(NAME) :
	@gcc -Wall -Wextra -Werror $(MINIFILES) $(NOB) $(LIB) -o $(NAME) -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib   -lreadline  -g 
fclean:
	@rm -rf minishell

re: fclean all