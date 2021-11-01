/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 03:37:17 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/28 14:49:15 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	test(char a, const char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (a == s[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static	int	fstart(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (test(s1[i], s2) != 1)
			return (i);
		i++;
	}
	return (0);
}

static	int	fend(const char *s1, const char *s2)
{
	int	l;

	l = 0;
	while (s1[l] != '\0')
	{
		l++;
	}
	l -= 1;
	while (l > 0)
	{
		if (test(s1[l], s2) != 1)
			return (l);
		l--;
	}
	return (0);
}

static	char	*substring(char const *s, unsigned int start, size_t len)
{
	int		k;
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = len + start;
	k = start;
	tab = (char *)malloc((len + 1) * sizeof(char));
	while (s[start] != '\0' && k < j)
	{
		tab[i] = s[start];
		i++;
		start++;
		k++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tab;
	t_help	help;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	help.i = fstart(s1, set);
	help.k = help.i;
	help.j = (fend(s1, set) - help.k);
	if (help.j == 0 && help.i == 0)
	{
		tab = (char *)malloc(2 * sizeof(char));
		tab[0] = s1[0];
		tab[1] = '\0';
		return (tab);
	}
	if (help.j == 0)
	{
		tab = (char *)malloc(1 * sizeof(char));
		tab[0] = '\0';
		return (tab);
	}
	help.j += 1;
	return (substring(s1, help.i, help.j));
}
