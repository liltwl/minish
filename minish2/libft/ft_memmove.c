/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 00:40:47 by otaouil           #+#    #+#             */
/*   Updated: 2019/11/09 21:49:44 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*str;
	const char	*str1;
	size_t		i;

	str = (char *)dst;
	str1 = (char *)src;
	i = 0;
	if (!str && !str1)
		return (NULL);
	if (!ft_memcmp(dst, src, len))
		return (dst);
	if (str1 < str)
		while (i++ < len)
			str[len - i] = str1[len - i];
	else
		while (len--)
			*str++ = *str1++;
	return (dst);
}
