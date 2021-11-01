/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:46:10 by ael-fadi          #+#    #+#             */
/*   Updated: 2019/10/22 01:36:16 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	p;
	size_t	l;

	p = 0;
	l = 0;
	while (src[l])
		l++;
	if (size == 0)
		return (l);
	while (p < l && p < size - 1)
	{
		dest[p] = src[p];
		p++;
	}
	dest[p] = '\0';
	return (l);
}
