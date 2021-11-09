/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 02:08:21 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/11/09 13:26:34 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*help;
	t_list	*str;

	str = *lst;
	while (str)
	{
		if (str->next)
			help = str->next;
		else
			help = NULL;
		del(str->content);
		free(str);
		str = help;
	}
	(*lst) = NULL;	
}
