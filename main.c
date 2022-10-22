/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:21:23 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/22 19:36:39 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_commands
{
	int		nb_args_in_command;
	int		infile;
	int		outfile;
	char	**single_command;
}	t_commands;

int	error_handler(int argc, char **argv)
{
	(void) argv;
	if (argc > 1)
	{
		printf("No such file or directory\n");
		return (1);
	}
	return (0);
}

void	prompt(void)
{
	ft_putstr_fd("minishell$ ", 0);
}

int	count_arguments(char *line, char c)
{
	int		count;
	int		i;
	int		flag_count;

	count = 0;
	flag_count = 1;
	i = 0;
	while (line[i] != '\0')
	{
		if (flag_count == 1 && line[i] != c && line[i] != '\n')
		{
			flag_count = 0;
			count++;
		}
		if (line[i] == c && line[i] != '\0')
			flag_count = 1;
		i++;
	}
	return (count);
}

t_commands	*init_commands(char	*line, int nb_pipes)
{
	int			i;
	t_commands	*commands;
	char		**full_command_line;

	full_command_line = ft_split(line, '|');
	commands = malloc(sizeof(t_commands) * nb_pipes);
	if (!commands)
		return (0);
	i = 0;
	while (full_command_line[i] != 0)
	{
		commands[i].single_command = ft_split(full_command_line[i], ' ');
		i++;
	}
	return (commands);
}

char	*correct_line(char *line)
{
	int		i;
	char	*correct;

	correct = line;
	i = 0;
	while (correct[i] != '\n')
		i++;
	correct[i] = '\0';
	return (correct);
}

int	main(int argc, char **argv)
{
	char		*line;
	int			i;
	int			j;
	int			nb_pipes;
	t_commands	*commands;

	if (error_handler(argc, argv) == 1)
		return (0);
	prompt();
	while (1)
	{
		line = get_next_line(0);
		//separate line with pipes and redirections
		line = correct_line(line);
		nb_pipes = count_arguments(line, '|');
		printf("%dpipes\n", nb_pipes);
		commands = init_commands(line, nb_pipes);
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
			i++;
		}
		free(commands);
		free (line);
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
