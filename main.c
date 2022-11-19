#include "minishell.h"

void	free_flag_string(t_f_str flag_string)
{
	free(flag_string.sp_chars);
	free(flag_string.quotes);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	int				nb_commands;
	t_commands		*commands;
	t_f_str	flag_string;
	t_envlist		*envc;

	envc = NULL;
	if (error_handler(argc, argv) == 1)
			return (0);
	envc = envcpy(envp);
	prompt();
	while (1)
	{
		parsing(&commands, &flag_string, &nb_commands, &line);
//		commands = commands_path(commands, nb_commands);
//		exec_main(commands, nb_commands, envp);
		free_flag_string(flag_string);
		free_command_line(commands, line, nb_commands);
		prompt();
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
