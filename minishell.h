#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"

# define TRUE 1
# define FALSE 0
# define ERR -1
# define PROMPT_SYMBOL "minishell$ "

int	g_errno;

typedef struct s_commands
{
	int		nb_args_in_command;
	int		nb_infile;
	int		nb_outfile;
	int		nb_hd;
	int		fdin;
	int		fdout;
	int		builtin;
	int		heredoc;
	int		append;
	int		*tab_fdin;
	int		*tab_fdout;
	char	**tab_infile;
	char	**tab_outfile;
	char	**tab_hd;
	char	*flag_in;
	char	*flag_out;
	char	**sgl_cmd;
}	t_commands;

typedef struct s_heredoc
{
	int	*pipefd;
	int	cpid;
	int	status;
}	t_heredoc;

typedef struct s_inc
{
	int	i;
	int	j;
	int	k;
	int	n;
	int l_i;
	int	l_j;
	int	l_e;
	int	lastfd;
	int	start;
}	t_inc;

typedef struct s_f_str
{
	char	*sp_chars;
	char	*quotes;
	t_inc	i;
}	t_f_str;

typedef struct	s_misc
{
	int		nb_commands;
	char	*line;
}	t_misc;

typedef struct s_exec
{
	int		nb_comm;
	pid_t	*cpid;
	int		**fd;
	int		comm_i;
	char	**env_tmp;
	int		status;
	int		temp;
	int		error;
}	t_exec;

typedef struct s_envcpy
{
	int				equal;
	char			*var;
	char			*val;
	int				env_;
	char			**oldpwd;
	int				is_oldpwd;
	struct s_envcpy	*next;
}	t_envlist;

//parsing
int			parsing(t_commands **commands, t_f_str *f_str, t_misc *misc, t_envlist *envc);
char		*correct_line(char *line);
int			quotes_flags(t_f_str *f_str, char *line);
int			special_char_flags(t_f_str *f_str, char *line);
int			find_end_redirection(t_f_str f_str, int *k);
int			find_special_char(char c, t_f_str f_str, t_inc *i, char *s_c);
int			malloc_tab_files(t_commands **c, int nb_pipes);
void		count_redirections(t_commands **commands, int np, t_f_str f_str);
int			manage_infile(t_commands **com, t_f_str f_str, t_inc *i, int *start);
int			manage_outfile(t_commands **com, t_f_str f_str, t_inc *i, int *start);
int			form_tab(t_commands **com, int np);
int			form_tab2(t_commands **com, int np);
int			correct_tab(t_commands **com, int np);
int			reform_tab(t_commands **com, int np);
int			create_fd(t_commands **cmd, int np, t_envlist *envc);
int			form_heredoc(t_commands **c, int nb_pipes);
int			create_fdin(t_commands **cmd, t_inc inc, int *lastfd);
int			create_fdin2(t_commands **cmd, t_inc inc, int *lastfd, t_envlist *envc);
int			expand_variable(t_commands **cmd, int np, t_envlist *envc);
int			copy_var(char *line, t_inc *i, t_envlist *envc, char **new_line);
int			expand_search(char *str, t_inc inc, t_f_str f_str);
int			cat_ex_var(char *line, t_inc *i, char *envstr, char **new_line, int mode);
int			cat_ex_varnf(char *line, t_inc *i, char **new_line);
int			search_expand(char **line, t_envlist *envc);
int			expand_heredoc(char **str, t_envlist *envc);
int			check_fd(t_commands **cmd, int np);
int			remove_quotes(t_commands **cmd, int np);
int			parse_error(char *line, t_f_str f_str);

//exec
int			exec_main(t_commands *commands, int nb_comm, t_envlist **envc);
int			pipe_error_case(int nb_comm, t_exec exec, t_commands *cmd);
void		wait_all_cpid(pid_t *cpid, int status, int i, t_exec *exec);
int			**tab_fd_mall(int nb_comm);
void		close_fd(int **fd, int i, t_commands *cmd);
void		child_process(t_commands *commands, t_exec *exec, t_envlist **envc, int *oldp_stat);
int			ft_echo(char **tab, t_exec exec, t_commands cmd);
int			is_builtins(t_commands cmd, t_exec *exec, t_envlist **envc, int *oldp_stat);
int			strcmp_tof(char *cmd, char *str);
int			ft_echo_n(char *str);
int			ft_echo_next_n(char *str);
int			ft_pwd(int nb_comm, t_commands cmd, t_exec exec);
int			ft_cd(char **tab, int nb_comm, t_envlist **envc);
void		dup_fd(t_exec exec, int nb_comm, t_commands *cmd);
int			is_it_builtin(char *cmd, t_exec *exec);
t_envlist	*envcpy(char **envp);
t_commands	*commands_path(t_commands *comm, int nb_comm, t_envlist *envc);
int			get_tmp_env(t_envlist **envc, t_exec *exec);
int			ft_unset(char **sgl_cmd, int nb_comm, t_envlist **envc, int *oldp_stat);
int			ft_export(t_commands cmd, t_exec exec, t_envlist **envc, int *oldp_stat);
int			ft_strcmp(char *s1, char *s2);
int			valid_id(char *var, char *cmd);
void		ft_lstadd_back_env(t_envlist **alst, t_envlist *new_lst);
t_envlist	*ft_lstnew_env(char **envp, int line);
int			ft_env(t_commands cmd, t_exec exec, t_envlist *envc, int oldp_stat);
void		ft_exit(char **cmd, int nb_comm);
void		rm_var(char *var, t_envlist **envc);
void		rm_val(char *str, t_envlist **envc, int *first_time);
int			check_pwd(void);
int			check_cmd_fd(t_commands cmd);
int			check_access(t_commands comm, t_envlist **envc);
void		sighandler(int sig);
void		pipe_sighandler(int sig);



//exec utils

//parsing utils
void		prompt(void);
int			count_arguments(char *line, char c, t_f_str *f_str);
int			is_in_quotes(t_f_str f_str, int i);
void		ft_increment(char const *s, char c, size_t *i, t_f_str f_str);
char		**ft_split_v2(char *s, char c, t_f_str *f_str);
char		**ft_split_v2old(char const *s, char c, t_f_str f_str);
int			ft_del_str_from_i(char *str, int i);
void		close_tab_fd(int *fd, int i);
int			ft_strrcmp(char *s1, char *s2);
int			ft_isenvarc(char c, int mode);
char		*ft_strdup_s_to_e(char const *src, size_t n, size_t index);
int			free_flags(t_f_str f_str, int mode);
int			is_sp_char(t_f_str f_str, int i);

//free
void		free_command_line(t_commands *commands, char *line, int nb_pipes);
void		free_tab(int **tab, int i);
int			free_all(t_exec exec, int nb_comm);
void		free_char_tab(char **tab);
void		ft_free_tab(char **tab);
int			free_char_tab_ret(t_exec exec);
int			free_expand(char *a, char *b, char *c, char *d);


//init
t_commands	*init_commands(char	*line, int nb_pipes, t_f_str *fs);
void		init_inc(t_inc *inc);
int			exec_init(t_exec *exec, int nb_comm);
int			*init_tab_fd(int nb_file);
void		init_command_tab(t_commands **commands, int nb_pipes);

//error
int			error_handler(int argc, char **argv);

//signal
void		sig_handler(int signum);

#endif
