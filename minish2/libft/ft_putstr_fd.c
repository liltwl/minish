/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:15:24 by otaouil           #+#    #+#             */
/*   Updated: 2019/12/14 02:12:26 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		ft_putchar_fd(s[i++], fd);
	return (i);
}
