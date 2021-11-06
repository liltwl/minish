#include "minishell.h"



void	init_env_list(char **envp)
{
	int		i;
	char	**s;
	t_env	*a;
    t_list  *env;

	i = 1;
	a = malloc(sizeof(t_env));
	s = ft_split(envp[0], '=');
	a->name = s[0];
	a->content = s[1];
	env = ft_lstnew(a);
	while (envp[i])
	{
		s = ft_split(envp[i], '=');
		a = malloc(sizeof(t_env));
		a->name = ft_strdup(s[0]);
		a->content = ft_strdup(s[1]);
		ft_lstadd_back(&(env), ft_lstnew(a));
		i++;
	}
	g_data->env = env;
}

