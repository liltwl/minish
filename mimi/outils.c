/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:19:25 by macbookpro        #+#    #+#             */
/*   Updated: 2021/10/29 17:31:33 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_string(char *str, char c)
{
	size_t		i;
	char	*p;
	i = 0;
	
	if (str == NULL)
	{
		p = strdup("");
		return (make_string(p, c));
	}
	p = malloc(sizeof(str) * (strlen(str) + 2));
	while (i < strlen(str))
	{
		p[i] = str[i];
		i++;
	}
	p[i] = c;
	p[++i] = '\0';
	return (p);
}

void	add_string(t_list **head, char *str)
{
	t_cl	*tmp;
	int		i;

	i = 0;
	if (!str[i])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = '\0';
		ft_lstadd_back(head, ft_lstnew(tmp));
	}
	while (str[i])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = str[i];
		ft_lstadd_back(head, ft_lstnew(tmp));
		i++;
	}
}

void	add_tab_to_ll(t_type **head, char *str, int type, int a)
{
	char **tab;
	int	i;

	i = 0;
	if (!str[0])
	{
		ft_lstadd_back_type(head, ft_lstnew_type2(ft_strdup(""), type, a));
		return ;
	}
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		ft_lstadd_back_type(head, ft_lstnew_type2(tab[i], type, a));
		i++;
	}
}

void	free_nodes_types(t_type	**tmp)
{
	t_type	*tmp2;
	//tmp2 = *tmp;
	//print_types(*tmp);
	while (*tmp)
	{
		tmp2 = *tmp;
		*tmp = (*tmp)->next;
		if (tmp2->word != NULL)
			free(tmp2->word);
		free(tmp2);
	}
}
void	free_nodes_env(t_list	**tmp)
{
	t_env	*tmp2;
	while (*tmp)
	{
		tmp2 = (*tmp)->content;
		*tmp = (*tmp)->next;
		if (tmp2->name != NULL)
			free(tmp2->name);
		if (tmp2->content != NULL)
			free(tmp2->content);
		free(tmp2);
	}
}

void	free_nodes_cmd(t_list	*tmp)
{
	t_cmd	*tmp2;
	t_type *t;
	t_list	*p;

	while (tmp)
	{
		tmp2 = (tmp)->content;
		p = (tmp2->args_list);
		t = (t_type *)p->content;
		//print_types(t);
		tmp = (tmp)->next;
		if (tmp2->cmd != NULL)
			free(tmp2->cmd);
		ft_free_split(tmp2->str);
		/*if (t)
			free_nodes_types(&t);*/
		free(tmp2);
	}
}
	
void	free_functio(void)
{
	// 	printf("-----------------eeee-------------------\n");
	// 	t_cmd *cmd = (t_cmd *)g_data->cmd_list;
	// print_types((t_type *)cmd->args_list->content);
	// 	printf("-------------------zzzzz-----------------\n");

		// printf("------------------------------------\n");
		// printf("------------------------------------\n");

	free(g_data->line);
	free_nodes_cmd(g_data->cmd_list);
	//free_nodes_env(&g_data->env);
	//printlist(g_data->env);
	t_type *t = (t_type *)g_data->tokkens->content;
	free_nodes_types(&t);
}
