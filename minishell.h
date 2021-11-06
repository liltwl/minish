#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/time.h>
# include "ft_libft/libft.h"
// # include "leak_detector_c/leak_detector_c.h"
# define FALSE 0
# define TRUE 1
# define READ 0
# define WRITE 1
# define SUCCESS 0
# define FAILURE 1
# define KEY_UP 183
# define KEY_DOWN 184
# define ENTER 10
# define KEY_REMOVE 127


typedef struct s_env
{
	char			*name;
	char			*content;
}               t_env;

typedef struct s_cl
{
	char c;
}				t_cl;

typedef	struct s_cmd
{
	char	*cmd;
	t_list	*args_list;
	char	**str;
	int		in;
	int		out;
}				t_cmd;

typedef	struct s_type
{
	char	*word;
	int		type;
	int		a;
	struct s_type *next;
	struct s_type *prev;
}				t_type;

typedef struct s_data
{
	t_list 	*env;
	t_list	*cmd_list;
	t_list	*tokkens;
	char	*line;
	int		exitstatu;
	int		numcmd;
	int 	syntx;
}				t_data;

t_data		*g_data;

int	builtin_echo(char **args, char **env);
void	excute_cmd(void);
//void	sig_handler(int sig);

//
char	**ll_to_dp(t_list *list);
void	expand_cmdlist(t_list *tmp, char *str);
void    create_file(char *s, t_cmd *cmd);
char 	*ll_to_string(t_list *head);
void	init_env_list(char **evnp);
void	printlist(t_list *env);
t_type	*expander(t_type *tmp);
int     real_character(char *line, int i, char c);
t_type	*ft_lstnew_type(char *content, int i, int b);
void	ft_lstadd_back_type(t_type **alst, t_type *new);
int		check_words(t_type *tmp);
char	*make_string(char *str, char c);
int     real_character1(char *line, int i, char c);
char	*return_env_value(char *key);
void	add_string(t_list **head, char *str);
int		add_sq(size_t *i, char c, t_type **head);
int		adds(size_t *i, t_type **head);
int    	check_if_sq(char *str, int *j);
void    help_q(t_list **head, char c);
void    parser2(t_list *cmd_list);
void	print_cmdlist(t_list *listcmd);
void	parser(void);
void	print_types(t_type *type);
void	add_tab_to_ll(t_type **head, char *str, int type, int a);
void	print_cmd(void);
void	print_tokkens(void);
char	*get_cmd_path(char *str, t_list *env);



char	*my_ft_strjoin(char const *s1, char const *s2);
void	add_out(size_t *i, char c, t_type **head);
void	add_in(size_t *i, char c, t_type **head);
t_type	*get_cmd(t_type *type);
t_type	*get_node(t_type *types);
void	help_args(t_type **tmp, t_list **args);
int		ft_lstsize_type(t_type *type);
t_type	*ft_lstlast_type(t_type *type);
t_type	*ft_lstnew_type2(char *content, int i, int a);
void	add_tab_to_ll(t_type **head, char *str, int type, int a);
t_list	*fill_list(size_t *i, char c);
void    log_error(char *s);
void    syntax_error();
void	free_functio();
char    **ft_free_split(char **d);
void	free_nodes_cmd(t_list	*tmp);
char    **ft_print_split(char **d);
int     is_redirection(int i);
char	*get_sq_word(t_type *types, int j, int *f);

/*clear tools*/
void	free_env(void *content);
void	free_char(void *content);
void	free_table(char **table);
void	clear_and_exit(void);
void	free_nodes_types(t_type	**list);
void	free_type(void *content);


char	**ft_free_split(char **d);
void	free_nodes_cmd(t_list	*tmp);
char	**ft_print_split(char **d);
int		is_redirection(int i);
char	*get_sq_word(t_type *types, int j, int *f);
void	ft_exit(t_cmd *cmd, t_data *data);
void	sig_handler(int sig);
void	ft_error(char *p, int i);
int		ft_spaceskip(char *line, int *i);
int		ft_cmp(char *s1, char *s2);
int		ft_splitlen(char **p);
char	**ft_free_split(char **d);
char	**ft_print_split(char **d);
t_env	*ft_lstfind(t_list *lst, char *name);
t_cmd	*ft_findcmd(t_list *data, int id);
void	do_help(void);
void	do_echo(t_data *data, t_cmd *cmd);
void	do_pwd(t_data *l, t_cmd *cmd);
void	do_env(t_data *data, t_cmd *cmd);
void	change_oldpwd(t_data *data);
void	change_pwd(t_data *data);
void	ft_docdret(t_data *data);
void	ft_docdsing(t_data *data);
void	ft_docd(t_data *data, t_cmd *cmd);
t_env	*ft_smllst(t_list *env);
t_env	*ft_getbiglst(t_list *tmp1, t_env *big);
void	ft_printsortlst(t_data	*data, t_cmd *cmd);
int		ft_findc(char *str, char c);
t_env	*ft_lstnewenv(char *name, char *str);
void	addnewenv(char	**p, t_data *data);
char	**mycatstr(char *str, int i);
void	export_join(t_data *data, char **p);
void	ft_lstupdate(t_data *data, char **str, int j);
void	do_export(t_data *data, t_cmd *cmd);
void	ft_deletlst(char *name, t_list *env);
void	do_unset(t_data *data, t_cmd *cmd);
int		ft_myatoi(char *str);
void	ft_exit(t_cmd *cmd, t_data *data);
void	exec_cmd(char **cmd1, t_data *l, t_cmd *cmd);
void	ft_check(t_data *l, t_cmd *cmd);
void	execdup(t_data *data, int *fds, int x, int fd);
void	mlpipe(t_data *data);
int		ff(char *p);

#endif