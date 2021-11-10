/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:34:36 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/10 22:30:42 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_dpointer(char	**tokkens)
{
	int		i;

	i = 0;
	while (tokkens[i])
	{
		free(tokkens[i]);
		i++;
	}
	free(tokkens);
}

char	*get_absolute_path(char **pa, char *cmd)
{
	int			i;
	char		*str;
	char		*tmp;
	int			fd;

	i = 0;
	fd = open(cmd, O_RDONLY);
	if (fd > 0)
		return (ft_strdup(cmd));
	while (pa[i])
	{
		str = ft_strjoin(pa[i], "/");
		tmp = str;
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		fd = open(str, O_RDONLY);
		if (fd > 0)
			return (str);
		free(str);
		i++;
	}
	return (ft_strdup(cmd));
}

char	*get_cmd_path(char *str, t_list *env)
{
	t_list	*env_tmp;
	char	**path;
	char	*cmd;
	t_env	*env_l;

	env_tmp = env;
	while (env_tmp)
	{
		env_l = env_tmp->content;
		if (!(ft_strncmp(env_l->name, "PATH", 4)))
			cmd = env_l->content;
		env_tmp = env_tmp->next;
	}
	path = ft_split(cmd, ':');
	str = get_absolute_path(path, str);
	free_table(path);
	return (str);
}

void	ffunction(t_type **head, char **tab, size_t i, int f)
{
	int		l;

	l = 0;
	while (tab[l])
		l++;
	if (l == 1)
	{
		if ((g_data->line[i] == '\'' || \
			g_data->line[i] == '"') && g_data->line[i - 1] != ' ')
			ft_lstadd_back_type(head, ft_lstnew_type(tab[0], 0, 1));
		else
			ft_lstadd_back_type(head, ft_lstnew_type(tab[0], 0, 0));
		return ;
	}
	ffunction2(head, tab, i, f);
}

int	adds(size_t *i, t_type **head)
{
	t_cl	*tmp;
	t_list	*list;
	char	**tab;
	char	*str;

	list = NULL;
	while ((g_data->line[(*i)] != '\'' && g_data->line[(*i)] != '"'
			&& g_data->line[(*i)] != '|' && g_data->line[(*i)] != '>'
			&& g_data->line[(*i)] != '<') && g_data->line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = g_data->line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	str = ll_to_string(list);
	tab = ft_split(str, ' ');
	ffunction(head, tab, *i, 0);
	free_table(tab);
	free(str);
	ft_lstclear(&list, &free_char);
	(*i)--;
	return (1);
}
