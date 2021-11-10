/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:44:48 by otaouil           #+#    #+#             */
/*   Updated: 2021/11/11 00:03:15 by mamali           ###   ########.fr       */
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
	}
	else
	{
		dup2(cmd->in, 0);
		dup2(cmd->out, 1);
		execve(cmd->cmd, cmd1, NULL);
		ft_putstr_fd("yoo: command not found\n", 2);
		exit(127);
	}
}

void	ft_check(t_data *l, t_cmd *cmd)
{
	g_data->sigpid = 1;
	if (l->numcmd == 0 || cmd == NULL)
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
	if (x != 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	if (data->numcmd - 1 != x)
		dup2(fds[1], 1);
	close(fds[1]);
	close(fds[0]);
}

void	ft_exitstatu(int *fd, int *fds, pid_t pid)
{
	if (pid == -1)
		ft_putstr_fd("error : fork failed\n", 2);
	else
	{
		if (*fd)
			close(*fd);
		close(fds[1]);
		*fd = fds[0];
	}
}

void	mlpipe(t_data *data)
{
	int		fds[2];
	pid_t	*pid;
	int		i;
	int		fd;

	i = -1;
	pid = malloc(sizeof(pid_t *) * (g_data->numcmd + 1));
	while (++i < data->numcmd)
	{
		pipe(fds);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			execdup(data, fds, i, fd);
			ft_check(data, ft_findcmd(data->cmd_list, i));
			exit(data->exitstatu);
		}
		ft_exitstatu(&fd, fds, pid[i]);
	}
	close (fd);
	i = -1;
	while (++i < data->numcmd)
		waitpid(pid[i], &data->exitstatu, 0);
	data->exitstatu = WEXITSTATUS(data->exitstatu);
	free (pid);
}
