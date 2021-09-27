/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:15:42 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/10 15:41:47 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *p;

	p = (unsigned char*)dst;
	if (!dst && !src)
		return (NULL);
	if (!ft_memcmp(dst, src, n))
		return (p);
	while (n-- > 0)
		*(unsigned char*)dst++ = *(unsigned char*)src++;
	return (p);
}
