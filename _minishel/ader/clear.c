/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 03:23:05 by macbook           #+#    #+#             */
/*   Updated: 2021/11/09 18:44:11 by macbookpro       ###   ########.fr       */
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
	t_list	*tmp1;
	//char *str;

	tmp = (t_cmd *)content;
	//str = (char	*)tmp->args_list->content;
	//free (str);
	while(tmp->args_list)
	{
		tmp1 = tmp->args_list;
		tmp->args_list = tmp->args_list->next;
		free(tmp1);	
	}
	free(tmp->cmd);
	free_table(tmp->str);
	free(tmp);
}

void	free_char(void *content)
{
	free(content);
}
