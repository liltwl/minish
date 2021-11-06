/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b2ools.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:56:06 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/06 16:12:00 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
	char p;

	p = 3;
	if (sig == SIGINT)
	{
		if(g_data->line)
			free(g_data->line);
		//write(1, "\n", 1);
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("yoo$> ", 1);
		//signal(SIGINT, sig_handler);
	}
}

void	ft_error(char *p, int i)
{
	ft_putstr_fd(p, 1);
	exit (i);
}

int	ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
		|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int	ft_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
