/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:14:41 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/25 16:22:48 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	spaces(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\v' || c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				sign;
	int				i;

	res = 0;
	sign = 0;
	i = 0;
	while (spaces(str[i]) == 1)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		res = res * 10 + ((int)str[i++] - '0');
	if (res > 2147483648 && sign == -1)
		return (0);
	if (res > 2147483647 && sign != -1)
		return (-1);
	if (sign == -1)
		return (res * -1);
	return (res);
}
