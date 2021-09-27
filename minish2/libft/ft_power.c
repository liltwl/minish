/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:42:10 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/15 12:42:13 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int nb, int power)
{
	int i;

	i = nb;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else if (power >= 1)
		i *= ft_power(nb, power - 1);
	return (i);
}
