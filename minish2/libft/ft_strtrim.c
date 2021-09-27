/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:33:12 by otaouil           #+#    #+#             */
/*   Updated: 2019/10/13 19:31:41 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_find(char c, char *s)
{
	int		i;

	i = -1;
	while (s[++i] != '\0')
		if (s[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[i] && ft_find(s1[i], (char *)set))
		i++;
	j = ft_strlen((char *)s1);
	while (s1[i] && ft_find(s1[j - 1], (char *)set))
		j--;
	return (ft_substr(s1, i, j - i));
}
