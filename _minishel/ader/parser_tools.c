#include "../minishell.h"

void	add_in(size_t *i, char c, t_type **head)
{
	t_cl	*tmp;
	t_list	*list;
	char	*str;
	size_t	k;

	list = NULL;
	while (g_data->line[(*i)] == c && g_data->line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = g_data->line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	(*i)--;
	str = ll_to_string(list);
	ft_lstclear(&list, &free_char);
	k = ft_strlen(str);
	if (k == 1)
		ft_lstadd_back_type(head, ft_lstnew_type(str, 6, 0));
	else if (k == 2)
		ft_lstadd_back_type(head, ft_lstnew_type(str, 5, 0));
	else
		log_error("syntax_error\n");
}

void	add_out(size_t *i, char c, t_type **head)
{
	t_cl	*tmp;
	t_list	*list;
	char	*str;
	size_t	k;

	list = NULL;
	while (g_data->line[(*i)] == c && g_data->line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = g_data->line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	(*i)--;
	str = ll_to_string(list);
	ft_lstclear(&list, &free_char);
	k = ft_strlen(str);
	if (k == 1)
		ft_lstadd_back_type(head, ft_lstnew_type(str, 4, 0));
	else if (k == 2)
		ft_lstadd_back_type(head, ft_lstnew_type(str, 3, 0));
	else
		log_error("syntax_error\n");
}

void	add_sq2(size_t *i, char c, t_type **head, char *str)
{
	if (c != '\'')
	{
		if (g_data->line[(*i)] == ' ' || !g_data->line[(*i)])
			ft_lstadd_back_type(head, ft_lstnew_type(str, 2, 0));
		else
			ft_lstadd_back_type(head, ft_lstnew_type(str, 2, 1));
	}
}

int	add_sq(size_t *i, char c, t_type **head)
{
	t_list	*list;
	char	*str;

	(*i)++;
	list = fill_list(i, c);
	str = ll_to_string(list);
	ft_lstclear(&list, &free_char);
	(*i)++;
	if (c == '\'')
	{
		if (g_data->line)
		{
			if (g_data->line[(*i)] == ' ' || !g_data->line[(*i)])
				ft_lstadd_back_type(head, ft_lstnew_type(str, 1, 0));
			else
				ft_lstadd_back_type(head, ft_lstnew_type(str, 1, 1));
		}
		(*i) -= 2;
		return (1);
	}
	add_sq2(i, c, head, str);
	(*i) -= 2;
	return (1);
}

void	ffunction2(t_type **head, char **tab, size_t i, int f)
{
	int		l;

	l = 0;
	while (tab[l])
		l++;
	if (l != 1)
	{
		while (tab[f] && f < (l - 1))
			ft_lstadd_back_type(head, ft_lstnew_type(tab[f++], 0, 0));
		if ((g_data->line[i] == '\'' || g_data->line[i] == '"')
			&& g_data->line[i - 1] != ' ')
			ft_lstadd_back_type(head, ft_lstnew_type(tab[f], 0, 1));
		else
		{
			if (tab[f] == NULL)
				ft_lstadd_back_type(head, ft_lstnew_type(ft_strdup(""), 0, 0));
			else
				ft_lstadd_back_type(head, ft_lstnew_type(tab[f], 0, 0));
		}
	}
}
