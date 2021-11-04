/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:47:39 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/04 19:57:43 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_deletlst(char *name, t_list *env)
{
	t_env	*lst;
	t_list	*tmplst;

	tmplst = NULL;
	while ((env))
	{
		lst = (env)->content;
		if (!strncmp(name, lst->name, strlen(lst->name) + 1))
			break ;
		tmplst = (env);
		(env) = (env)->next;
	}
	if (!(env))
		return ;
	if (tmplst)
		tmplst->next = (env)->next;
	else
		g_data->env = (env)->next;
	free (lst->content);
	free (lst->name);
	free (lst);
	free ((env));
}


void	do_unset(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**str;

	i = 0;
	str = cmd->str;
	if (!str[1])
		return ;
	while (str[++i])
		ft_deletlst(str[i], data->env);
	data->exitstatu = 0;
 }
 