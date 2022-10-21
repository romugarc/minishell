/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:21:23 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/21 19:38:47 by rgarcia          ###   ########lyon.fr   */
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

int	count_arguments(char *line)
{
	int		count;
	int		i;
	int		flag_count;

	count = 0;
	flag_count = 1;
	i = 0;
	while (line[i] != '\0')
	{
		if (flag_count == 1 && line[i] != ' ' && line[i] != '\0')
		{
			flag_count = 0;
			count++;
		}
		if (line[i] == ' ' && line[i] != '\0')
			flag_count = 1;
		i++;
	}
	return (count);
}

int	main(int argc, char **argv)
{
	char		*line;
	int			i;
	t_commands	commands;

	if (error_handler(argc, argv) == 1)
		return (0);
	prompt();
	while (1)
	{
		line = get_next_line(0);
		//separate line with pipes and redirections
		//count pipes
		//malloc struct arguments with nb_pipes
		//struct arguments = malloc(sizeof(char *) * nb_pipes + 1);
		//full_line = ft_split(line, '|');, this is a tab with every command
		//single_command = ft_split(full_line[i], ' ');, this is a tab with the arguments of a given command
		//commands.nb_args_in_command = count_arguments(full_line[i]);
		//commands.single_command = ft_split(full_line[i], ' ');
		commands.nb_args_in_command = count_arguments(line);
		printf("%d", commands.nb_args_in_command);
		commands.single_command = ft_split(line, ' ');
		i = 0;
		while (commands.single_command[i] != 0)
		{
			printf("%s ", commands.single_command[i]);
			i++;
		}
		i = 0;
		while (commands.single_command[i] != 0)
		{
			free(commands.single_command[i]);
			i++;
		}
		free(commands.single_command);
		free (line);
		prompt();
	}
	return (0);
}
