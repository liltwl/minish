/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 03:23:05 by macbook           #+#    #+#             */
/*   Updated: 2021/11/06 16:35:52 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void *content)
{
	t_env   *tmp;

	tmp = (t_env *)content;
	free(tmp->content);
	free(tmp->name);
	free(tmp);
}

void	free_table(char **table)
{
	int i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	table = NULL;
}

void	free_type(void *content)
{
	t_type	*tmp;

	tmp = (t_type *)content;
	free_nodes_types(&tmp);
}

void	free_cmd(void *content)
{
	t_cmd	*tmp;

	tmp = (t_cmd *)content;
	free(tmp->cmd);
	// ft_lstclear(&tmp->args_list, &free_type);
	free_table(tmp->str);
	free(tmp);
}

void	free_char(void *content)
{
	free(content);
}

void clear_and_exit(void)
{
	ft_lstclear(&g_data->env, &free_env);
	ft_lstclear(&g_data->cmd_list, &free_cmd);
	// ft_lstclear(&g_data->tokkens, &free_type);
	free(g_data->line);
	// free(g_data);
}

void	free_nodes_types(t_type	**list)
{
	t_type	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		if (tmp->word != NULL)
			free(tmp->word);
		free(tmp);
	}
}
