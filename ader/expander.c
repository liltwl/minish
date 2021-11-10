/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:29:10 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/10 19:36:55 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_lk(char *s, int a, t_cl *tmp, t_list **list_keys)
{
	tmp = malloc(sizeof(t_cl));
	tmp->c = s[a];
	ft_lstadd_back(list_keys, ft_lstnew(tmp));
}

char	*return_env_value(char *key)
{
	t_list	*env;
	t_env	*tmp;
	size_t	i;

	env = g_data->env;
	i = 0;
	while (env)
	{
		tmp = (t_env *)env->content;
		i = ft_strlen(tmp->name);
		if (i == ft_strlen(key))
		{
			if (ft_strcmp(tmp->name, key) == 0)
				return (tmp->content);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

void	to_skip2(char *s, size_t *a, t_list **head, t_cl *tmp)
{
	char	*swap;
	t_list	*list_keys;

	list_keys = NULL;
	swap = NULL;
	(*a)++;
	while (ft_isalnum(s[(*a)]) == 1)
		add_to_lk(s, (*a)++, tmp, &list_keys);
	swap = ll_to_string(list_keys);
	ft_lstclear(&list_keys, &free_char);
	add_string(head, return_env_value(swap));
	free(swap);
	(*a)--;
}

static void	to_skip(char *s, size_t *a, t_list **head, size_t i)
{
	t_cl	*tmp;
	t_list	*list_keys;
	char	*key;

	list_keys = NULL;
	tmp = NULL;
	if (s[i + 1] == '\'' || s[i + 1] == '?')
	{
		if (s[i + 1] == '?')
		{
			key = ft_itoa(g_data->exitstatu);
			(*a)++;
		}
		else
		{
			add_to_lk(s, *a, tmp, &list_keys);
			key = ll_to_string(list_keys);
			ft_lstclear(&list_keys, &free_char);
		}
		add_string(head, key);
		free(key);
		return ;
	}
	to_skip2(s, a, head, tmp);
}

void	expand_word2(char *str, t_list **head, int a, size_t i)
{
	t_cl	*tmp;
	size_t	f;

	while (1)
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = str[i];
		if (str[i] == '$')
		{
			f = i;
			to_skip(str, &i, head, f);
			free(tmp);
		}
		else if (str[i] == ' ' && a == 0)
		{
			ft_lstadd_back(head, ft_lstnew(tmp));
			while (str[i] == ' ')
				i++;
			i--;
		}
		else
			ft_lstadd_back(head, ft_lstnew(tmp));
		if (i++ >= ft_strlen(str) - 1)
			break ;
	}
}
