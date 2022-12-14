#include "minishell.h"

void	free_flag_string(t_f_str flag_string)
{
	free(flag_string.sp_chars);
	free(flag_string.quotes);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		errno = 1;
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_misc			misc;
	t_commands		*commands;
	t_f_str			flag_string;
	t_envlist		*envc;

	envc = NULL;
	if (argc != 1 || !isatty(1))
		return (0);
	envc = envcpy(envp);
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		parsing(&commands, &flag_string, &misc, envc);
		commands = commands_path(commands, misc.nb_commands, envc);
		exec_main(commands, misc.nb_commands, &envc);
		free_flag_string(flag_string);
		free_command_line(commands, misc.line, misc.nb_commands);
	}
	return (0);
}

/*debug code pour les tableaux d'arguments
		i = 0;
		while (line[i] != '\n')
			i++;
		line[i] = '\0';
		printf("%sline\n", line);
		nb_pipes = count_arguments(line, '|');
		full_command_line = ft_split(line, '|');
		printf("%dpipes\n", nb_pipes);
		printf("%s\n", f_str.sp_chars);
		printf("%s\n", f_str.quotes);
		printf("%d\n", nb_pipes);
		i = 0;
		while (full_command_line[i] != 0)
		{
			printf("%scommandline\n", full_command_line[i]);
			i++;
		}
		commands = malloc(sizeof(t_commands) * nb_pipes);
		if (!commands)
			return (0);
		i = 0;
		while (full_command_line[i] != 0)
		{
			commands[i].single_command = ft_split(full_command_line[i], ' ');
			i++;
		}
		i = 0;
		while (i < nb_pipes)
		{
			j = 0;
			while (commands[i].single_command[j] != 0)
			{
				printf("%s.%d\n", commands[i].single_command[j], i);
				j++;
			}
			i++;
		}
		i = 0;
		while (i < nb_pipes)
		{
			j = 0;
			while (commands[i].single_command[j] != 0)
			{
				free(commands[i].single_command[j]);
				j++;
			}
			free(commands[i].single_command);
			free(full_command_line[i]);
			i++;
		}
		free(commands);
		free(full_command_line);
		free (line);
		*/
/*debug redirections
 		i = 0;
		while (i < nb_pipes)
		{
			printf("%d\t%d\n", commands[i].nb_infile, commands[i].nb_outfile);
			i++;
		}
*/
//debug arguments
/*		printf("%s\t%s\n", f_str.quotes, f_str.sp_chars);
		printf("%d\n", nb_commands);
		i = 0;
		while (i < nb_commands)
		{
			j = 0;
			while (commands[i].single_command[j] != 0)
			{
				printf("%s\n", commands[i].single_command[j]);
				j++;
			}
			i++;
		}*/
//debug tab_files
/*		i = 0;
		while (i < nb_commands)
		{
			j = 0;
			while (j < commands[i].nb_infile)
			{
				printf("%s\t%din\n", commands[i].tab_infile[j], i);
				j++;
			}
			if (commands[i].nb_infile > 0)
				printf("%s\tf_in\n", commands[i].flag_in);
			i++;
		}
		i = 0;
		while (i < nb_commands)
		{
			j = 0;
			while (j < commands[i].nb_outfile)
			{
				printf("%s\t%dout\n", commands[i].tab_outfile[j], i);
				j++;
			}
			if (commands[i].nb_outfile > 0)
				printf("%s\tf_out\n", commands[i].flag_out);
			i++;
		}*/
/*		i = 0;
		while (i < nb_commands)
		{
			j = 0;
			while (commands[i].sgl_cmd[j] != 0)
			{
				printf("%s.%d\n", commands[i].sgl_cmd[j], i);
				j++;
			}
			j = 0;
			while (commands[i].nb_infile > 0 && j < commands[i].nb_infile)
			{
				printf("%s.%d.infile\n", commands[i].tab_infile[j], i);
				j++;
			}
			if (commands[i].nb_infile > 0)
				printf("%s.%dfin\n", commands[i].flag_in, i);
			j = 0;
			while (commands[i].nb_outfile > 0 && j < commands[i].nb_outfile)
			{
				printf("%s.%d.outfile\n", commands[i].tab_outfile[j], i);
				j++;
			}
			if (commands[i].nb_outfile > 0)
				printf("%s.%dfout\n", commands[i].flag_out, i);
			i++;
		}*/
