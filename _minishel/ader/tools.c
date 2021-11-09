#include "../minishell.h"

t_type	*ft_lstnew_type(char *content, int i, int b)
{
	t_type	*new;

	new = (t_type *)malloc(sizeof(t_type) * 1);
	new->word = strdup(content);
	new->type = i;
	new->a = b;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_type	*ft_lstlasttype(t_type *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_type(t_type **alst, t_type *new)
{
	t_type	*last;

	new->next = NULL;
	last = *alst;
	if (!(*alst))
	{
		new->prev = NULL;
		*alst = new;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

void	init_data(void)
{
	g_data->tokkens = NULL;
	g_data->cmd_list = NULL;
	g_data->line = NULL;
	g_data->sigpid = 0;
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
			if (expanded_types->prev->type == 4
				&& (is_redirection(expanded_types->type) == 0))
				*i = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			else if (expanded_types->prev->type == 3
				&& (is_redirection(expanded_types->type) == 0))
				*i = open(s, O_WRONLY | O_CREAT | O_APPEND, 0777);
			expanded_types = expanded_types->next;
		}
	}
}
