/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 02:48:21 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/13 15:37:31 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char *res;

	if (!(res = (char *)malloc(ft_strlen((char *)src) + 1)))
		return (0);
	ft_strcpy(res, (char *)src);
	return (res);
}
