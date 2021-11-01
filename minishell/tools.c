#include "minishell.h"

void    log_error(char *s)
{
    ft_putstr(s);
    exit(1);
}

// void    check_words(t_type *tmp)
// {
//     t_type  *tmp2;
//     int     i;

//     tmp2 = tmp;
//     i = 0;
//     while (tmp2)
//     {
//         if (tmp2->word[0] == '\'')
//         {
//             if (ft_strlen(tmp2->word) == 1)
//                 log_error("syntax_error\n", 2);
//             i = ft_strlen(tmp2->word);
//             if (tmp2->word[i - 1] != '\'')
//             {
//                 log_error("syntax_error\n", 2);
//             }
//         }
//         else if (tmp2->word[0] == '"')
//         {
//             if (ft_strlen(tmp2->word) == 1)
//                 log_error("syntax_error\n", 2);
//             i = ft_strlen(tmp2->word);
//             if (tmp2->word[i - 1] != '"')
//                 log_error("syntax_error\n", 2);
//         }
//         tmp2 = tmp2->next;
//     }
// }

t_type	*ft_lstnew_type(char *content, int i, int b)
{
	t_type *new;

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
    t_type  *last;

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
        last->next  = new;
        new->prev = last;
    }
}
