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

typedef struct s_commands
{
	int		nb_args_in_command;
	int		nb_infile;
	int		nb_outfile;
	int		fdin;
	int		fdout;
	int		builtin;
	int		heredoc;
	int		append;
	char	**tab_infile;
	char	**tab_outfile;
	char	**sgl_cmd;
}	t_commands;

typedef struct s_inc
{
	int	i;
	int	j;
	int	k;
	int	n;
	int l_i;
	int	l_j;
	int	l_e;
}	t_inc;

typedef struct s_f_str
{
	char	*sp_chars;
	char	*quotes;
	char	**tab_sp_chars;
	char	**tab_quotes;
	t_inc	i;
}	t_f_str;

typedef struct s_exec
{
	int		nb_comm;
	pid_t	*cpid;
	int		**fd;
	int		comm_i;
	char	**env_tmp;
	int		status;
	int		temp;
}	t_exec;

typedef struct s_envcpy
{
	int				equal;
	char			*var;
	char			*val;
	int				env_;
	int				is_oldpwd;
	char			**oldpwd;
	struct s_envcpy	*next;
}	t_envlist;

//parsing
int			parsing(t_commands **commands, t_f_str *f_str, int *nb_pipes, char **line);
char		*correct_line(char *line);
int			quotes_flags(t_f_str *f_str, char *line);
int			special_char_flags(t_f_str *f_str, char *line);
int			find_end_redirection(t_f_str f_str, int *k);
int			find_special_char(char c, t_f_str f_str, t_inc *i, char *s_c);

//exec
int			exec_main(t_commands *commands, int nb_comm, t_envlist **envc);
int			pipe_error_case(int nb_comm, t_exec exec);
void		wait_all_cpid(pid_t *cpid, int status, int i);
int			**tab_fd_mall(int nb_comm);
void		close_fd(int **fd, int i);
void		child_process(t_commands *commands, t_exec exec, int nb_comm, t_envlist **envc);
int			ft_echo(char **tab, int nb_comm);
int			is_builtins(char **cmds, int nb_comm, t_envlist **envc);
int			strcmp_tof(char *cmd, char *str);
int			ft_echo_n(char *str);
int			ft_echo_next_n(char *str);
int			ft_pwd(int nb_comm);
int			ft_cd(char **tab, int nb_comm, t_envlist **envc);
void		dup_fd(t_exec exec, int nb_comm);
int			is_it_builtin(char *cmd);
t_envlist	*envcpy(char **envp);
t_commands	*commands_path(t_commands *comm, int nb_comm);
int			get_tmp_env(t_envlist **envc, t_exec *exec);
int			ft_unset(char **sgl_cmd, int nb_comm, t_envlist **envc);
int			ft_export(char **comm, int nb_comm, t_envlist **envc);
int			ft_strcmp(char *s1, char *s2);
int			valid_id(char *var, char *cmd);
void		ft_lstadd_back_env(t_envlist **alst, t_envlist *new);
t_envlist	*ft_lstnew_env(char **envp, int line);
int			ft_env(char **cmds, int nb_comm, t_envlist *envc);
void		ft_exit(char **cmd, int nb_comm);
void		rm_var(char *var, t_envlist **envc);



//exec utils

//parsing utils
void		prompt(void);
int			count_arguments(char *line, char c, t_f_str *f_str);
int			is_in_quotes(t_f_str f_str, int i);
void		ft_increment(char const *s, char c, size_t *i, t_f_str f_str);
char		**ft_split_v2(char *s, char c, t_f_str *f_str);
char		**ft_split_v2old(char const *s, char c, t_f_str f_str);

//free
void		free_command_line(t_commands *commands, char *line, int nb_pipes);
void		free_tab(int **tab, int i);
int			free_all(t_exec exec, int nb_comm);
void		free_char_tab(char **tab);
int			free_char_tab_ret(t_exec exec);

//init
t_commands	*init_commands(char	*line, int nb_pipes, t_f_str *fs);
void		init_inc(t_inc *inc);
int			exec_init(t_exec *exec, int nb_comm);

//error
int			error_handler(int argc, char **argv);

//signal
void		sig_handler(int signum);

#endif
