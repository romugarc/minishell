/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:49:32 by rgarcia           #+#    #+#             */
/*   Updated: 2022/10/30 15:55:28 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	set_quote_flag(char *str, int *i, int *flag)
{
	if (str[*i] == '\0')
		return ('\0');
	if (str[*i] == '"' && *flag == 0)
	{
		*flag = 2;
		*i = *i + 1;
	}
	else if (str[*i] == '"' && *flag == 2)
	{
		*flag = 0;
		*i = *i + 1;
	}
	else if (str[*i] == 39 && *flag == 0)
	{
		*flag = 1;
		*i = *i + 1;
	}
	else if (str[*i] == 39 && *flag == 1)
	{
		*flag = 0;
		*i = *i + 1;
	}
	return ('0');
}

static char	what_quote(char *str, int i, int flag)
{
	if (str[i] != '\0')
	{
		if (flag == 2 && str[i] != '"')
			return ('2');
		else if (flag == 1 && str[i] != 39)
			return ('1');
		else if (flag == 0)
			return ('0');
		else
			return ('0');
	}
	return ('\0');
}

int	quotes_flags(t_flag_string *flag_string, char *line)
{
	int		i;
	int		j;
	int		quote_flag;
	char	*quote_string;

	i = 0;
	quote_flag = 0;
	quote_string = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!quote_string)
	{
		free(quote_string);
		return (1);
	}
	while (line[i] != '\0')
	{
		j = i;
		quote_string[i] = set_quote_flag(line, &j, &quote_flag);
		i = j;
		quote_string[i] = what_quote(line, i, quote_flag);
		if (line[i] != '\0')
			i++;
	}
	quote_string[i] = '\0';
	flag_string->quotes = quote_string;
	return (0);
}
