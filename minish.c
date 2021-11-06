/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:47:41 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/04 19:45:15 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		ft_putstr_fd("yoo$> ", 2);
	}
}

void	ft_error(char *p, int i)
{
	ft_putstr_fd(p, 1);
	exit (i);
}


int		ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int	ft_cmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

 /**********************split*******************************/

int		ft_splitlen(char **p)
{
	int i;

	i = 0;
	while (p[i])
		i++;
	return (i);
}
 
char    **ft_free_split(char **d)
{
	int				i;

	i = 0;
	if (d == NULL)
		return (NULL);
	while (d[i])
	{
		if (d[i])
			free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

char    **ft_print_split(char **d)
{
	int				i;

	i = 0;
	if (d == NULL)
		return (NULL);
	while (d[i])
	{
		printf("\n**%s**\n", d[i]);
		i++;
	}
	return (NULL);
}



 /**********************env***lst*******************************/

t_env		*ft_lstfind(t_list *lst, char *name)
{
	t_env *env;

	while (lst)
	{
		env = (t_env *)lst->content;
		if (!strncmp(name, env->name, strlen(env->name) + 1))
			return (env);
		else
			lst = lst->next;
	}
	return (NULL);
}

t_cmd	*ft_findcmd(t_list *data, int id)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	while (tmp && ++i < g_data->numcmd)
	{
		tmp = data->content;
		if (i == id)
			return (tmp);
		data = data->next;
	}
	return (NULL);
}


//---------------------help-----------------------//

void	do_help(void)
{
	ft_putstr_fd("Available commands:\n", 1);
	ft_putstr_fd("echo\ncd\npwd\nexport\nunset\nenv\nexit\n", 1);
}

//---------------------------echo-------------------//

void	do_echo(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**str;

	str = cmd->str;
	i = 0;
	j = 0;
	while (!ft_strncmp(str[++i], "-n", 3))
		j = 1;
	while(str[i])
	{
		write(cmd->out, str[i], strlen(str[i]));
		if (str[++i])
			write(cmd->out, " ", 1);
	}
	if (j == 0)
		write(cmd->out, "\n", 1);
	data->exitstatu = 0;
}

//--------------------pwd--------------------------//

void    do_pwd(t_data *l, t_cmd *cmd)
{
    t_env  *tmp;
	char	*str;

	str = getcwd(NULL, 0);
	if (cmd->str[1])
		l->exitstatu = 1;
	else
	{
		ft_putstr_fd(str, cmd->out);
		write(cmd->out, "\n", 1);
	}
	l->exitstatu = 0;
}

//----------------------env-------------------------//



void    do_env(t_data *data, t_cmd *cmd)
{
	t_list	*l;
	t_env	*env;

	l = data->env;
	if (cmd->str[1])
	{
		data->exitstatu = 127;
		return ;
	}
    while(l != NULL)
    {
		env = l->content;
        ft_putstr_fd(env->name, cmd->out);
        write(cmd->out, "=", 1);
        ft_putstr_fd(env->content, cmd->out);
        write(cmd->out, "\n", 1);
        l = l->next;
    }
	data->exitstatu = 0;
}

//----------------------CD-------------------------//

void	change_oldpwd(t_data *data)
{
	char	*str;
	t_env	*oldpwd;

	oldpwd = ft_lstfind(data->env, "OLDPWD");
	str = oldpwd->content;
	if (!(str = getcwd(NULL, 0)))
		return ;
	oldpwd->content = ft_strdup(str);
	free (str);
}

void	change_pwd(t_data *data)
{
	char	*str;
	t_env	*pwd;

	pwd = ft_lstfind(data->env, "PWD");
	str = pwd->content;
	free (str);
	if (!(str = getcwd(NULL, 0)))
		return ;
	pwd->content = ft_strdup(str);
	free (str);
}

void        ft_docdret(t_data *data)
{
    t_env			*lst;
	char			*src;

	if ((lst = ft_lstfind(data->env, "OLDPWD")))
	{
		src = ft_strdup(lst->content);
		change_oldpwd(data);
		chdir(src);
		free(src);
        change_pwd(data);
		data->exitstatu = 0;
	}
	else
		data->exitstatu = 1;
}

void        ft_docdsing(t_data *data)
{
    t_env			*lst;
	char			*src;

	if ((lst = ft_lstfind(data->env, "HOME")))
	{
		src = ft_strdup(lst->content);
		change_oldpwd(data);
		chdir(src);
		free(src);
        change_pwd(data);
		data->exitstatu = 0;
	}
	else
		data->exitstatu = 1;
}

void	ft_docd(t_data *data, t_cmd *cmd)
{
	char		**str;
	
	str = cmd->str;
	if (str[1] && !(ft_cmp("-", str[1])))
        ft_docdret(data);
	else if (!str[1] || str[1][0] == '~')
        ft_docdsing(data);
	else if(str[1] && !str[2])
    {
        change_oldpwd(data);
        if (chdir(str[1]) <= 0)
        {
			data->exitstatu = 1;
        	return ;
        }
        change_pwd(data);
		data->exitstatu = 0;
    }
}

//----------------------export-------------------------//

t_env	*ft_smllst(t_list *env)
{
	char	*str;
	t_env	*tmp;

	tmp = (t_env *)env->content;
	str = tmp->name;
	env = env->next;
	while (env && tmp->name)
	{
		tmp = (t_env *)env->content;
		if (ft_memcmp(str, tmp->name, strlen(str) + 1) < 0)
			str = tmp->name;
		env = env->next;
	}
	tmp = ft_lstfind(env, str);
	return (tmp);
}

t_env	*ft_getbiglst(t_list *tmp1, t_env *big)
{
	t_env	*tmp;
	char	*c;
	char	*p;
	t_env	*env;

	p = NULL;
	if (big)
		p = strdup(big->name);
	c = strdup("~~~~~~~~");
	while (tmp1)
	{
		env = (t_env *)tmp1->content;
		if ((ft_memcmp(c, env->name, strlen(c) + 1) > 0 && !p)||
			((p && ft_memcmp(p, env->name, strlen(env->name) + 1) < 0)
			&& ft_memcmp(c, env->name, strlen(env->name) + 1) > 0))
		{
			tmp = env;
			free (c);
			c = strdup(env->name);
		}
		tmp1 = tmp1->next;
	}
	free (c);
	free (p);
	return (tmp);
}

void	ft_printsortlst(t_data	*data, t_cmd *cmd)
{
	int		i;
	t_env	*tmp;

	tmp = NULL;
	i = 0;
	while (i < ft_lstsize(data->env))
	{
		i++;
		tmp = ft_getbiglst(data->env, tmp);
		write(cmd->out, "declare -x ", 11);
		write(cmd->out, tmp->name, strlen(tmp->name));
		if (tmp->content[0])
		{
			write(cmd->out, "=\"", 2);
			write(cmd->out, tmp->content, strlen(tmp->content));
			write(cmd->out, "\"", 1);
		}
		write(cmd->out, "\n", 1);
	}
}

int	ft_findc(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

t_env	*ft_lstnewenv(char *name, char *str)
{
	t_env	*elt;

	if (!(elt = (t_env *)malloc(sizeof(* elt))))
		return (NULL);
	elt->name = ft_strdup(name);
	elt->content = ft_strdup(str);
	return (elt);
}

void	addnewenv(char	**p, t_data *data)
{
	t_env	*env;
	t_env	*tmp;

	env = ft_lstfind(data->env, p[0]);
	if (env)
	{
		free (env->content);
		if (p[1])
			env->content = strdup(p[1]);
		else
			env->content = strdup("");
	}
	else
	{
		if (p[1])
			env = ft_lstnewenv(p[0], p[1]);
		else
			env = ft_lstnewenv(p[0], "");
		tmp = ft_lstlast(data->env)->content;  // hadi waaa9ila makaynach
		ft_lstadd_back(&data->env, ft_lstnew((void *)env));
	}
}

char	**mycatstr(char *str, int i)
{
	char	**p;
	char	*tmp;

	p = malloc(sizeof(char **) * 3);
	if (i)
	{
		tmp = malloc(i + 2);
		if (str[i - 1] == '+')
			ft_strlcpy(tmp, str, i);
		else
			ft_strlcpy(tmp, str, i + 1);
		p[0] = tmp;
		tmp = malloc(strlen(&str[i] + 2) + 2);
		ft_strlcpy(tmp, &str[i + 1], strlen(&str[i]));
		p[1] = tmp;
		p[2] = NULL;
	}
	else
	{
		p[0] = ft_strdup(str);
		p[1] = NULL;
	}
	return (p);
}

void	export_join(t_data *data, char **p)
{
	char	*str;
	char	*tmp;
	t_env	*env;

	env = ft_lstfind(data->env, p[0]);
	if (env)
	{
		if (p[1])
			str = strdup(p[1]);
		else
			str = strdup("");
		tmp = ft_strjoin(env->content, str);
		free (env->content);
		free (str);
		env->content = tmp;
	}
	else
		addnewenv(p, data);
}

void	ft_lstupdate(t_data *data, char **str,int j)
{
	int		i;
	char	**p;

	i = 0;
	data->exitstatu = 1;
	while (str[++i])
	{
		j = ft_findc(str[i], '=');
		p = mycatstr(str[i], j);
		if (!ft_isalpha(str[i][0]) && str[i][0] != '_')
			data->exitstatu = 1;
		else if (j)
		{
			if (ft_strchr(p[0], '+'))
				return ;
			if (str[i][j - 1] == '+')
				export_join(data, p);
			else
				addnewenv(p, data);
		}
		else
			addnewenv(p, data);
		ft_free_split(p);
	}
	data->exitstatu = 0;
}

void	do_export(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**str;

	str = cmd->str;
	i = 0;
	if (!str[1])
		ft_printsortlst(data, cmd);
	else
		ft_lstupdate(data, str, 0);
}

 /*************************unset*******************************/

void	ft_deletlst(char *name, t_list *env)
{
	t_env	*lst;
	t_list	*tmplst;

	tmplst = NULL;
	while ((env))
	{
		lst = (env)->content;
		if (!strncmp(name, lst->name, strlen(lst->name) + 1))
			break ;
		tmplst = (env);
		(env) = (env)->next;
	}
	if (!(env))
		return ;
	if (tmplst)
		tmplst->next = (env)->next;
	else
		g_data->env = (env)->next;
	free (lst->content);
	free (lst->name);
	free (lst);
	free ((env));
}


 void	do_unset(t_data *data, t_cmd *cmd)
 {
	int		i;
	char	**str;

	i = 0;
	str = cmd->str;
	if (!str[1])
		return ;
	while (str[++i])
		ft_deletlst(str[i], data->env);
	data->exitstatu = 0;
 }
   /*************************exit*******************************/

int	ft_myatoi(char *str)
{
	unsigned long long	m;
	int					i;
	int					n;

	m = 0;
	n = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		n = -1;
		if (str[++i] == '-')
			ft_error("", 255);
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		m = (m * 10) + (str[i++] - 48);
		if ((m > 9223372036854775807 && n > 0) ||
		    (m - 1 > 9223372036854775807 && n < 0))
			ft_error("", 255);
	}
	if (str[i] && !(str[i] >= '0' && str[i] <= '9'))
		ft_error("", 255);
	return (m * n);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	char	i;
	char	**p;

	i = data->exitstatu;
	if (cmd == NULL)
		exit (i);
	p = cmd->str;
	if (p[1] && p[2])
	{
		data->exitstatu = 1;
		ft_putstr_fd("", cmd->out);
		return ;
	}
	else if (p[1]) 
		i = (char)ft_myatoi(p[1]);
	exit (i);
}

   /*************************exec*******************************/

void	exec_cmd(char **cmd1, t_data *l, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0) 
    {
		waitpid(pid, &status, 0);
		l->exitstatu = WEXITSTATUS(status);
		kill(pid, SIGTERM);
	} 
    else 
    {
		if (l->numcmd == 1)
        {
			dup2(cmd->in, 0);
			dup2(cmd->out, 1);
        }
        execve(cmd->cmd, cmd1, NULL);
		ft_putstr_fd("yoo: command not found\n", 2);
		exit(127);
	}
}



void    ft_check(t_data *l, t_cmd *cmd)
{
    char *str;
	
	if (!cmd->cmd || !cmd->str)
		return ;
    else if(!strncmp(cmd->str[0], "help", 5))
        do_help();
    else if(!strncmp(cmd->str[0], "echo", 5))
        do_echo(l, cmd);
    else if(!strncmp(cmd->str[0],"exit", 5))
        ft_exit(cmd, l);
    else if(!strncmp(cmd->str[0],"pwd", 4))
        do_pwd(l, cmd);
    else if(!strncmp(cmd->str[0],"env", 4))
        do_env(l, cmd);
    else if(!strncmp(cmd->str[0],"cd", 3))
        ft_docd(l, cmd);
	else if(!strncmp(cmd->str[0],"export", 7))
        do_export(l, cmd);
	else if(!strncmp(cmd->str[0],"unset", 6))
        do_unset(l, cmd);
    else
        exec_cmd(cmd->str, l, cmd);
}

/**********************pipe************************/

void	execdup(t_data *data, int *fds, int x, int fd)
{
	t_cmd *cmd;
    t_list *tmp;
    int     i;

    i = -1;
    tmp = data->cmd_list;
	while (++i < x)
		tmp = tmp->next;
	cmd = tmp->content;
	if (x != 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	if (data->numcmd - 1 != x)
		dup2(fds[1], 1);
	close(fds[0]);
}

void	mlpipe(t_data *data)
{
	int		fds[2];
	pid_t	pid;
	int		i;
	int		fd;

	i = -1;
	while (++i < data->numcmd )
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
			printf("error : fork failed");
		else if (pid == 0)
		{
			execdup(data, fds, i, fd);
			ft_check(data, ft_findcmd(data->cmd_list, i));
			exit(data->exitstatu);
		}
		else
		{
			waitpid(pid, &data->exitstatu, 0);
			data->exitstatu = WEXITSTATUS(data->exitstatu);
			close(fds[1]);
			fd = fds[0];
		}
	}
}

/*int main(int argc,char  **argv, char **env)
{
	t_data	data;
	char	*line;
	char	**p;
	int		i;

	p = NULL;
	data.env = NULL;
	data.cmd = NULL;   //hanya kayna dik init
	data.exitstatu = 0;
	data.env = ft_addevnlist(&data.env, env);
	while (1)
	{
		signal(SIGINT, my_int);
		i = 0;
		if (!(line = readline("yoo$>")))
	    	return (1);
		add_history(line);
		p = ft_split(line, ';');
		while (p[i])
		{
			if (p[i][0])
			{
				data.cmd = ft_addcmdlist(&data.cmd, p[i], &data.numcmd, &data);
				if (data.numcmd == 1)
					ft_check(&data, data.cmd);
				else if (data.numcmd < 557)
					mlpipe(&data);
				ft_free_cmd(&data);
			}
			i++;
		}
		if (!p[0])
			data.exitstatu = 0;
		ft_free_split(p);
		free (line);
	}
	return 0;
}
*/

int		main(int argc, char **argv, char **env)
{
	char **p;

	g_data = malloc(sizeof(t_data));
	init_env_list(env);
	argc = 0;
	argv = NULL;
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		g_data->tokkens = NULL;
		g_data->cmd_list = NULL;
		signal(SIGINT, sig_handler);
		if (!(g_data->line = readline("ader🤡$>")))
	    	return (1);
		if (g_data->line[0])
		{
			parser();
			if (g_data->numcmd == 1)
				ft_check(g_data, g_data->cmd_list->content);
			else if (g_data->numcmd < 557)
				mlpipe(g_data);
			add_history(g_data->line);
			//free_nodes_cmd(g_data->cmd_list);
			//free_functio();
		}
	}
	return (0);
}