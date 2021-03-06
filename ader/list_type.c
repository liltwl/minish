/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:07:06 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/10 20:07:09 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_type(t_type *type)
{
	int		i;

	i = 0;
	if (type)
	{
		while (type)
		{
			i++;
			type = type->next;
		}
	}
	return (i);
}

t_type	*ft_lstlast_type(t_type *type)
{
	if (!type)
		return (type);
	while (type->next)
		type = type->next;
	return (type);
}

t_type	*ft_lstnew_type2(char *content, int i, int a)
{
	t_type	*new;

	new = (t_type *)malloc(sizeof(t_type) * 1);
	new->word = content;
	new->type = i;
	new->a = a;
	new->next = NULL;
	return (new);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->str = NULL;
	cmd->args_list = NULL;
	cmd->in = 0;
	cmd->out = 1;
}
