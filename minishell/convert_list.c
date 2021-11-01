#include "minishell.h"

char *ll_to_string(t_list *head)
{
    char    *str;
    int     len;

    int i;
    
    i = 0;
    len = ft_lstsize(head);
    str = malloc(len + 1);
    while (head)
    {
        str[i] = ((t_cl *)head->content)->c;
        i++;
        head = head->next;
    }
    str[len] = '\0';
    return (str);
}

char	**ll_to_dp(t_list *list)
{
	int		len;
	int		i;
	char	**str;

	len =  ft_lstsize(list);
	str = malloc(sizeof(char *)  * (len + 1));
	i = 0;
	while (list)
	{
		str[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	str[i] = 0;
	return (str);
}
