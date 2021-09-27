/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:04:13 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/25 21:04:17 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *ch, size_t len)
{
	int		i;
	size_t	n;

	n = ft_strlen((char *)ch);
	i = -1;
	if (!ch || !src)
		return ((char *)src);
	while (src[++i] && (size_t)i < len--)
		if (!ft_strncmp((char *)&src[i], (char *)ch, n))
			return ((char *)src + i);
	return (NULL);
}
