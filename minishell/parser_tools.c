#include "minishell.h"

void	add_in(size_t *i, char c, t_type **head)
{
	t_cl	*tmp;
	t_list  *list;
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
	k = ft_strlen(str);
	if (k == 1)
		ft_lstadd_back_type(head,ft_lstnew_type(str, 6, 0));
	else if (k == 2)
		ft_lstadd_back_type(head,ft_lstnew_type(str, 5, 0));
	else
	{
		printf("error\n");
		exit(1);
	}
}
void	add_out(size_t *i, char c, t_type **head)
{
	t_cl	*tmp;
	t_list  *list;
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
	k = ft_strlen(str);
	if (k == 1)
		ft_lstadd_back_type(head,ft_lstnew_type(str, 4, 0));
	else if (k == 2)
		ft_lstadd_back_type(head,ft_lstnew_type(str, 3, 0));
	else
	{
		printf("error\n");
		exit(1);
	}
}

/*since i didn't meet the c charachter i add the charchters between '' or "" in a struct type t_cl that add a charchter in a c variable
 and i add all the structs back to each others in a list of type t_list
 then i convert the list to a string, finally i add the string to a list of type t_type that
 contains the string and his type. */


int	add_sq(size_t *i, char c, t_type **head)
{
	t_list  *list;
	char 	*str;

	(*i)++;
	list = fill_list(i, c);
	str = ll_to_string(list);
	if (c == '\'')
	{
		(*i)++;
		if (g_data->line[(*i)] == ' ' || !g_data->line[(*i)])
			ft_lstadd_back_type(head,ft_lstnew_type(str, 1, 0));
		else
			ft_lstadd_back_type(head,ft_lstnew_type(str, 1, 1));
	}
	else
	{
		(*i)++;
		if (g_data->line[(*i)] == ' ' || !g_data->line[(*i)])
			ft_lstadd_back_type(head,ft_lstnew_type(str, 2, 0));
		else
			ft_lstadd_back_type(head,ft_lstnew_type(str, 2, 1));
	}
	(*i)--;
	(*i)--;
	return (1);
}
/*i add the charchters till i meet '', "", |, or >  in a struct type t_cl that add a charchter in a c variable
 and i add all the structs back to each others in a list of type t_list
 then i convert the list to a string, finally i add the string to a list of type t_type that
 contains the string and his type.*/
void	ffunction(t_type **head, char **tab, size_t i, int f)
{
	int		l;

	l = 0;
	while (tab[l])
		l++;
	if (l == 1)
	{
		if (g_data->line[i] == '\'' || g_data->line[i] == '"')
			ft_lstadd_back_type(head,ft_lstnew_type(tab[0], 0, 1));
		else
			ft_lstadd_back_type(head,ft_lstnew_type(tab[0], 0, 0));
	}
	else
	{
		while (tab[f] && f < (l - 1))
		{
			ft_lstadd_back_type(head,ft_lstnew_type(tab[f], 0, 0));      
			f++;
		}
		// printf("line de i :%c\n", g_data->line[i - 1]);
		if ((g_data->line[i] == '\'' || g_data->line[i] == '"') && g_data->line[i - 1] != ' ')
			ft_lstadd_back_type(head,ft_lstnew_type(tab[f], 0, 1));
		else
		{
			if (tab[f] == NULL)
				ft_lstadd_back_type(head,ft_lstnew_type(ft_strdup(""), 0, 0));
			else
				ft_lstadd_back_type(head,ft_lstnew_type(tab[f], 0, 0));
		}
	}
}

int		adds(size_t *i, t_type **head)
{
	t_cl	*tmp;
	t_list  *list;
	char    **tab;
	char	*str;
	list = NULL;
	while ((g_data->line[(*i)] != '\'' && g_data->line[(*i)] != '"' && g_data->line[(*i)] != '|' && g_data->line[(*i)] != '>' && g_data->line[(*i)] != '<') && g_data->line[(*i)])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = g_data->line[(*i)];
		ft_lstadd_back(&list, ft_lstnew(tmp));
		(*i)++;
	}
	str = ll_to_string(list);
	tab = ft_split(str, ' ');
	ffunction(head, tab, *i, 0);
	(*i)--;
	return (1);
}
