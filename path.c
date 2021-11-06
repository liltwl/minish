/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 00:34:36 by macbookpro        #+#    #+#             */
/*   Updated: 2021/11/06 20:21:14 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*my_ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*p;
// 	int		i;
// 	int		j;

// 	i = ft_strlen((char *)s1);
// 	j = ft_strlen((char *)s2);
// 	p = malloc(i + j + 2);
// 	if (!(p))
// 		return (0);
// 	ft_strcpy(p, (char *)s1);
// 	ft_strcpy(&p[i], "/");
// 	ft_strcpy(&p[i + 1], (char *)s2);
// 	return (p);
// }

// char	*get_absolute_path(char **path, char *str)
// {
// 	int		i;
// 	int		fd;
// 	char	*cmd;

// 	i = 0;
// 	while (path[i])
// 	{
// 		cmd = my_ft_strjoin(path[i], str);
// 		fd = open(cmd, O_RDONLY);
// 		if (fd > 0)
// 			return (cmd);
// 		free(cmd);
// 		i++;
// 	}
// 	return (NULL);
// }

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
