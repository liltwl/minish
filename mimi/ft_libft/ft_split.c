/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:42:17 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/28 14:33:53 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	t_help	help;

	help.i = 0;
	help.j = 0;
	help.k = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == c)
		{
			help.i = 1;
			help.k = 0;
		}
		else if (help.k == 0)
		{
			help.k = 1;
			help.j++;
		}
		str++;
	}
	if (help.i == 0 && help.j == 1)
		return (-1);
	else
		return (help.j);
}

static int	words_lenght(const char *str, int i, char c)
{
	int	lenght;

	lenght = 0;
	while (str[i] != c && str[i] != '\0')
	{
		lenght++;
		i++;
	}
	return (lenght);
}

static char	**help(const char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * 2);
	tab[0] = (char *)malloc(1 * ft_strlen(str) + 1);
	while (str[i])
	{
		tab[0][i] = str[i];
		i++;
	}
	tab[0][i] = '\0';
	tab[1] = NULL;
	return (tab);
}

char	**ft_split(const char *str, char c)
{
	char	**tab;
	t_help	loop;

	loop.i = 0;
	loop.j = 0;
	if (count_words(str, c) == -1 || !str)
	{
		if (count_words(str, c) == -1)
			return (help(str));
		else
			return (NULL);
	}
	tab = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	while (str[loop.i] != '\0' && loop.j < count_words(str, c))
	{
		loop.k = 0;
		while (str[loop.i] == c)
			loop.i++;
		tab[loop.j] = (char *)malloc(1 * words_lenght(str, loop.i, c) + 1);
		while (str[loop.i] != c && str[loop.i] != '\0')
			tab[loop.j][loop.k++] = str[loop.i++];
		tab[loop.j++][loop.k] = '\0';
	}
	tab[loop.j] = NULL;
	return (tab);
}
