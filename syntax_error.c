/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:10:02 by mamali            #+#    #+#             */
/*   Updated: 2021/11/06 16:48:45 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    log_error(char *s)
{
	ft_putstr(s);
	g_data->exitstatu = 258;
	g_data->syntx = 1;
}

int     is_redirection(int i)
{
	if (i == 4 || i == 5 || i == 6 || i == 3)
		return (1);
	return (0);
}

char	*get_sq_word(t_type *types, int i, int *f)
{
	while (types)
	{
		if (types->type == i)
			return (types->word);
		types = types->next;
		(*f)++;
	}
	return (NULL);
}

int		check_words(t_type *tmp)
{
	t_type  *tmp2;
	t_type  *tmp1;
	int     i;
	int		f;
	char 	*str;

	i = 0;
	tmp2 = tmp;
	tmp1 = tmp;
	if (g_data->line[0] == '|')
		return (0);
	while (g_data->line[i] != '|' && g_data->line[i])
	{
		if (g_data->line[i] == '\'')
		{
			f = 1;
			str = get_sq_word(tmp2, 1, &f);
			while (tmp2 && f != 0)
			{
				f--;
				tmp2 = tmp2->next;
			}
			i += ft_strlen(str) + 1;
			if (g_data->line[i] != '\'')
				return (0);
		}
		else if (g_data->line[i] == '"')
		{
			f = 1;
			str = get_sq_word(tmp1, 2, &f);
			while (tmp1 && f != 0)
			{
				f--;
				tmp1 = tmp1->next;
			}
			i += ft_strlen(str) + 1;
			if (g_data->line[i] != '"')
				return (0);
		}
		i++;
	}
	while (g_data->line[++i] && g_data->line[i] == ' ')
		i++;
	if (g_data->line[i] == '|' || g_data->line[i - 1] == '|')
		return (0);
	tmp2 = tmp;
	while (tmp2)
	{
		if (is_redirection(tmp2->type))
			if (!(tmp2->next))
				return (0);
		tmp2 = tmp2->next;
	}
	return (1);
}

void    syntax_error(t_list *types)
{
	t_type  *tmp;
	char    *str;

	while (types)
	{
		tmp = types->content;
		if (check_words(tmp) == 0)
		{
			log_error("syntax_error\n");
			return ;
		}
		else
			g_data->syntx = 0;
		types = types->next;
	}
	str = g_data->line;
	if (str[0] == '|')
		log_error("syntax_error\n");
}