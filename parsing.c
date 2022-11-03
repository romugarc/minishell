/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/03 19:34:21 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	tab_redirections(t_commands **commands, t_flag_string flag_string, char **line)
{
	
	return (0);
}*/
int	split_redirection(char *tab, char **tab_files, int nb_files, t_flag_string f_str)
{
	int	i;
	int	j;

	i = 0;
	(void)f_str;
	while (tab_files[i] != 0)
		i++;
	while (i < nb_files)
	{
		j = 0;
		while (tab[j] != '\0')
		{
			j++;
		}
		i++;
	}
	return (0);
}

int	is_redirection(char *str, t_flag_string f_str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
		{
			if (str[i + 1] != '>')
				return (1);
			return (0);
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] != '<')
				return (2);
			return (0);
		}
		i++;
	}
	return (0);
}

void	count_redirections(t_commands **commands, int np)
{
	int	i;
	int	j;

	i = 0;
	while (i < np)
	{
		(*commands)[i].nb_outfile = 0;
		(*commands)[i].nb_infile = 0;
		j = 0;
		while ((*commands)[i].single_command[j] != 0)
		{
			if (is_redirection((*commands)[i].single_command[j]) == 1)
				(*commands)[i].nb_outfile += 1;
			else if (is_redirection((*commands)[i].single_command[j]) == 2)
				(*commands)[i].nb_infile += 1;
			j++;
		}
		i++;
	}
}

/*int	correct_tabs(t_commands **commands, t_flag_string flag_string, int nb_pipes)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_pipes)
	{
		j = 0;
		while (*commands[i]->single_command[j] != 0)
		{
			if ((*commands)[i].single_command[j][0] == '>')
			{
				if ((*commands)[i].single_command[j][1] != '>')
					(*commands)[i].nb_outfile += 1;
			}
			j++;
		}
		i++;
	}
	return (0);
}*/

int	parsing(t_commands **commands, t_flag_string *flag_string, int *nb_pipes, char **line)
{
//	char	**tab;
//	char	**tab_infiles;
//	char	**tab_outfiles;
//	int		i;
//	int		j;
//	int		k;
//	int		nb_infiles;
//	int		nb_outfiles;

	*line = get_next_line(0);
	*line = correct_line(*line);
	if (special_char_flags(flag_string, *line) != 0)
		return (1);
	if (quotes_flags(flag_string, *line) != 0)
		return (1);
	*nb_pipes = count_arguments(*line, '|', *flag_string);
//	tab = ft_split_v2(*line, '|', *flag_string);
//	*commands = malloc(sizeof(t_commands) * *nb_pipes);
//	if (!commands)
//		return (0);
/*	tab_infiles = malloc(sizeof(char *) * (nb_infiles + 1));
	if (!tab_infiles)
		return (1);
	tab_outfiles = malloc(sizeof(char *) * (nb_outfiles + 1));
	if (!tab_outfiles)
		return (1);*/
	*commands = init_commands(*line, *nb_pipes, *flag_string);
	count_redirections(commands, *nb_pipes);
//	correct_tabs(commands, *flag_string, *nb_pipes);
	return (0);
}

//debug code pour commands (attention aux segfault si y a rien dans commands)
/*	i = 0;
	while (i < *nb_pipes)
	{
		printf("avantnb\n");
		commands[i]->nb_infile = 0;
		commands[i]->nb_outfile = 0;
		printf("avantredir\n");
		count_redirections(commands[i], *flag_string, tab);
		printf("%d\t%d\n", commands[i]->nb_infile, commands[i]->nb_outfile);
		i++;
	}*/

