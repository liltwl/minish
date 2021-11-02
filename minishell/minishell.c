#include "minishell.h"

t_list	*get_args(t_list **args ,t_type	*types, t_cmd **cmd)
{
	t_type	*tmp;
	t_list	*list_files;
	int		i;

	tmp = types;
	i = 0;
	list_files = NULL;
	while (tmp)
	{
		if (tmp->type == 4 || tmp->type == 3 || tmp->type == 5 || tmp->type == 6)
			ft_lstadd_back(&list_files, ft_lstnew(tmp->next->word));
		if (tmp->type != 4 && tmp->type != 3 && tmp->type != 5 && tmp->type != 6)
		{
			if (tmp->prev != NULL)
			{
				if (tmp->prev->type != 4 && tmp->prev->type != 3 && tmp->prev->type != 5 && tmp->prev->type != 6)
					help_args(&tmp, args);
			}
			else
				ft_lstadd_back(args, ft_lstnew(tmp->word));
		}
		tmp = tmp->next;
	}
	(*cmd)->str = ll_to_dp(*args);
	//while ((*cmd)->str[i])
		//printf(">>>>>%s\n", (*cmd)->str[i++]);
	// t_list *list = *args;
	// while (list)
	// {
	// 	printf("tt = %s\n", (char *)(list)->content);
	// 	list = (list)->next;
	// }
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
	*i = 0;
	char	*s;
	if (list_files)
	{
		expanded_types = expanded_types->next;
		while (expanded_types)
		{
			// printf("file_out is = %s %d\n", expanded_types->word, expanded_types->type);
			if (expanded_types->prev->type == 5)
			{
				s = expanded_types->word;
				//printf("file_in %s\n", expanded_types->word);
				*i = ft_heredoc(expanded_types->word);
			}
			else if (expanded_types->prev->type == 6)
			{
				s = expanded_types->word;
				//printf("%s\n", expanded_types->word);
				*i = open(expanded_types->word, O_RDONLY);
			}	
			expanded_types = expanded_types->next;
		}
		//printf("file_in is = %s\n", s);
	}
}

void	get_out(int *i, t_list *list_files, t_type *expanded_types)
{
	char	*s;

	*i = 1;
	if (list_files)
	{
		expanded_types = expanded_types->next;
		while (expanded_types)
		{
		//s = ft_lstlast(list_files)->content;
		//while (strcmp(expanded_types->word, s) != 0)
			s = expanded_types->word;
			if (expanded_types->prev->type == 4)
				*i = open(s, O_WRONLY | O_CREAT | O_TRUNC , 0777);  ///hadi asat ra kant khasra mhm ra 9aditha
			else if (expanded_types->prev->type == 3)
				*i = open(s, O_WRONLY | O_CREAT | O_APPEND , 0777);
			expanded_types = expanded_types->next;
		}
		/*while (list_files)
		{
			printf("file_out is = %s\n", list_files->content);
			if (ft_strncmp(s, list_files->content, strlen(s) + 1) != 0)
				open(list_files->content, O_WRONLY | O_CREAT | O_TRUNC , 0777);
			list_files = list_files->next;
		}*/
	}
}
// > file echo sdsd > file2
// echo "$PATH"dfgd
void	get_command(t_type *tmp2, char *str, t_cmd **cmd, t_type **expanded_types)
{
	t_type	*tmp;

	tmp = tmp2;
	if (tmp2->type == 4 || tmp2->type == 3 || tmp2->type == 5 || tmp2->type == 6)
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
			while(tmp->type == 4 || tmp->type == 3 || tmp2->type == 5 || tmp2->type == 6)
				tmp = tmp->next->next;
			(*cmd)->cmd = get_cmd_path(tmp->word, g_data->env);
		}
	}
	else if (tmp2->type == 0)
		(*cmd)->cmd = get_cmd_path((*expanded_types)->word, g_data->env);
}

void	expand_cmdlist(t_list *tmp, char *str)
{
	t_cmd	*cmd;
	t_type	*expanded_types;
	int		i;
	t_list	*list_files;
	t_type	*tmp2;

	i = 0;
	while (tmp)
	{
		i++;
		tmp2 = tmp->content;
		// printf("ici = %s|\n", tmp2->word);
		expanded_types = expander(tmp->content);
		//print_types(expanded_types);
		cmd = malloc(sizeof(t_cmd));
		get_command(tmp2, str, &cmd, &expanded_types);
		cmd->args_list = NULL;
		list_files = get_args(&(cmd->args_list), expanded_types, &cmd);
		get_out(&(cmd->out), list_files, expanded_types);
		get_in(&(cmd->in), list_files, expanded_types);
		ft_lstadd_back(&g_data->cmd_list, ft_lstnew(cmd));
		tmp = tmp->next;
		//printf("--------------------\n");
	}
	g_data->numcmd = i;
}

/*int		main(int argc, char **argv, char **env)
{
	g_data = malloc(sizeof(t_data));
	init_env_list(env);
	argc = 0;
	argv = NULL;
	while (1)
	{
		g_data->tokkens = NULL;
		g_data->cmd_list = NULL;
		if (!(g_data->line = readline("ader🤡$>")))
	    	return (1);
		parser();
		print_cmd();
		// excute_cmd();
		print_tokkens();
		add_history(g_data->line);
		//free_functio();
		// check_words(tmp);
	}
	return (0);
}*/

