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

typedef struct s_commands
{
	int		nb_args_in_command;
	int		nb_infile;
	int		nb_outfile;
	int		builtin;
	int		heredoc;
	int		append;
	char	**tab_infile;
	char	**tab_outfile;
	char	**single_command;
}	t_commands;

typedef struct s_flag_string1
{
	char	*special_chars;
	char	*quotes;
	char	**tab_special_chars;
	char	**tab_quotes;
}	t_flag_string;

typedef struct s_inc
{
	int	i;
	int	j;
	int	k;
	int	n;
}	t_inc;

typedef struct s_exec
{
	int		nb_comm;
	pid_t	*cpid;
	int		**fd;
	int		comm_i;
	char	**envp;
	int		status;
	int		temp;
}	t_exec;

char		*correct_line(char *line);
int			count_arguments(char *line, char c, t_flag_string f_str);
int			is_in_quotes(t_flag_string flag_string, int i);
int			error_handler(int argc, char **argv);
int			parsing(t_commands **commands, t_flag_string *flag_string, int *nb_pipes, char **line);
int			quotes_flags(t_flag_string *flag_string, char *line);
int			special_char_flags(t_flag_string *flag_string, char *line);
void		sig_handler(int signum);
void		prompt(void);
void		free_command_line(t_commands *commands, char *line, int nb_pipes);
void		ft_increment(char const *s, char c, size_t *i, t_flag_string f_str);
char		**ft_split_v2(char const *s, char c, t_flag_string f_str);
t_commands	*init_commands(char	*line, int nb_pipes, t_flag_string fs);
int			exec_main(t_commands *commands, int nb_pipes, char **envp);
int			pipe_error_case(int nb_comm, t_exec exec);
void		wait_all_cpid(pid_t *cpid, int status, int i);
int			exec_init(t_exec *exec, t_commands *commands, int nb_comm, char **envp);
int			**tab_fd_mall(int nb_comm);
void		close_fd(int **fd, int i);
void		child_process(t_commands *commands, int temp, int nb_comm, t_exec exec);
void		free_tab(int **tab, int i);
int			free_all(t_exec exec, int nb_comm);
int			find_special_char(char c, t_flag_string f_str, int *k);
int			find_end_redirection(char c, t_flag_string f_str, int *k);

#endif
