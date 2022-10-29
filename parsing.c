/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:53:03 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/29 19:35:56 by rgarcia          ###   ########lyon.fr   */
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

char	*set_quote_flag(char *line, char *quote_string, int *i, int flag)
{
	int		j;

	if (flag != 0)
		j = *i + 1;
	else
		j = *i;
	if (flag == 2)
	{
		while (line[j] != '"' && line[j] != '\0')
		{
			printf("sqf2.%c\n", line[j]);
			printf("cho.j2.%d\n", j);
			quote_string[j] = '2';
			printf("%c\n", quote_string[j]);
			printf("%s\n", quote_string);
			j++;
		}
	}
	else if (flag == 1)
	{
		while (line[j] != 39 && line[j] != '\0')
		{
			printf("cho.j1.%d\n", j);
			quote_string[j] = '1';
			j++;
		}
	}
	else if (flag == 0)
	{
		printf("sqf0.%c\n", line[j]);
		printf("cho.j0.%d\n", j);
		quote_string[j] = '0';
	}
	printf("%dj\n", j);
	if (quote_string[j] != '\0' && flag != 0)
		*i = j + 1;
	else
		*i = j;
	return (quote_string);
}

char	what_quote(int flag)
{
	if (flag == 2)
		return ('2');
	else if (flag == 1)
		return ('1');
	return ('0');
}

int	quotes_flags(t_flag_string *flag_string, char *line)
{
	int	i;
	int	quote_flag;
	char	*quote_string;

	i = 0;
	quote_flag = 0;
	quote_string = malloc (sizeof(char) * ft_strlen(line));
	if (!quote_string)
	{
		free(quote_string);
		return (1);
	}
	while (line[i] != '\0')
	{
		if (line[i] == '"' && quote_flag == 0 && line[i] != '\0')
			quote_flag = 2;
		else if (quote_flag == 2 && line[i] != '\0')
			quote_flag = 0;
		if (line[i] == 39 && quote_flag == 0 && line[i] != '\0')
			quote_flag = 1;
		else if (quote_flag == 1 && line[i] != '\0')
			quote_flag = 0;
	}
	quote_string[i] = '\0';
	flag_string->quotes = quote_string;
	return (0);
}

int	special_char_flags(t_flag_string *flag_string, char *line)
{
	int		i;
	char	*special_string;

	special_string = malloc (sizeof(char) * ft_strlen(line));
	if (!special_string)
	{
		free(special_string);
		return (1);
	}
	i = 0;
	while (line[i] != '\0')
	{
		special_string[i] = what_special_char(line, i);
		i++;
	}
	special_string[i] = '\0';
	flag_string->special_chars = special_string;
	return (0);
}

int	parsing(t_commands **commands, t_flag_string *flag_string, int *nb_pipes, char **line)
{
	*line = get_next_line(0);
	*line = correct_line(*line);
	*nb_pipes = count_arguments(*line, '|');
	printf("%d\n", *nb_pipes);
	special_char_flags(flag_string, *line);
//	printf("%s\n", flag_string->special_chars);
	quotes_flags(flag_string, *line);
	printf("%s\n", flag_string->special_chars);
	printf("%s\n", flag_string->quotes);
	*commands = init_commands(*line, *nb_pipes);
	return (0);
}
