/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtintools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:49:54 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/04 19:57:22 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_splitlen(char **p)
{
	int i;

	i = 0;
	while (p[i])
		i++;
	return (i);
}
 
char    **ft_free_split(char **d)
{
	int				i;

	i = 0;
	if (d == NULL)
		return (NULL);
	while (d[i])
	{
		if (d[i])
			free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

char    **ft_print_split(char **d)
{
	int				i;

	i = 0;
	if (d == NULL)
		return (NULL);
	while (d[i])
	{
		printf("\n**%s**\n", d[i]);
		i++;
	}
	return (NULL);
}

t_env		*ft_lstfind(t_list *lst, char *name)
{
	t_env *env;

	while (lst)
	{
		env = (t_env *)lst->content;
		if (!strncmp(name, env->name, strlen(env->name) + 1))
			return (env);
		else
			lst = lst->next;
	}
	return (NULL);
}

t_cmd	*ft_findcmd(t_list *data, int id)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	while (tmp && ++i < g_data->numcmd)
	{
		tmp = data->content;
		if (i == id)
			return (tmp);
		data = data->next;
	}
	return (NULL);
}
