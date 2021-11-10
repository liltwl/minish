/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:28:48 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/10 19:28:49 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ll_to_string(t_list *head)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize(head);
	str = malloc(len + 1);
	while (head)
	{
		str[i] = ((t_cl *)head->content)->c;
		i++;
		head = head->next;
	}
	str[len] = '\0';
	return (str);
}

char	**ll_to_dp(t_list *list)
{
	int		len;
	int		i;
	char	*l;
	char	**str;

	len = ft_lstsize(list);
	str = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (list)
	{
		str[i] = ft_strdup(list->content);
		l = (char *)list->content;
		i++;
		list = list->next;
	}
	str[i] = 0;
	return (str);
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
