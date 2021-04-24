/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:28 by otaouil           #+#    #+#             */
/*   Updated: 2021/04/24 11:16:02 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------tools-----------------//

void    envcheck(char **d, t_list *l)
{
    char *tmp;
    t_list *t;
    int i;

    i = -1;
    while (d[++i])
        if (d[i][0] == '$')
        {
            if ((t = ft_lstfind(l, &d[i][1])))
            {
                tmp = d[i];
                d[i] = ft_strdup(t->str);
                free (tmp);
            }
        }
}

void	exec_cmd(char **cmd)
{
	pid_t	pid = 0;
	int		status = 0;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) {
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else {
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

t_list		*ft_lstfind(t_list *lst, char *name)
{
	while (lst)
	{
		if (!ft_cmp(name, lst->name))
			return (lst);
		else
			lst = lst->next;
	}
	return (NULL);
}

static void	my_int(int ret)
{
	ft_putstr("\n$> ");
	ret = 0;
}

char				**ft_free_split(char **d)
{
	int				i;

	i = 0;
	while (d[i])
	{
		free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

int		ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

t_list    *ft_addevnlist(t_list **l, char **evn)
{
    char    **str;
    int     i;
    t_list  **tmp;

	i = 0;
    str	= ft_split(evn[i], '=');
	ft_lstadd_back(l, ft_lstnew(str[0], str[1]));
    str = ft_free_split(str);
    tmp = l;
	while (evn[++i])
	{
		str	= ft_split(evn[i], '=');
		ft_lstadd_back(tmp, ft_lstnew(str[0], str[1]));
		str = ft_free_split(str);
	}
    return (*l);
}




//---------------------help-----------------------//

void	do_help(void)
{
	ft_putstr("Available commands:\n");
	ft_putstr("echo\ncd\npwd\nexport\nunset\nenv\nexit\n");
}

//---------------------------echo-------------------//
char    ft_getc(char *p)
{
    int     i;

    i = -1;
    while (p[++i] != 34 && p [i] != 39)
        if (!p[i])
            return 0;
    return (p[i]);
}

int    do_echoenv(char *p, t_list *l)
{
    t_list  *tmp;

    if (p[0] == '$')
	{
		if ((tmp = ft_lstfind(l, &p[1])))
			ft_putstr(tmp->str);
		return (1);
	}
	return (0);
}

void    do_echo(char **p, t_list *l)
{
    int     i;
    int     j;
   t_list  tmp;
    char    c;

    i = 1;
    c = 0;
    while (p[i] && !(j = 0))
    {
        if (!do_echoenv(p[i], l))
        {
			if (!c)
				c = ft_getc(p[i]);
			while (p[i][++j])
				if (p[i][j] != c)
					write(1, p[i] + j, 1);
		}
		if (p[++i])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
//--------------------pwd--------------------------//
void    do_pwd(char *p, t_list *l)
{
    t_list  *tmp;

    if ((tmp = ft_lstfind(l, "PWD")))
        ft_putstr(tmp->str);
    write(1, "\n", 1);
}
//----------------------env-------------------------//
void    do_env(t_list *l)
{
    while(l != NULL)
    {
        ft_putstr(l->name);
        write(1, "=", 1);
        ft_putstr(l->str);
        write(1, "\n", 1);
        l = l->next;
    }
}
 //-----------------------ls------------------------//

char     **ft_getdirs(int   *i)
{
    int     j;
    char **tmp;
    DIR *dir;
    struct dirent *dp;
    char    **buff;

    *i = 0;
    buff =  NULL;
    if((dir = opendir(".")) == NULL)
        exit(1);
    while ((dp = readdir(dir)) != NULL && (j = -1))
    {
        tmp = buff;
        buff = malloc(sizeof(buff) * ((*i) + 1));
        while(++j < (*i))
            buff[j] = tmp[j];
        buff[(*i)++] = ft_strdup((*dp).d_name);
        free (tmp);
    }
    return buff;
}

void        ft_dols()
{
    int     i;
    int     j;
    char    **buff;

    i = -1;
    buff = ft_getdirs(&j);
    printf("%d \n",j);
    while(++i < j)
    {
        ft_putstr(buff[i]);
        write(1, "\n", 1);
    }
}

//-----------------------cd-----------------------------//

void				change_oldpwd(t_list *all)
{
	char			*str;
	t_list			*lst;
	char			*pwd;

	if ((lst = ft_lstfind(all, "OLDPWD")))
	{
		str = lst->str;
		free(str);
	}
	if (!(pwd = getcwd(NULL, 0)))
		return ;
	lst->str = ft_strdup(pwd);
	free(pwd);
}

void				change_pwd(t_list *all)
{
	char			*str;
	t_list			*lst;
	char			*pwd;

	if ((lst = ft_lstfind(all, "PWD")))
	{
		str = lst->str;
		free(str);
	}
	if (!(pwd = getcwd(NULL, 0)))
		return ;
	lst->str = ft_strdup(pwd);
	free(pwd);
}

void        ft_docdret(t_list *l)
{
    t_list			*lst;
	char			*src;

	if ((lst = ft_lstfind(l, "OLDPWD")))
	{
		src = ft_strdup(lst->str);
		change_oldpwd(l);
		chdir(src);
		free(src);
        change_pwd(l);
	}
}

void        ft_docd(t_list *l, char **p)
{
    //if (p)
    if (p[1] && !(ft_cmp("-", p[1])))
        ft_docdret(l);
    /*else if(p[1][0] == '~')
        ft_docdsing(p[1], l);*/
    else if(p[1])
    {
        change_oldpwd(l);
        chdir(p[1]);
        change_pwd(l);
    }
}
//------------------------------------------------------//
void    ft_check(char *p, t_list *l)
{
    int i;
    char **str;

    i = 0;
    ft_spaceskip(p, &i);
    str = ft_split(&p[i], ' ');
    if(!ft_cmp(str[0], "help"))
        do_help();
    else if(!ft_cmp(str[0],"echo"))
        do_echo(str, l);
    else if(!ft_cmp(str[0],"exit"))
        exit(0);
    else if(!ft_cmp(str[0],"pwd"))
        do_pwd(str[1], l);
    else if(!ft_cmp(str[0],"env"))
        do_env(l);
    /*else if(!ft_cmp(str[0],"ls"))
        ft_dols();*/
    else if(!ft_cmp(str[0],"cd"))
        ft_docd(l, str);
    else
        exec_cmd(str);
}

int     main(int argc,char  **argv, char **env)
{
    int i;
    char    **p;
    char    *gh;
    t_list  *l;
	t_list  *tmp;

    i = -1;
    //getcwd(p, 100);
    //ft_getdir(&gh);
    //printf(" %s   \n",gh);
	l = NULL; 
    i = -1;
    l = ft_addevnlist(&l, env);
    //ft_putstr(fclear);
    while ((i = -1))
    {
        tmp = ft_lstfind(l, "PWD");
        printf(" %s  ",tmp->str);
        signal(SIGINT, my_int);
        if (!(gh = readline("$> ")))
	    	return (1);
        add_history(gh);
        p = ft_split(gh, ';');
        envcheck(p,l);
        while (p[++i])
            ft_check(p[i], l);
        ft_free_split(p);
    }
}