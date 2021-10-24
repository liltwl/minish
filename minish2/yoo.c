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

int		ft_frstr(t_cmd *l, t_data *data, int *i, int j)
{
	char **tmp;
	int fd;
	int x;

	x = *i;
	if (j == 2)
		fd = ft_heredoc(l->str[++*i]);
	else
		fd = open(l->str[++*i], O_RDONLY);
	tmp = l->str;
	if (tmp[2] != 0)
	{
		l->str = malloc(sizeof(char **) * (ft_splitlen(&tmp[1]) + 1));
		while (tmp[++*i] != 0)
			l->str[*i - 2] = ft_strdup(tmp[*i]);
		l->str[*i - 2] = 0;
	}
	else
		l->str = NULL;
	ft_free_split(tmp);
	*i = --x;
	return (fd);
}

int		ft_midr(t_cmd *l, t_data *data, int *i, int j)
{
	char **tmp;
	int fd;
	int	x;

	x = *i;
	fd = 0;
	if (l->str[(*i) + 1] == 0)
	{
		ft_free_split(l->str);
		l->str = NULL;
		data->exitstatu = 258;
		return (fd);
	}
	if (j == 2)
		fd = ft_heredoc(l->str[(*i) + 1]);
	else
		fd = open(l->str[(*i) + 1], O_RDONLY);
	while (l->str[(*i)])
	{
		free (l->str[(*i)]);
		if (l->str[(*i) + 1] && l->str[(*i) + 2])
			l->str[(*i)] = ft_strdup(l->str[(*i) + 2]);
		else
			l->str[(*i)] = NULL;
		(*i)++;
	}
	*i = --x;
	return (fd);
}

int		ft_getfile(t_cmd *l, t_data *data)
{
	int i;
	int	fd;
	char	**tmp;

	i = -1;
	fd = 0;
	while (l->str && l->str[++i] != NULL)
	{
		if (!ft_strncmp(l->str[i], "<", 2) && i == 0 && l->str[1] != 0)
			fd = ft_frstr(l, data, &i, 0);
		else if (!ft_strncmp(l->str[i], "<<", 3) && i == 0 && l->str[1] != 0)
			fd = ft_frstr(l, data, &i, 2);
		else if (!ft_strncmp(l->str[i], "<", 2)	&& i != 0)
			fd = ft_midr(l, data, &i, 0);
		else if (!ft_strncmp(l->str[i], "<<", 3)	&& i != 0)
			fd = ft_midr(l, data, &i, 2);
	}
	return (fd);
}
