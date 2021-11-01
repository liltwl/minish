/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:10:02 by mamali            #+#    #+#             */
/*   Updated: 2021/10/26 20:18:19 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    syntax_error()
{
    char    *str;
    int     i;

    str = g_data->line;
    i = 0;
    if (str[i] == '|')
        log_error("syntax_error\n");
}