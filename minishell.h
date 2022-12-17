/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:21:58 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 14:26:28 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:19:24 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/17 14:19:24 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

int	g_errno;

typedef struct s_commands
{
	int		nb_inf;
	int		nb_outf;
	int		nb_hd;
	int		fdin;
	int		fdout;
	int		builtin;
	int		heredoc;
	int		append;
	int		*tab_fdin;
	int		*tab_fdout;
	char	**tab_inf;
	char	**tab_outf;
	char	*flag_in;
	char	*flag_out;
	char	**sgl_cmd;
}	t_cmd;

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
	int	l_i;
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
	struct s_envcpy	*next;
}	t_envlist;

typedef struct s_misc
{
	int			nb_commands;
	int			mode;
	char		*line;
	char		*ex_var;
	t_envlist	*tmp;
}	t_misc;

//parsing
int			parsing(t_cmd **cmd, t_f_str *f_str, t_misc *misc, t_envlist *envc);
char		*correct_line(char *line);
int			quotes_flags(t_f_str *f_str, char *line);
int			special_char_flags(t_f_str *f_str, char *line);
int			find_end_redirection(t_f_str f_str, int *k);
int			find_special_char(char c, t_f_str f_str, t_inc *i, char *s_c);
int			malloc_tab_files(t_cmd **c, int nb_pipes);
void		count_redirections(t_cmd **commands, int np, t_f_str f_str);
int			manage_infile(t_cmd **com, t_f_str f_str, t_inc *i, int *start);
int			manage_outfile(t_cmd **com, t_f_str f_str, t_inc *i, int *start);
int			form_tab(t_cmd **com, int np);
int			form_tab2(t_cmd **com, int np);
int			correct_tab(t_cmd **com, int np);
int			reform_tab(t_cmd **com, int np);
int			create_fd(t_cmd **cmd, int np, t_envlist *envc);
int			create_fdin(t_cmd **cmd, t_inc inc, int *lastfd);
int			create_fdin2(t_cmd **cmd, t_inc inc, int *lastfd, t_envlist *envc);
int			expand_variable(t_cmd **cmd, int np, t_envlist *envc);
int			copy_var(char *line, t_inc *i, t_envlist *envc, char **new_line);
int			cat_ex_var(char *line, t_inc *i, char *envstr, char **new_line);
int			cat_ex_varnf(char *line, t_inc *i, char **new_line);
int			search_expand(char **line, t_envlist *envc);
int			expand_heredoc(char **str, t_envlist *envc);
int			check_fd(t_cmd **cmd, int np);
int			remove_quotes(t_cmd **cmd, int np);
int			removing_quotes(char **str);
int			parse_error(char *line, t_f_str f_str);
int			cat_ex_var(char *line, t_inc *i, char *envstr, char **new_line);
int			cat_ex_varnf(char *line, t_inc *i, char **new_line);
int			create_fdnorm(t_cmd **cmd, t_inc *i, int mode, t_envlist *env);
int			hd_routine(t_cmd **c, t_inc inc, t_heredoc *hd, t_envlist *envc);

//exec
int			exec_main(t_cmd *commands, int nb_comm, t_envlist **envc);
int			pipe_error_case(int nb_comm, t_exec exec, t_cmd *cmd);
void		wait_all_cpid(pid_t *cpid, int status, int i, t_exec *exec);
int			**tab_fd_mall(int nb_comm);
void		close_fd(int **fd, int i, t_cmd *cmd);
void		child_process(t_cmd *commands, t_exec *exec, t_envlist **envc, int *oldp_stat);
int			ft_echo(char **tab, t_exec exec, t_cmd cmd);
int			is_builtins(t_cmd cmd, t_exec *exec, t_envlist **envc, int *oldp);
int			strcmp_tof(char *cmd, char *str);
int			ft_echo_n(char *str);
int			ft_echo_next_n(char *str);
int			ft_pwd(int nb_comm, t_cmd cmd, t_exec exec);
int			ft_cd(char **tab, int nb_comm, t_envlist **envc);
void		dup_fd(t_exec exec, int nb_comm, t_cmd *cmd);
int			is_it_builtin(char *cmd, t_exec *exec);
t_envlist	*envcpy(char **envp);
t_cmd		*commands_path(t_cmd *comm, int nb_comm, t_envlist *envc);
int			get_tmp_env(t_envlist **envc, t_exec *exec);
int			ft_unset(char **sgl_cmd, int nb_comm, t_envlist **envc, int *oldp);
int			ft_export(t_cmd cmd, t_exec exec, t_envlist **envc, int *oldp_stat);
int			ft_strcmp(char *s1, char *s2);
int			valid_id(char *var, char *cmd);
void		ft_lstadd_back_env(t_envlist **alst, t_envlist *new_lst);
t_envlist	*ft_lstnew_env(char **envp, int line);
int			ft_env(t_cmd cmd, t_exec exec, t_envlist *envc, int oldp_stat);
void		ft_exit(char **cmd, int nb_comm);
void		rm_var(char *var, t_envlist **envc);
int			rm_val(char *str, t_envlist **envc, int *first_time);
int			check_pwd(void);
int			check_cmd_fd(t_cmd cmd);
int			check_access(t_cmd comm, t_envlist **envc);
void		sighandler(int sig);
void		pipe_sighandler(int sig);
char		*new_comm(char *sglcmd, char *temp);
char		*get_slash(char *str);
void		free_envc(t_envlist *envc);
int			check_access(t_cmd comm, t_envlist **envc);
void		print_export(t_envlist *envc, int oldp_stat, int out);
int			add_export(t_envlist **envc, char *new_var, char c);
int			get_next_val(t_envlist **envc, char *new_var, char c);
int			get_new_val(t_envlist **envc, char *new_val, char c);
int			valid_id_exp(char *var, char *cmd, int *oldp_stat);
char		*export_valstr(char *new_var);
char		*export_varstr(char *new_var, char c);

//exec utils
int			puterror(char *s1, char *s2, int mod, int ret);
int			put_char_error(char c, int mod, int ret);
int			is_command_path(t_cmd cmd, t_envlist **envc);
int			is_it_path(char *str);
int			whithout_builtins(t_cmd comm);
void		search_var(t_envlist **cpy, char *search);
int			whithout_builtins(t_cmd comm);
int			is_it_path(char *str);
int			check_cmd_fd(t_cmd cmd);
int			get_shlvl(t_envlist **envc);
t_envlist	*new_shlvl(void);
int			strlen_from(char *str, char *from);
int			strlen_until(char *str, char *until);
char		*valuestr(char **envp, int line);
char		*varstr(char **envp, int line);
char		*check_comm(t_cmd comm, char **allpath);
char		*new_comm(char *sglcmd, char *temp);
int			strlen_after_c(char *new_var, char c);
int			strlen_from_c(char *str, char c);
int			strlen_until_c(char *new_var, char c);
int			is_equal(char *new_var);
int			ft_strcmp(char *s1, char *s2);

//parsing utils
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
int			ft_isspace(char c);

//builtin utils
int			refresh_pwd(t_envlist **envc);
int			refresh_oldp(t_envlist **envc);

//free
void		free_command_line(t_cmd *commands, char *line, int nb_pipes, int g);
void		free_tab(int **tab, int i);
int			free_all(t_exec exec, int nb_comm);
void		free_char_tab(char **tab);
int			ft_free_tab(char **tab);
int			free_char_tab_ret(t_exec exec);
int			free_expand(char *a, char *b, char *c, char *d);
void		ft_lstclear_v2(t_envlist **lst);
void		free_flag_string(t_f_str flag_string);

//init
t_cmd		*init_commands(char	*line, int nb_pipes, t_f_str *fs);
void		init_inc(t_inc *inc);
int			exec_init(t_exec *exec);
int			*init_tab_fd(int nb_file);
void		init_command_tab(t_cmd **commands, int nb_pipes);

//error
int			error_handler(int argc, char **argv);
int			error_type(t_cmd *comm, int line, t_envlist **envc);
int			mall_error(void);

//signal
void		sighandler(int sig);
void		sig_handler(int signum);
void		sig_heredoc(int signum);
void		pipe_sighandler(int sig);
void		cancel_sighandler(int signal);

#endif
