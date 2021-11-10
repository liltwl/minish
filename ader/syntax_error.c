/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:10:02 by mamali            #+#    #+#             */
/*   Updated: 2021/11/10 01:41:09 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	log_error(char *s)
{
	ft_putstr(s);
	g_data->exitstatu = 258;
	g_data->syntx = 1;
}

int	is_redirection2(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_redirection(int i)
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

void	syntax_error(t_list *types)
{
	t_type	*tmp;
	char	*str;
	int		i;

	i = 0;
	while (types)
	{
		tmp = types->content;
		if (check_words(tmp, &i) == 0)
		{
			log_error("syntax_error\n");
			return ;
		}
		else
			g_data->syntx = 0;
		types = types->next;
	}
	str = g_data->line;
	i = ft_strlen(str) - 1;
	if (str[0] == '|' || str[i] == '|')
		log_error("syntax_error\n");
}
