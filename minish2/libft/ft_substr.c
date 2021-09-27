/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:35:10 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/13 15:48:10 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	int		i;

	i = 0;
	if (start > len)
		return (ft_strdup("\0"));
	p = (char *)malloc((int)ft_strlen((char*)s + start) + 1);
	while (len-- > 0 && s[i])
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
