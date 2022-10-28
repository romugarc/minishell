/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/28 19:31:00 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	what_special_char(char *str, int i)
{
	if (str[i] == 39)
		return ('3');
	else if (str[i] == '"')
		return ('4');
	else if (str[i] == '|')
		return ('5');
	else if (str[i] == '>')
		return ('6');
	else if (str[i] == '<')
		return ('7');
	return ('0');
}

int	special_char_flags(t_flag_string *flag_string, char *line)
{
	int		i;
	char	*special_string;

	special_string = malloc (sizeof(char) * ft_strlen(line));
	if (!special_string)
	{
		free(special_string);
		return (0);
	}
	i = 0;
	while (line[i] != '\0')
	{
		special_string[i] = what_special_char(line, i);
		i++;
	}
	special_string[i] = '\0';
	flag_string->special_chars = special_string;
	flag_string->quotes = special_string;
	return (0);
}

int	parsing(t_commands **commands, t_flag_string *flag_string, int *nb_pipes, char **line)
{
	*line = get_next_line(0);
	*line = correct_line(*line);
	*nb_pipes = count_arguments(*line, '|');
	printf("%d\n", *nb_pipes);
	special_char_flags(flag_string, *line);
	printf("%s\n", flag_string->special_chars);
	*commands = init_commands(*line, *nb_pipes);
	return (0);
}
