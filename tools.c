#include "minishell.h"


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
