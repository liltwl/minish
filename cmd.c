/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:23:27 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/05 04:00:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_args(t_type **tmp, t_list **args)
{
	char	*str;
	int		i;

	i = 0;
	if ((*tmp)->a == 1)
	{
		while ((*tmp)->a == 1)
		{
			if (i == 0)
				str = ft_strjoin((*tmp)->word, (*tmp)->next->word);
			else
				str = ft_strjoin(str, (*tmp)->next->word);
			i++;
			(*tmp) = (*tmp)->next;
		}
		ft_lstadd_back(args, ft_lstnew(str));
	}
	else
		ft_lstadd_back(args, ft_lstnew((*tmp)->word));
}

t_type	*get_cmd(t_type *type)
{
	t_type	*tmp;
	int		i;

	tmp = type;
	i = 0;
	while (tmp->next->word[i] != '-')
		tmp = tmp->next;
	return (tmp);
}

t_type	*get_node(t_type *types)
{
	int		a;
	t_type	*tmp;

	a = 2;
	tmp = types;
	while (a-- && tmp)
		tmp = tmp->next;
	return (tmp);
}

t_list	*fill_list(size_t *i, char c)
{
	t_cl	*tmp;
	t_list  *list;

	list = NULL;
	while (g_data->line[(*i)] != c && g_data->line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = g_data->line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	return (list);
}
