/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:30:43 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/28 14:50:34 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		k;
	int		i;
	int		j;
	char	*tab;

	if (!s)
		return (NULL);
	if (s[0] == '\0' || start > ft_strlen(s))
	{
		tab = malloc(1 * sizeof(char));
		tab[0] = '\0';
		return (tab);
	}
	i = 0;
	j = len + start;
	k = start;
	tab = (char *)malloc((len + 1) * sizeof(char));
	while (s[start] != '\0' && k++ < j)
		tab[i++] = s[start++];
	tab[i] = '\0';
	return (tab);
}
