/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:52:55 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/08 19:36:37 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_env(t_data *data, t_cmd *cmd)
{
	t_list	*l;
	t_env	*env;

	l = data->env;
	if (cmd->str[1])
	{
		data->exitstatu = 127;
		return ;
	}
	while (l != NULL)
	{
		env = l->content;
		ft_putstr_fd(env->name, cmd->out);
		write(cmd->out, "=", 1);
		ft_putstr_fd(env->content, cmd->out);
		write(cmd->out, "\n", 1);
		l = l->next;
	}
	data->exitstatu = 0;
}

void	do_pwd(t_data *l, t_cmd *cmd)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (cmd->str[1])
		l->exitstatu = 1;
	else
	{
		ft_putstr_fd(str, cmd->out);
		write(cmd->out, "\n", 1);
	}
	l->exitstatu = 0;
}
