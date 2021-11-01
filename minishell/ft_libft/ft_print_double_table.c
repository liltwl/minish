/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fadi <ael-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:07:06 by ael-fadi          #+#    #+#             */
/*   Updated: 2021/04/25 16:31:32 by ael-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_double_pointer(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			ft_putendl_fd(str[i], 1);
			i++;
		}
	}
}
