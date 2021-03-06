/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 03:23:05 by macbook           #+#    #+#             */
/*   Updated: 2021/11/10 22:26:22 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(void *content)
{
	t_env	*tmp;

	tmp = (t_env *)content;
	free(tmp->content);
	free(tmp->name);
	free(tmp);
}

void	free_table(char **table)
{
	int	i;

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
	t_list	*args;
	t_list	*help;

	tmp = (t_cmd *)content;
	args = tmp->args_list;
	while (args)
	{
		if (args->next)
			help = args->next;
		else
			help = NULL;
		free(args->content);
		free(args);
		args = help;
	}
	free(tmp->cmd);
	free_table(tmp->str);
	free(tmp);
}

void	free_char(void *content)
{
	free(content);
}
