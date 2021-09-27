/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:57:36 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/11 20:11:38 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*str;
	const unsigned char	*str1;

	str = (unsigned char*)dst;
	str1 = (unsigned char*)src;
	while (n-- > 0 && *str1)
	{
		*(str++) = *(str1);
		if ((*str1 == (unsigned char)c))
			return (str);
		str1++;
	}
	return (NULL);
}
