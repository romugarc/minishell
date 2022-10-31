/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:41:46 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/31 17:48:04 by fsariogl         ###   ########.fr       */
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

typedef struct s_commands
{
	int		nb_args_in_command;
	int		infile;
	int		outfile;
	char	**single_command;
}	t_commands;

typedef struct s_flag_string
{
	char	*special_chars;
	char	*quotes;
}	t_flag_string;

char		*correct_line(char *line);
int			count_arguments(char *line, char c);
int			is_in_quotes(char	*str, int index, int *last_quote);
int			error_handler(int argc, char **argv);
int			parsing(t_commands **commands, t_flag_string *flag_string, int *nb_pipes, char **line);
int			quotes_flags(t_flag_string *flag_string, char *line);
int			special_char_flags(t_flag_string *flag_string, char *line);
void		sig_handler(int signum);
void		prompt(void);
void		free_command_line(t_commands *commands, char *line, int nb_pipes);
char		**ft_split_v2(char const *s, char c);
t_commands	*init_commands(char	*line, int nb_pipes);
void		exec_main(t_commands *commands, int nb_pipes, char **envp);


#endif
