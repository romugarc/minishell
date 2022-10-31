/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:21:23 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/31 18:56:15 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	int				nb_pipes;
	t_commands		*commands;
	t_flag_string	flag_string;
	int	i;
	int	j;

	(void)envp;
	if (error_handler(argc, argv) == 1)
			return (0);
	prompt();
	while (1)
	{
		//signal(SIGINT, sig_handler);
		//signal(SIGQUIT, SIG_IGN);
		//signal(SIGTSTP, SIG_IGN);
		parsing(&commands, &flag_string, &nb_pipes, &line);
		printf("%s\n", flag_string.special_chars);
		printf("%s\n", flag_string.quotes);
		printf("%d\n", nb_pipes);
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
		//if (commands[0].single_command != 0)
		//execve(commands[0].single_command[0], commands[0].single_command, envp);
		//perror("minishell");
		free_command_line(commands, line, nb_pipes);
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
