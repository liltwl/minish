/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:47:41 by otaouil           #+#    #+#             */
/*   Updated: 2021/09/27 19:11:02 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	fd = 0;
	while (s[i] != '\0')
		write(1, &s[i++], 1);
	return (i);
}

/*********************libft*******************************/
int		ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}
char	*ft_strdup(const char *src)
{
	char *res;

	if (!(res = (char *)malloc(strlen((char *)src) + 1)))
		return (0);
	ft_strcpy(res, (char *)src);
	return (res);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = -1;
	while (src[++i] != '\0')
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
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
 
char    **ft_free_split(char **d)
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

char	*ft_mystrjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = strlen((char *)s1);
	j = strlen((char *)s2);
	p = malloc(i + j + 2);
	if (!p)
		return (0);
	strcpy(p, (char *)s1);
	strcpy(&p[i], "/");
	strcpy(&p[i + 1], (char *)s2);
	return (p);
}

int	number_of_words(char *str, char c)
{
	int	nbr;
	int	i;
	int	indice;

	nbr = 0;
	i = 0;
	indice = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			if (indice != 1)
			{
				nbr++;
				indice = 1;
			}
		}
		else
			indice = 0;
		i++;
	}
	return (nbr);
}

int	word_size(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

void	fill_string(char *str, char *cas, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
	{
		cas[i] = str[i];
		i++;
	}
	cas[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		n;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tab = (char **)malloc((number_of_words((char *)s, c) + 1) * 8);
	n = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			if (n != 1)
			{
				tab[++j] = malloc(word_size((char *)&s[i], c) + 1);
				fill_string((char *)&s[i], tab[j], c);
				n = 1;
			}
		}
		else
			n = 0;
	}
	tab[++j] = 0;
	return (tab);
}

 /**********************env***lst*******************************/

t_env		*ft_lstfind(t_env *lst, char *name)
{
	while (lst)
	{
		if (!strncmp(name, lst->name, strlen(lst->name) + 1))
			return (lst);
		else
			lst = lst->next;
	}
	return (NULL);
}

t_env	*ft_lstnewenv(char *name, char *str)
{
	t_env	*elt;

	if (!(elt = (t_env *)malloc(sizeof(* elt))))
		return (NULL);
	elt->name = ft_strdup(name);
	elt->str = ft_strdup(str);
	elt->next = NULL;
	return (elt);
}

t_env	*ft_lastenv(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_addenv_back(t_env **alst, t_env *new)
{
	t_env	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lastenv(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

t_env	*ft_addevnlist(t_env **l, char **evn)
{
    char    **str;
    int     i;
    t_env  *tmp;

	i = 0;
    str	= ft_split(evn[i], '=');
	ft_addenv_back(l, ft_lstnewenv(str[0], str[1]));
    str = ft_free_split(str);
    tmp = *l;
	while (evn[++i])
	{
		str	= ft_split(evn[i], '=');
		ft_addenv_back(l, ft_lstnewenv(str[0], str[1]));
		str = ft_free_split(str);
	}
	return (tmp);
}
   /**************************lst**cmd****************************/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = strlen((char *)src);
	if (size == 0)
		return (k);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (k);
}



int checkbackslash(char **str, int j, int *d)
{
	int i;
	int	x;
	char *tmp;
	char  *tmp1;

	x = j;
	i = 0;
	tmp1 = *str;
	while (--j >= 0)
	{
		if (tmp1[j] == '\\')
			i++;
		else
			break ;
	}
	if (i > 0)
	{
		tmp = malloc(strlen(tmp1));
		j =  (i / 2) + !(!(i % 2)) * 1;
		ft_strlcpy(tmp, tmp1, x + 1 - j);
		ft_strcpy(&tmp[x - j], &tmp1[x]);
		printf("%s\n",tmp);
		free (tmp1);
		*str = tmp;
		*d = x - j;
		return (!(i % 2));
	}
	else
		return (1);

}

void    envcheck(char **d, t_env *l)
{
    char *tmp;
    int i;
	char *str;
	int		j;

    i = -1;
	str = "";
    while (d[++i])
	{
		j = -1;
		while (d[i][++j])
		{
			if (d[i][j] == '$' && checkbackslash(&d[i], j, &j))
			{
				if (ft_lstfind(l, &d[i][j + 1]))
				{
					str = ft_lstfind(l, &d[i][j + 1])->str;
					tmp = malloc(strlen(str) + j + 1);
				}
				else
					tmp = malloc(j + 1);
				ft_strlcpy(tmp, d[i], j +1);
				strcpy(&tmp[j], str);
				free (d[i]);
				j = strlen(str) + j + 1;
				tmp[j] = 0;
				d[i] = tmp;
				break ;
			}
		}
	}
}
t_cmd	*ft_findcmd(t_data *data, int id)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	tmp = data->cmd;
	while (tmp && ++i < data->numcmd)
	{
		if (i == id)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_cmd	*ft_lstnewcmd(char *str, int fd0, int fd1, t_data *l)
{
	t_cmd	*elt;
	int		i;

	i = 0;
	if (!(elt = (t_cmd *)malloc(sizeof(* elt))))
		return (NULL);
	ft_spaceskip(str, &i);
	elt->str = ft_split(&str[i], ' ');
	envcheck(elt->str, l->env);
	elt->fd0 = fd0;
	elt->fd1 = fd1;
	elt->next = NULL;
	return (elt);
}

t_cmd	*ft_lastcmd(t_cmd *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_addcmd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lastcmd(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

t_cmd	*ft_freelstcmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free (tmp);
	}
	return (NULL);
}

t_cmd	*ft_addcmdlist(t_cmd **l, char *evn, int *x, t_data *data)
{
    char    **str;
    int     i;
    t_cmd  *tmp;

	i = 0;
	if (*l)
		*l = ft_freelstcmd(*l);
	str	= ft_split(evn, '|');
	ft_addcmd_back(l, ft_lstnewcmd(str[i], 0, 1, data));
    tmp = *l;
	while (str[++i])
		ft_addcmd_back(l, ft_lstnewcmd(str[i], 0, 1, data));
	str = ft_free_split(str);
	*x = i;
	return (tmp);
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
	i = 1;
	j = 0;
	while(str[i])
	{
		write(1, str[i], strlen(str[i]));
		if (str[++i])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

//--------------------pwd--------------------------//

void    do_pwd(t_data *l)
{
    t_env  *tmp;

    if ((tmp = ft_lstfind(l->env, "PWD")))
        ft_putstr_fd(tmp->str, 1);
    write(1, "\n", 1);
}

//----------------------env-------------------------//



void    do_env(t_data *data)
{
	t_env	*l;

	l = data->env;
    while(l != NULL)
    {
        ft_putstr_fd(l->name, 1);
        write(1, "=", 1);
        ft_putstr_fd(l->str, 1);
        write(1, "\n", 1);
        l = l->next;
    }
}

//----------------------env-------------------------//

void	change_oldpwd(t_data *data)
{
	char	*str;
	t_env	*oldpwd;

	oldpwd = ft_lstfind(data->env, "OLDPWD");
	str = oldpwd->str;
	free (str);
	if (!(str = getcwd(NULL, 0)))
		return ;
	oldpwd->str = ft_strdup(str);
	free (str);
}

void	change_pwd(t_data *data)
{
	char	*str;
	t_env	*pwd;

	pwd = ft_lstfind(data->env, "PWD");
	str = pwd->str;
	free (str);
	if (!(str = getcwd(NULL, 0)))
		return ;
	pwd->str = ft_strdup(str);
	free (str);
}

void        ft_docdret(t_data *data)
{
    t_env			*lst;
	char			*src;

	lst = data->env;
	if ((lst = ft_lstfind(lst, "OLDPWD")))
	{
		src = ft_strdup(lst->str);
		change_oldpwd(data);
		chdir(src);
		free(src);
        change_pwd(data);
	}
}

void        ft_docdsing(t_data *data)
{
    t_env			*lst;
	char			*src;

	lst = data->env;
	if ((lst = ft_lstfind(lst, "HOME")))
	{
		src = ft_strdup(lst->str);
		change_oldpwd(data);
		chdir(src);
		free(src);
        change_pwd(data);
	}
}

void	ft_docd(t_data *data, t_cmd *cmd)
{
	char		**str;
	
	str = cmd->str;
	if (str[1] && !(ft_cmp("-", str[1])))
        ft_docdret(data);
	if (!str[1] || str[1][0] == '~')
        ft_docdsing(data);
	else if(str[1] && !str[2])
    {
        change_oldpwd(data);
        chdir(str[1]);
        change_pwd(data);
    }
}

   /*************************exec*******************************/

char	*ft_getabspath(char *path, char **tmp)
{
	int		i;
	char	*cmd;
	char	**p;
	int		fd;

	i = -1;
	cmd = NULL;
	p = ft_split(path, ':');
	while (p[++i])
	{
		cmd = ft_mystrjoin(p[i], tmp[0]);
		fd = open(cmd, O_RDONLY);
		if (fd > 0)
			break ;
		close(fd);
		free(cmd);
	}
	close(fd);
	return (cmd);
}


void	exec_cmd(char **cmd1, t_data *l)
{
	char	*pcmd;
	pid_t	pid;
	int		status;

	pcmd = ft_getabspath(ft_lstfind(l->env, "PATH")->str, cmd1);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0) 
    {
		waitpid(pid, &status, 0);
		l->exitstatu = WEXITSTATUS(status);
		printf("%d   --  %d\n", l->exitstatu, status);
		kill(pid, SIGTERM);
	} 
    else 
    {
		execve(pcmd, cmd1, NULL);
		perror("shell");
		exit(EXIT_FAILURE);
	}
}

void    ft_check(t_data *l, t_cmd *cmd)
{
    int i;
    char **str;

    i = 0;
	str = cmd->str;
    if(!strncmp(str[0], "help", 5))
        do_help();
    else if(!strncmp(str[0], "echo", 5))
        do_echo(l, cmd);
    else if(!strncmp(str[0],"exit", 5))
        exit(0);
    else if(!strncmp(str[0],"pwd", 4) && !str[1])
        do_pwd(l);
    else if(!strncmp(str[0],"env", 4) && !str[1])
        do_env(l);
    else if(!strncmp(str[0],"cd", 3))
        ft_docd(l, cmd);
    else
        exec_cmd(str, l);
}
/**********************pipe************************/

void	execdup(int	i, int *fds, int x, int fd)
{
	if (x != 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	if (i - 1 != x)
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
			execdup(data->numcmd, fds, i, fd);
			ft_check(data, ft_findcmd(data, i));
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

int main(int argc,char  **argv, char **env)
{
	t_data	data;
	char	*line;

	data.env = NULL;
	data.cmd = NULL;
	data.exitstatu = 0;
	data.env = ft_addevnlist(&data.env, env);
	while (1)
	{
		printf("%d",data.exitstatu);
		if (!(line = readline("yoo$> ")))
	    	return (1);
		if (line[0])
		{
			data.cmd = ft_addcmdlist(&data.cmd, line, &data.numcmd, &data);
			add_history(line);
			//printf("%s\n", line);
			/*if (data.numcmd == 1)
				ft_check(&data, data.cmd);
			else*/
			mlpipe(&data);
		}
		//data.cmd = data.cmd->next;
	}
}
