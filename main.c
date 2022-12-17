#include "minishell.h"

void	print_parsing_err(int errnb)
{
	if (errnb == 134)
		ft_putstr_fd("minishell: malloc error\n", 2);
	else if (errnb == 258)
		ft_putstr_fd("minishell: syntax error\n", 2);
}

int	main(int argc, char **argv, char **envp)
{
	t_misc			misc;
	t_cmd		*commands;
	t_f_str			flag_string;
	t_envlist		*envc;

	envc = NULL;
	if (argc != 1 || argv[1] != NULL || !isatty(1))
		return (0);
	envc = envcpy(envp);
	if (g_errno == 134)
		print_parsing_err(g_errno);	
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		g_errno = parsing(&commands, &flag_string, &misc, envc);
		if (g_errno == 0)
		{
			commands = commands_path(commands, misc.nb_commands, envc);
			exec_main(commands, misc.nb_commands, &envc);
		}
		else
			print_parsing_err(g_errno);
		free_flag_string(flag_string);
		free_command_line(commands, misc.line, misc.nb_commands, g_errno);
	}
	free_envc(envc);
	return (0);
}
