/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:28:25 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/10 19:28:37 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_sq(int *i, t_type **tmp2, int *f, char *str)
{
	*f = 1;
	str = get_sq_word((*tmp2), 1, f);
	while ((*tmp2) && *f != 0)
	{
		(*f)--;
		(*tmp2) = (*tmp2)->next;
	}
	*i += ft_strlen(str) + 1;
	if (g_data->line[*i] != '\'')
		return (-1);
	return (0);
}

int	check_dblq(int *i, t_type **tmp1, int *f, char *str)
{
	*f = 1;
	str = get_sq_word((*tmp1), 2, f);
	while ((*tmp1) && *f != 0)
	{
		(*f)--;
		(*tmp1) = (*tmp1)->next;
	}
	*i += ft_strlen(str) + 1;
	if (g_data->line[*i] != '"')
		return (-1);
	return (0);
}

int	check_words2(int *i, t_type *tmp2)
{
	while (tmp2)
	{
		if (is_redirection(tmp2->type))
			if (!(tmp2->next))
				return (0);
		tmp2 = tmp2->next;
	}
	if (g_data->line[*(i)] == '\0')
		return (1);
	(*i)++;
	ft_spaceskip(g_data->line, i);
	if (g_data->line[*i] == '|')
		return (0);
	return (1);
}

int	check_words(t_type *tmp, int *i)
{
	t_type	*tmp2;
	t_type	*tmp1;
	int		f;

	tmp2 = tmp;
	tmp1 = tmp;
	while (g_data->line[*(i)] && g_data->line[*(i)] != '|')
	{
		if (g_data->line[*(i)] == '\'')
		{
			if (check_sq(i, &tmp2, &f, NULL) == -1)
				return (0);
		}
		else if (g_data->line[*(i)] == '"')
		{
			if (check_dblq(i, &tmp1, &f, NULL) == -1)
				return (0);
		}
		(*i)++;
	}
	return (check_words2(i, tmp));
}
