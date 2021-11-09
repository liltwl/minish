#include "../minishell.h"

t_list	*get_args(t_list **args, t_type *types, t_cmd **cmd)
{
	t_type	*tmp;
	t_list	*list_files;

	tmp = types;
	list_files = NULL;
	while (tmp)
	{
		if (is_redirection(tmp->type) && tmp->next
			&& !is_redirection(tmp->next->type))
			ft_lstadd_back(&list_files, ft_lstnew(tmp->next->word));
		if (!is_redirection(tmp->type))
		{
			if (tmp->prev != NULL)
			{
				if (!is_redirection(tmp->prev->type))
					help_args(&tmp, args);
			}
			else
				ft_lstadd_back(args, ft_lstnew(tmp->word));
		}
		tmp = tmp->next;
	}
	(*cmd)->str = ll_to_dp(*args);
	return (list_files);
}

int	ft_heredoc(char *str)
{
	int		fd[2];
	char	*line;
	int		x;

	x = 1;
	pipe(fd);
	while (x)
	{
		line = readline("");
		x = strcmp(line, str);
		if (!x)
			break ;
		else
			write(fd[1], line, strlen(line));
		free(line);
		write(fd[1], "\n", 1);
	}
	if (line)
		free(line);
	close(fd[1]);
	return (fd[0]);
}

void	get_in(int *i, t_list *list_files, t_type *expanded_types)
{
	char	*s;

	*i = 0;
	s = NULL;
	if (list_files)
	{
		expanded_types = expanded_types->next;
		while (expanded_types)
		{
			if (expanded_types->prev->type == 5
				&& (is_redirection(expanded_types->type) == 0))
			{
				s = expanded_types->word;
				*i = ft_heredoc(expanded_types->word);
			}
			else if (expanded_types->prev->type == 6
				&& (is_redirection(expanded_types->type) == 0))
			{
				s = expanded_types->word;
				*i = open(expanded_types->word, O_RDONLY);
			}	
			expanded_types = expanded_types->next;
		}
	}
}

void	get_command(t_type *tmp2, char *str,
	t_cmd **cmd, t_type **expanded_types)
{
	if (!tmp2)
		return ;
	if (is_redirection(tmp2->type))
	{
		if (ft_lstsize_type(tmp2) == 2)
			(*cmd)->cmd = ft_strdup("");
		else if (ft_lstsize_type(tmp2) == 3)
		{
			str = get_node(tmp2)->word;
			(*cmd)->cmd = get_cmd_path(str, g_data->env);
		}
		else
		{
			while (is_redirection(tmp2->type))
				tmp2 = tmp2->next->next;
			(*cmd)->cmd = get_cmd_path(tmp2->word, g_data->env);
		}
	}
	else if (tmp2->type == 0)
		(*cmd)->cmd = get_cmd_path((*expanded_types)->word, g_data->env);
}

int	main(int argc, char **argv, char **env)
{
	init_env_list(env);
	argc = 0;
	argv = NULL;
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		init_data();
		signal(SIGINT, sig_handler);
		g_data->line = readline("omareda🤡$>");
		if (!(g_data->line))
			return (1);
		if (g_data->line[0])
		{
			parser();
			if (g_data->numcmd == 1 && g_data->cmd_list)
				ft_check(g_data, g_data->cmd_list->content);
			else if (g_data->numcmd < 557
				&& g_data->numcmd > 0 && g_data->cmd_list)
				mlpipe(g_data);
			//add_history(g_data->line);
		}
		clear();
	}
	ft_lstclear(&g_data->env, &free_env);
	return (0);
}
