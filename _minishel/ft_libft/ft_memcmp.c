/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 23:34:11 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/25 16:30:37 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (unsigned char *)s1 - 1;
	str2 = (unsigned char *)s2 - 1;
	while (n--)
	{
		if (*++str1 != *++str2)
			return (*str1 - *str2);
	}
	return (0);
}
