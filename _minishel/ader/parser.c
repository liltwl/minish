/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:48:20 by mamali            #+#    #+#             */
/*   Updated: 2021/11/09 18:48:41 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// echo $"$'hf$PWD'gh"hfh

void	function2(int *dblq, int *single, size_t *i, t_type **type)
{
	if (g_data->line[*i] == '\'' && *single == 0 && *dblq == 0)
		*single = add_sq(i, '\'', type);
	else if (g_data->line[*i] == '\'' && *single == 1 && *dblq == 0)
		*single = 0;
	else if (g_data->line[*i] == '"' && *single == 0 && *dblq == 0)
		*dblq = add_sq(i, '"', (type));
	else if (g_data->line[*i] == '"' && *single == 0 && *dblq == 1)
		*dblq = 0;
	else if (g_data->line[*i] == '|' && *single == 0 && *dblq == 0)
	{
		ft_lstadd_back(&g_data->tokkens, ft_lstnew((*type)));
		(*type) = NULL;
	}
	else if (g_data->line[*i] == '>' && *single == 0 && *dblq == 0)
		add_out(i, '>', (type));
	else if (g_data->line[*i] == '<' && *single == 0 && *dblq == 0)
		add_in(i, '<', (type));
	else if (g_data->line[*i] != ' ')
		adds(i, (type));
}

t_type	*function(int dblq, int single, size_t i)
{
	t_type	*type;

	type = NULL;
	while (1)
	{
		function2(&dblq, &single, &i, &type);
		if (i++ >= ft_strlen(g_data->line) - 1)
			break ;
	}
	return (type);
}

void	parser(void)
{
	t_type	*type;
	t_list	*tmp1;
	char	*str;

	str = NULL;
	type = function(0, 0, 0);
	if (type)
		ft_lstadd_back(&g_data->tokkens, ft_lstnew(type));
	tmp1 = g_data->tokkens;
	syntax_error(tmp1);
	expand_cmdlist(tmp1, str);
	ft_lstclear(&g_data->tokkens, &free_type);
}

void	free_functio(void)
{
	t_type	*t;

	free(g_data->line);
	free_nodes_cmd(g_data->cmd_list);
	t = (t_type *)g_data->tokkens->content;
	free_nodes_types(&t);
}

void	expand_cmdlist(t_list *tmp, char *str)
{
	t_cmd	*cmd;
	t_type	*expanded_types;
	t_list	*list_files;
	t_type	*tmp2;

	if (g_data->syntx == 1)
	{
		cmd = NULL;
		return ;
	}
	while (tmp)
	{
		tmp2 = tmp->content;
		expanded_types = expander(tmp->content);
		cmd = malloc(sizeof(t_cmd));
		init_cmd(cmd);
		get_command(tmp2, str, &cmd, &expanded_types);
		list_files = get_args(&(cmd->args_list), expanded_types, &cmd);
		get_out(&(cmd->out), list_files, expanded_types);
		get_in(&(cmd->in), list_files, expanded_types);
		ft_lstadd_back(&g_data->cmd_list, ft_lstnew(cmd));
		free_nodes_types(&expanded_types);
		//free(expanded_types);
		tmp = tmp->next;
	}
	g_data->numcmd = ft_lstsize(g_data->cmd_list);
}
