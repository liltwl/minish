/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 23:18:57 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/28 14:39:45 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		j;
	int		i;
	char	*tab;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	tab = (char *)malloc((i + j) * sizeof(char) + 1);
	i = -1;
	while (s1[++i] != '\0')
		tab[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
	{
		tab[i] = s2[j];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
