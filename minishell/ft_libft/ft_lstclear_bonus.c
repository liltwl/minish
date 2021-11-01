/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 02:08:21 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/25 16:28:43 by ael-fadi         ###   ########.fr       */
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
