/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:57:15 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/28 13:50:53 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	x;
	char			nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		x = n * -1;
	}
	else
		x = n;
	if (x > 10)
		ft_putnbr_fd(x / 10, fd);
	nb = x % 10 + 48;
	write(fd, &nb, 1);
}
