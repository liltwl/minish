#include "minishell.h"
// dans cette fonction je retourne une liste des fichier et je remplis args_list avec les arguments
t_list	*get_args(t_list **args ,t_type	*types, t_cmd **cmd)
{
	t_type	*tmp;
	t_list	*list_files;

	tmp = types;
	list_files = NULL;
	while (tmp)
	{
		if (is_redirection(tmp->type) && tmp->next && !is_redirection(tmp->next->type))
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
	*i = 0;
	char	*s;

	s = NULL;
	if (list_files)
	{
		expanded_types = expanded_types->next;
		while (expanded_types)
		{
			if (expanded_types->prev->type == 5 && (is_redirection(expanded_types->type) == 0))
			{
				s = expanded_types->word;
				*i = ft_heredoc(expanded_types->word);
			}
			else if (expanded_types->prev->type == 6 && (is_redirection(expanded_types->type) == 0))
			{
				s = expanded_types->word;
				*i = open(expanded_types->word, O_RDONLY);
			}	
			expanded_types = expanded_types->next;
		}
		printf("file_in is = %s\n", s);
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
			s = expanded_types->word;
			if (expanded_types->prev->type == 4 && (is_redirection(expanded_types->type) == 0))
				*i = open(s, O_WRONLY | O_CREAT | O_TRUNC , 0777);  ///hadi asat ra kant khasra mhm ra 9aditha
			else if (expanded_types->prev->type == 3 && (is_redirection(expanded_types->type) == 0))
				*i = open(s, O_WRONLY | O_CREAT | O_APPEND , 0777);
			expanded_types = expanded_types->next;
		}
	}
}

// verifier s'il y'a un genre de redirection au debut de la commande, si oui :
// je distingue les operations selon la longueur de la commande
void	get_command(t_type *tmp2, char *str, t_cmd **cmd, t_type **expanded_types)
{
	if (!tmp2)
		return ;
	if (is_redirection(tmp2->type))
	{
		if (ft_lstsize_type(tmp2) == 2) // cmd = " "
			(*cmd)->cmd = ft_strdup("");
		else if (ft_lstsize_type(tmp2) == 3) // j'affecte le troisieme elment a cmd;
		{
			str = get_node(tmp2)->word;
			(*cmd)->cmd = get_cmd_path(str, g_data->env);
		}
		else
		{
			while(is_redirection(tmp2->type))
				tmp2 = tmp2->next->next; // je pointe apres le fichier et je verifie s'il y'a une commande ou bien une autre directive de redirection
			(*cmd)->cmd = get_cmd_path(tmp2->word, g_data->env);
		}
	}
	else if (tmp2->type == 0)
		(*cmd)->cmd = get_cmd_path((*expanded_types)->word, g_data->env); // la commande doit etre la premiere
}

// loup sur g_data->tokkens, pour remplir la structure t_cmd et j'ajoute cette derniere dans l'arriere de g_data->cmd_list
void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->str = NULL;
	cmd->args_list = NULL;
	cmd->in = 0;
	cmd->out = 1;
}

void	expand_cmdlist(t_list *tmp, char *str)
{
	t_cmd	*cmd;
	t_type	*expanded_types; //katakhed nodes dyal list tmp fihom types m2expandyin
	t_list	*list_files;
	t_type	*tmp2; // katpointer eela content dyal list tmp li fiha types.
	int		i;

	i = 0;
	if (g_data->syntx == 1)
	{
		cmd = NULL;
		return ;
	}
	while (tmp)
	{
		i++;
		tmp2 = tmp->content;
		expanded_types = expander(tmp->content);
		cmd = malloc(sizeof(t_cmd));
		init_cmd(cmd);
		get_command(tmp2, str, &cmd, &expanded_types);
		list_files = get_args(&(cmd->args_list), expanded_types, &cmd);
		get_out(&(cmd->out), list_files, expanded_types);
		get_in(&(cmd->in), list_files, expanded_types);
		ft_lstadd_back(&g_data->cmd_list, ft_lstnew(cmd));
		free_nodes_types(&expanded_types);
		tmp = tmp->next;
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

int		main(int argc, char **argv, char **env)
{
	char **p;

	g_data = malloc(sizeof(t_data));
	init_env_list(env);
	g_data->exitstatu = 0;
	argc = 0;
	argv = NULL;
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		g_data->tokkens = NULL;
		g_data->cmd_list = NULL;
		g_data->line = NULL;
		signal(SIGINT, sig_handler);
		if (!(g_data->line = readline("ader🤡$>")))
	    	return (1);
		if (g_data->line[0])
		{
			parser();
			if (g_data->numcmd == 1 && g_data->cmd_list)
				ft_check(g_data, g_data->cmd_list->content);
			else if (g_data->numcmd < 557 && g_data->numcmd > 0 && g_data->cmd_list)
				mlpipe(g_data);
			add_history(g_data->line);
			//free_nodes_cmd(g_data->cmd_list);
			//free_functio();
		}
	}
	return (0);
}
