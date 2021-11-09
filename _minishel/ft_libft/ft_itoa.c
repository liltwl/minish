/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:29:22 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/25 16:27:40 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*ft_zero(void)
{
	char	*str;

	(str = (char *)malloc(sizeof(char) * 2));
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*limit(char *src)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	i += 1;
	p = (char *)malloc(i * sizeof(char));
	if (p == 0)
		return (0);
	while (src[j] != '\0')
	{
		p[j] = src[j];
		j++;
	}
	p[j] = '\0';
	return (p);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		i;

	if (nb == -2147483648)
		return (limit("-2147483648"));
	if (nb == 0)
		return (ft_zero());
	i = len(nb) + 1;
	str = (char *)malloc(sizeof(char) * i);
	i -= 1;
	str[i] = '\0';
	i -= 1;
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[i] = 48 + (nb % 10);
		nb = nb / 10;
		i--;
	}
	return (str);
}
