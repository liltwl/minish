/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:26:07 by otaouil           #+#    #+#             */
/*   Updated: 2019/12/11 17:09:14 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(int n)
{
	int i;

	i = 0;
	while (n >= 10 || n <= -10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

void	ft_comnbr(int nb, char *s)
{
	int		i;
	int		n;
	int		j;

	j = 0;
	n = nb;
	i = ft_power(10, ft_intlen(n));
	while (i > 0)
	{
		n = nb / i;
		nb %= i;
		s[j++] = n + '0';
		i /= 10;
	}
	s[j] = '\0';
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;

	i = 0;
	if (!(p = malloc(ft_intlen(n) + 1)))
		return (0);
	if (n == -2147483648)
	{
		n %= 1000000000;
		*p = '-';
		p[1] = '2';
		n *= -1;
		i = 2;
	}
	else if (n < 0)
	{
		*p = '-';
		n *= -1;
		i = 1;
	}
	ft_comnbr(n, &p[i]);
	return (p);
}
