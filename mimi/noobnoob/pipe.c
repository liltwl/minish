/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:44:48 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/05 17:00:48 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_check(t_data *l, t_cmd *cmd)
{
	char	*str;

	if (!cmd->cmd || !cmd->str)
		return ;
	else if (!strncmp(cmd->str[0], "help", 5))
		do_help();
	else if (!strncmp(cmd->str[0], "echo", 5))
		do_echo(l, cmd);
	else if (!strncmp(cmd->str[0], "exit", 5))
		ft_exit(cmd, l);
	else if (!strncmp(cmd->str[0], "pwd", 4))
		do_pwd(l, cmd);
	else if (!strncmp(cmd->str[0], "env", 4))
		do_env(l, cmd);
	else if (!strncmp(cmd->str[0], "cd", 3))
		ft_docd(l, cmd);
	else if (!strncmp(cmd->str[0], "export", 7))
		do_export(l, cmd);
	else if (!strncmp(cmd->str[0], "unset", 6))
		do_unset(l, cmd);
	else
		exec_cmd(cmd->str, l, cmd);
}

void	execdup(t_data *data, int *fds, int x, int fd)
{
	t_cmd	*cmd;
	t_list	*tmp;
	int		i;

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

void	ft_exitstatu(int *fd, int *fds, t_data *data, pid_t pid)
{
	wait(NULL);
	close(fds[1]);
	*fd = fds[0];
}

void	mlpipe(t_data *data)
{
	int		fds[g_data->numcmd * 2];
	pid_t	pid;
	int		x;
	int		s;
	int		j;

	for( x = 0; x < g_data->numcmd; x++ )
	{
    	if( pipe(fds + x*2) < 0 )
		{
        	perror("pipe");
    	}
	}
	j = 0;
	x = -1;
	while( ++x < g_data->numcmd )
	{
		pid = fork();
		if( pid == 0 )
		{
			printf("%d -- %d\n",j - 2, j + 1);
			if( x != 0 )
			{
				if( dup2(fds[j - 2], 0) < 0 )
				{
					perror("dup");
				}
			}
			if( g_data->numcmd - 1 != x)
			{
				if( dup2(fds[j + 1], 1) < 0 )
				{
					perror("dup");
				}
			}
			for( s = 0; s < 2 * g_data->numcmd; s++ )
			{
				close( fds[s] );
			}
			
			ft_check(data, ft_findcmd(data->cmd_list, x));
			exit(0);
		}
		else if( pid < 0 )
		{
			perror("fork");
		}
		j += 2;
	}

/* parent closes all of its copies at the end */
for( x = 0; x < 2 * g_data->numcmd; x++ ){
    close( fds[x] );
}
}

void	mlpcipe(t_data *data)
{
	int		fds[2];
	pid_t	pid;
	int		i;
	int		fd;

	i = -1;
	while (++i < data->numcmd)
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("error : fork failed\n", 2);
		else if (pid == 0)
		{
			execdup(data, fds, i, fd);
			ft_check(data, ft_findcmd(data->cmd_list, i));
			exit(data->exitstatu);
		}
		else
			ft_exitstatu(&fd, fds, data, pid);
	}
	waitpid(pid, &data->exitstatu, 0);
	data->exitstatu = WEXITSTATUS(data->exitstatu);
}
