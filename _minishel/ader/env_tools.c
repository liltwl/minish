/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:29:01 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/10 19:29:04 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env_list(char **envp)
{
	int		i;
	char	**s;
	t_env	*a;
	t_list	*env;

	g_data = malloc(sizeof(t_data));
	i = 1;
	a = malloc(sizeof(t_env));
	s = ft_split(envp[0], '=');
	a->name = ft_strdup(s[0]);
	a->content = ft_strdup(s[1]);
	free_table(s);
	env = ft_lstnew(a);
	while (envp[i])
	{
		s = ft_split(envp[i], '=');
		a = malloc(sizeof(t_env));
		a->name = ft_strdup(s[0]);
		a->content = ft_strdup(s[1]);
		ft_lstadd_back(&(env), ft_lstnew(a));
		free_table(s);
		i++;
	}
	g_data->env = env;
	g_data->exitstatu = 0;
}

void	expand_word(char *str, t_list **head, int a, size_t i)
{
	t_cl	*tmp;

	if (!str[i])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = '\0';
		ft_lstadd_back(head, ft_lstnew(tmp));
		return ;
	}
	expand_word2(str, head, a, i);
}

t_type	*expander(t_type *tmp)
{
	t_type	*new;
	t_list	*head;
	char	*to_str;

	new = NULL;
	while (tmp)
	{
		head = NULL;
		if (tmp->type == 2 || tmp->type == 0)
			expand_word(tmp->word, &head, tmp->type, 0);
		else
			add_string(&head, tmp->word);
		if (tmp->type == 0)
		{
			to_str = ll_to_string(head);
			add_tab_to_ll(&new, to_str, tmp->type, tmp->a);
			free(to_str);
		}
		else
			ft_lstadd_back_type(&new, ft_lstnew_type2(ll_to_string(head), tmp->type, tmp->a));
		ft_lstclear(&head, &free_char);
		tmp = tmp->next;
	}
	return (new);
}
