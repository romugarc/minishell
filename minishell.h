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

typedef struct s_inc
{
	int	i;
	int	j;
	int	k;
	int	n;
	int	m;
	int l_i;
	int	l_j;
	int	l_e;
	int	lastfd;
}	t_inc;

typedef struct s_f_str
{
	char	*sp_chars;
	char	*quotes;
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
int			malloc_tab_files(t_commands **c, int nb_pipes);
void		count_redirections(t_commands **commands, int np, t_f_str f_str);
int			form_tab(t_commands **com, t_f_str f_str, int np);
int			manage_infile(t_commands **com, t_f_str *f_str, t_inc *i, int *start);
int			manage_outfile(t_commands **com, t_f_str *f_str, t_inc *i, int *start);
int			form_tab(t_commands **com, t_f_str f_str, int np);
int			form_tab2(t_commands **com, t_f_str f_str, int np);
int			correct_tab(t_commands **com, t_f_str f_str, int np);
int			reform_tab(t_commands **com, int np);
int			create_fd(t_commands **cmd, int np);
int			form_heredoc(t_commands **c, int nb_pipes);

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
void		prmai_handler(int argc, char **argv);

//signal
void		sig_handler(int signum);

#endif
