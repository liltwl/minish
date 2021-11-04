/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:54:51 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/04 19:57:18 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_smllst(t_list *env)
{
	char	*str;
	t_env	*tmp;

	tmp = (t_env *)env->content;
	str = tmp->name;
	env = env->next;
	while (env && tmp->name)
	{
		tmp = (t_env *)env->content;
		if (ft_memcmp(str, tmp->name, strlen(str) + 1) < 0)
			str = tmp->name;
		env = env->next;
	}
	tmp = ft_lstfind(env, str);
	return (tmp);
}

t_env	*ft_getbiglst(t_list *tmp1, t_env *big)
{
	t_env	*tmp;
	char	*c;
	char	*p;
	t_env	*env;

	p = NULL;
	if (big)
		p = strdup(big->name);
	c = strdup("~~~~~~~~");
	while (tmp1)
	{
		env = (t_env *)tmp1->content;
		if ((ft_memcmp(c, env->name, strlen(c) + 1) > 0 && !p)||
			((p && ft_memcmp(p, env->name, strlen(env->name) + 1) < 0)
			&& ft_memcmp(c, env->name, strlen(env->name) + 1) > 0))
		{
			tmp = env;
			free (c);
			c = strdup(env->name);
		}
		tmp1 = tmp1->next;
	}
	free (c);
	free (p);
	return (tmp);
}

void	ft_printsortlst(t_data	*data, t_cmd *cmd)
{
	int		i;
	t_env	*tmp;

	tmp = NULL;
	i = 0;
	while (i < ft_lstsize(data->env))
	{
		i++;
		tmp = ft_getbiglst(data->env, tmp);
		write(cmd->out, "declare -x ", 11);
		write(cmd->out, tmp->name, strlen(tmp->name));
		if (tmp->content[0])
		{
			write(cmd->out, "=\"", 2);
			write(cmd->out, tmp->content, strlen(tmp->content));
			write(cmd->out, "\"", 1);
		}
		write(cmd->out, "\n", 1);
	}
}

int	ft_findc(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

t_env	*ft_lstnewenv(char *name, char *str)
{
	t_env	*elt;

	if (!(elt = (t_env *)malloc(sizeof(* elt))))
		return (NULL);
	elt->name = ft_strdup(name);
	elt->content = ft_strdup(str);
	return (elt);
}
