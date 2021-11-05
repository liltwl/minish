/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:47:07 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/05 12:01:48 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_myatoi(char *str)
{
	unsigned long long	m;
	int					i;
	int					n;

	m = 0;
	n = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		n = -1;
		if (str[++i] == '-')
			ft_error("", 255);
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		m = (m * 10) + (str[i++] - 48);
		if ((m > 9223372036854775807 && n > 0)
			|| (m - 1 > 9223372036854775807 && n < 0))
			ft_error("", 255);
	}
	if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		ft_error("", 255);
	return (m * n);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	char	i;
	char	**p;

	i = data->exitstatu;
	if (cmd == NULL)
		exit (i);
	p = cmd->str;
	if (p[1] && p[2])
	{
		data->exitstatu = 1;
		ft_putstr_fd("", cmd->out);
		return ;
	}
	else if (p[1])
		i = (char)ft_myatoi(p[1]);
	exit (i);
}
