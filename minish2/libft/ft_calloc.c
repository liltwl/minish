/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:16:17 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/13 15:43:34 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void *p;

	if (!(p = malloc((nelem * elsize))))
		return (NULL);
	if (p == 0)
		return (p);
	ft_bzero(p, nelem * elsize);
	return (p);
}
