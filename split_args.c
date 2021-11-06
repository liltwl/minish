/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:30:18 by mamali            #+#    #+#             */
/*   Updated: 2021/11/06 20:22:47 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_equale(char *s1, char *s2)
{
	int	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] && s2[i])
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		if (s1[i] == s2[i])
			return (1);
		else
			return (0);
	}
	return (-1);
}

void	init_struct(t_counter *counters)
{
	counters->i = 0;
	counters->j = 0;
	counters->k = 0;
}

int	check_conditions(char	*args)
{
	if (!(ft_str_equale(args, "<")) && !(ft_str_equale(args, ">"))
		&& !(ft_str_equale(args, ">>")) && args)
	{
		return (1);
	}
	else
		return (0);
}

int	check(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	words_lenght(char *str, int i, char *set)
{
	int		lenght;
	char	a;

	lenght = 0;
	while (!(check(set, str[i])) && str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			a = str[i++];
			lenght++;
			while (str[i] && str[i] != a)
			{
				i++;
				lenght++;
			}
		}
		lenght++;
		i++;
	}
	return (lenght);
}

int	norm_return(t_counter help)
{
	if (help.k == 0 && help.i == 1)
		return (-1);
	else
		return (help.i);
}

static int	words(char *str, char *set, t_counter help)
{
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == 34 || *str == 39)
		{
			help.a = *str++;
			while (*str && *str != help.a)
				str++;
		}
		if (check(set, *str))
		{
			help.k = 1;
			help.j = 0;
		}
		else if (help.j == 0)
		{
			help.j = 1;
			help.i++;
		}
		str++;
	}
	return (norm_return(help));
}

static	char	**help(char *str)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 1;
	tab = (char **)malloc(sizeof(char *) * 2);
	tab[0] = ft_strdup(str);
	tab[1] = NULL;
	return (tab);
}

char	**norm(t_counter loop, char *str, char *set, char **tab)
{
	char		a;
	t_counter	data;

	init_struct(&data);
	while (str[loop.i] != '\0' && loop.j < words(str, set, data))
	{
		loop.k = 0;
		while (check(set, str[loop.i]))
			loop.i++;
		tab[loop.j] = (char *)malloc(1 * words_lenght(str, loop.i, set) + 1);
		while (!(check(set, str[loop.i])) && str[loop.i] != '\0')
		{
			if (str[loop.i] == 34 || str[loop.i] == 39)
			{
				a = str[loop.i];
				tab[loop.j][loop.k++] = str[loop.i++];
				while (str[loop.i] && str[loop.i] != a)
					tab[loop.j][loop.k++] = str[loop.i++];
			}
			tab[loop.j][loop.k++] = str[loop.i++];
		}
		tab[loop.j++][loop.k] = '\0';
	}
	tab[loop.j] = NULL;
	return (tab);
}

char	**split_args(char *str, char *set)
{
	char		**tab;
	t_counter	loop;
	t_counter	data;

	loop.i = 0;
	loop.j = 0;
	loop.k = 0;
	init_struct(&data);
	if (words(str, set, data) == -1 || !str)
	{
		init_struct(&data);
		if (words(str, set, data) == -1)
			return (help(str));
		else
			return (NULL);
	}
	init_struct(&data);
	tab = (char **)malloc(sizeof(char *) * (words(str, set, data) + 1));
	return (norm(loop, str, set, tab));
}

