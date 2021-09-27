/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:23:30 by otaouil           #+#    #+#             */
/*   Updated: 2019/11/14 18:17:50 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_fd(int n, int fd)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		i++;
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			i++;
			n %= 1000000000;
		}
		n *= -1;
	}
	if (n < 10)
		i += ft_putchar_fd(n + '0', fd);
	else if (n >= 10)
	{
		i += ft_putnbr_fd(n / 10, fd);
		i += ft_putchar_fd(n % 10 + '0', fd);
	}
	return (i);
}
