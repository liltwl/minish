#include "minishell.h"

int	handle_op_n(char *str, int *i)
{
	int	n;

	n = 1;
	if (!str)
		return (0);
	if (str[0] == '-')
	{
		while (str[n] == 'n')
			n++;
		if (n == (int)strlen(str))
		{
			(*i)++;
			return (1);
		}
	}
	return (0);
}

int get_argc(char **s)
{
    int i;

    i  = 0;
    while (s[i])
        i++;
    return (i);
}

int	builtin_echo(char **args, char **env)
{
	int	i;
	int	f;

	(void)env;
	i = 1;
	f = 0;
	if (get_argc(args) == 1)
		ft_putchar_fd('\n', 1);
	else
	{
		while (handle_op_n(args[i], &i) == 1)
			f = 1;
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			i++;
			if (i > get_argc(args) - 1)
				break ;
			write(1, " ", 1);
		}
		if (f == 0)
			write(1, "\n", 1);
	}
	return (0);
}