/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:48:20 by mamali            #+#    #+#             */
/*   Updated: 2021/11/05 06:38:18 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo $"$'hf$PWD'gh"hfh

t_type	*function(int dblq, int single, size_t i)
{
	t_type *type;

	type = NULL;
	while (1)
	{
		if (g_data->line[i] == '\'' && single == 0 && dblq == 0)
			single = add_sq(&i, '\'', &type);
		else if (g_data->line[i] == '\''  && single == 1 && dblq == 0)
			single = 0;
		else if (g_data->line[i] == '"' && single == 0 && dblq == 0)
			dblq = add_sq(&i, '"', &type);
		else if (g_data->line[i] == '"' && single == 0 && dblq == 1)
			dblq = 0;
		else if (g_data->line[i] == '|' && single == 0 && dblq == 0)
		{
			ft_lstadd_back(&g_data->tokkens, ft_lstnew(type));
			type = NULL;
		}
		else if (g_data->line[i] == '>' && single == 0 && dblq == 0)
			add_out(&i, '>', &type);
		else if (g_data->line[i] == '<' && single == 0 && dblq == 0)
			add_in(&i, '<', &type);
		else if (g_data->line[i] != ' ')
			adds(&i, &type);
		if (i++ >= ft_strlen(g_data->line) - 1)
			break;
	}
	return (type);
}

void	parser(void)
{
	t_type	*type;
	t_list	*tmp1;
	char 	*str;

	str = NULL;

	type = function(0, 0, 0);
	if (type)
		ft_lstadd_back(&g_data->tokkens, ft_lstnew(type));
	tmp1 = g_data->tokkens;
	syntax_error(tmp1);
	expand_cmdlist(tmp1, str);
	ft_lstclear(&g_data->tokkens, &free_type);
}
