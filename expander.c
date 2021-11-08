#include "minishell.h"

static void	add_to_lk(char *s, int a, t_cl *tmp, t_list **list_keys)
{
	tmp = malloc(sizeof(t_cl));
	tmp->c = s[a];
	ft_lstadd_back(list_keys, ft_lstnew(tmp));
}

char	*return_env_value(char *key)
{
	t_list	*env;
	t_env	*tmp;
	size_t		i;

	env = g_data->env;
	i = 0;
	while (env)
	{
		tmp = (t_env *)env->content;
		i = ft_strlen(tmp->name);
		if (i == ft_strlen(key))
		{
			if (ft_strcmp(tmp->name, key) == 0)
				return (tmp->content);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

static void	to_skip(char *s, size_t *a, t_list **head, size_t i)
{
	t_cl	*tmp;
	t_list	*list_keys;
	char	*key;
	char	*swap;

	list_keys = NULL;
	tmp = NULL;
	if (s[i + 1] == '\'' || s[i + 1] == '?')
	{
		if (s[i + 1] == '?')
		{
			add_string(head, ft_itoa(g_data->exitstatu));
			(*a)++; // hadi bach nfoto : ?
		}
		else
		{
			add_to_lk(s, *a, tmp, &list_keys);
			key = ll_to_string(list_keys);
			add_string(head, key);
			ft_lstclear(&list_keys, &free_char);
			free(key);
		}
		return ;
	}
	(*a)++;
	while (ft_isalnum(s[(*a)]) == 1)
			add_to_lk(s, (*a)++, tmp, &list_keys);
	swap = ll_to_string(list_keys);
	ft_lstclear(&list_keys, &free_char);
	add_string(head, return_env_value(swap));
	free(swap);
	(*a)--;
}
// ila kan khasso yt2expanda kanb6a n2ajouter f les charactres f wahd list
// hta kanl6a $ HHHHH
static void	expand_word(char *str, t_list **head, int a, size_t i)
{
	t_cl	*tmp;
	size_t	f;

	if (!str[i])
	{
		tmp = malloc(sizeof(t_cl));
		tmp->c = '\0';
		ft_lstadd_back(head, ft_lstnew(tmp));
		return ;
	}
    while (1)
    {
		tmp = malloc(sizeof(t_cl));
		tmp->c = str[i];
        if (str[i] ==  '$')
		{
			f = i;
			to_skip(str , &i, head, f);
			free(tmp);
		}
		else if (str[i] == ' ' && a == 0)
		{
			ft_lstadd_back(head, ft_lstnew(tmp));
			while (str[i] == ' ')
				i++;
			i--;
		}
		else
			ft_lstadd_back(head, ft_lstnew(tmp));
		if (i++ >= ft_strlen(str) - 1)
			break;
    }
}

t_type	*expander(t_type *tmp)
{
    t_type  *tmp2;
    t_type  *new;
	t_list	*head;
	char	*to_str;

    tmp2 = tmp;
	new = NULL;
    while (tmp2)
    {
		head = NULL;
        if (tmp2->type == 2 || tmp2->type == 0)
           expand_word(tmp2->word, &head, tmp2->type, 0);
		else
			add_string(&head, tmp2->word);
		if (tmp2->type == 0)
		{
			to_str = ll_to_string(head);
			printf("%s\n", to_str);
			add_tab_to_ll(&new, to_str, tmp2->type, tmp2->a);
			free(to_str);
		}
		else
 			ft_lstadd_back_type(&new, ft_lstnew_type2(ll_to_string(head), tmp2->type, tmp2->a));
		ft_lstclear(&head, &free_char);
        tmp2 = tmp2->next;
    }
    return (new);
}
