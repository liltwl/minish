/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:52:15 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/07 20:08:09 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_oldpwd(t_data *data)
{
	char	*str;
	t_env	*oldpwd;

	oldpwd = ft_lstfind(data->env, "OLDPWD");
	str = oldpwd->content;
	oldpwd->content = ft_strdup(ft_lstfind(data->env, "PWD")->content);
	free (str);
}

void	change_pwd(t_data *data)
{
	char	*str;
	t_env	*pwd;

	pwd = ft_lstfind(data->env, "PWD");
	str = pwd->content;
	free (str);
	str = getcwd(NULL, 0);
	if (!(str))
		return ;
	pwd->content = ft_strdup(str);
	free (str);
}

void	ft_docdret(t_data *data)
{
	t_env	*lst;
	char	*src;

	lst = ft_lstfind(data->env, "OLDPWD");
	if (lst)
	{
		src = ft_strdup(lst->content);
		change_oldpwd(data);
		chdir(src);
		free(src);
		change_pwd(data);
		data->exitstatu = 0;
	}
	else
		data->exitstatu = 1;
}

void	ft_docdsing(t_data *data, t_cmd *cmd)
{
	t_env	*lst;
	char	*src;

	lst = ft_lstfind(data->env, "HOME");
	if (lst)
	{
		src = ft_strdup(lst->content);
		change_oldpwd(data);
		chdir(src);
		free(src);
		change_pwd(data);
		data->exitstatu = 0;
	}
	else
		data->exitstatu = 1;
	if (ft_strlen(cmd->str[1]) > 2)
	{
		
	}
}

void	ft_docd(t_data *data, t_cmd *cmd)
{
	char		**str;

	str = cmd->str;
	if (str[1] && !(ft_cmp("-", str[1])))
		ft_docdret(data);
	else if (str[1][0] == '~')
		ft_docdsing(data, cmd);
	else if (str[1])
	{
		if (chdir(str[1]) < 0)
		{
			perror("cd");
			data->exitstatu = 1;
			return ;
		}
		change_oldpwd(data);
		change_pwd(data);
		data->exitstatu = 0;
	}
}
