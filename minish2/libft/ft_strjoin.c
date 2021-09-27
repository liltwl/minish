/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:21:29 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/13 16:27:44 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	if (!(p = malloc(i + j + 1)))
		return (0);
	ft_strcpy(p, (char *)s1);
	ft_strcpy(&p[i], (char *)s2);
	return (p);
}
