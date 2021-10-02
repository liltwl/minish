/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:38:46 by otaouil           #+#    #+#             */
/*   Updated: 2021/10/02 07:37:45 by otaouil          ###   ########.fr       */
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
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "libft/libft.h"

#define fclear "\033[?1049h\033[H"


char				**ft_free_split(char **d);

typedef struct s_cmd
{
	char			**str;
	int				fd0;
	int				fd1;
	struct s_cmd	*next;
}               t_cmd;

typedef struct s_env
{
	char			*name;
	char			*str;
	struct s_env	*next;
}               t_env;

typedef struct s_data
{
	t_env		*env;
	t_cmd		*cmd;
	int			numcmd;
	int			exitstatu;
}               t_data;

#endif