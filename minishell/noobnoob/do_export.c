/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:49:50 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/05 12:00:51 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addnewenv(char	**p, t_data *data)
{
	t_env	*env;
	t_env	*tmp;

	env = ft_lstfind(data->env, p[0]);
	if (env)
	{
		free (env->content);
		if (p[1])
			env->content = strdup(p[1]);
		else
			env->content = strdup("");
	}
	else
	{
		if (p[1])
			env = ft_lstnewenv(p[0], p[1]);
		else
			env = ft_lstnewenv(p[0], "");
		tmp = ft_lstlast(data->env)->content;
		ft_lstadd_back(&data->env, ft_lstnew((void *)env));
	}
}

char	**mycatstr(char *str, int i)
{
	char	**p;
	char	*tmp;

	p = malloc(sizeof(char **) * 3);
	if (i)
	{
		tmp = malloc(i + 2);
		if (str[i - 1] == '+')
			ft_strlcpy(tmp, str, i);
		else
			ft_strlcpy(tmp, str, i + 1);
		p[0] = tmp;
		tmp = malloc(strlen(&str[i] + 2) + 2);
		ft_strlcpy(tmp, &str[i + 1], strlen(&str[i]));
		p[1] = tmp;
		p[2] = NULL;
	}
	else
	{
		p[0] = ft_strdup(str);
		p[1] = NULL;
	}
	return (p);
}

void	export_join(t_data *data, char **p)
{
	char	*str;
	char	*tmp;
	t_env	*env;

	env = ft_lstfind(data->env, p[0]);
	if (env)
	{
		if (p[1])
			str = strdup(p[1]);
		else
			str = strdup("");
		tmp = ft_strjoin(env->content, str);
		free (env->content);
		free (str);
		env->content = tmp;
	}
	else
		addnewenv(p, data);
}

void	ft_lstupdate(t_data *data, char **str, int j)
{
	int		i;
	char	**p;

	i = 0;
	data->exitstatu = 1;
	while (str[++i])
	{
		j = ft_findc(str[i], '=');
		p = mycatstr(str[i], j);
		if (!ft_isalpha(str[i][0]) && str[i][0] != '_')
			data->exitstatu = 1;
		else if (j)
		{
			if (ft_strchr(p[0], '+'))
				return ;
			if (str[i][j - 1] == '+')
				export_join(data, p);
			else
				addnewenv(p, data);
		}
		else
			addnewenv(p, data);
		ft_free_split(p);
	}
	data->exitstatu = 0;
}

void	do_export(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**str;

	str = cmd->str;
	i = 0;
	if (!str[1])
		ft_printsortlst(data, cmd);
	else
		ft_lstupdate(data, str, 0);
}
