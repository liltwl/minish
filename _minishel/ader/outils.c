/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:19:25 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/10 19:43:26 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_string(char *str, char c)
{
	size_t		i;
	char		*p;

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
	char	**tab;
	int		i;

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
	free (tab);
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

