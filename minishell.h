/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:38:46 by otaouil           #+#    #+#             */
/*   Updated: 2021/04/09 15:40:16 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <libgen.h>
#include <curses.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

#define fclear "\033[?1049h\033[H"

#endif