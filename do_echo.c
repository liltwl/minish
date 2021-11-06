/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:53:48 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/04 19:57:31 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_help(void)
{
	ft_putstr_fd("Available commands:\n", 1);
	ft_putstr_fd("echo\ncd\npwd\nexport\nunset\nenv\nexit\n", 1);
}

void	do_echo(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**str;

	str = cmd->str;
	i = 0;
	j = 0;
	while (!ft_strncmp(str[++i], "-n", 3))
		j = 1;
	while(str[i])
	{
		write(cmd->out, str[i], strlen(str[i]));
		if (str[++i])
			write(cmd->out, " ", 1);
	}
	if (j == 0)
		write(cmd->out, "\n", 1);
	data->exitstatu = 0;
}