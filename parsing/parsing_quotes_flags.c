/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:49:32 by rgarcia           #+#    #+#             */
/*   Updated: 2022/11/19 14:49:16 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	what_quote(char *str, int i, int *flag)
{
	if (str[i] != '\0')
	{
		if (*flag == 2 && str[i] != '"')
			return ('2');
		else if (*flag == 1 && str[i] != 39)
			return ('1');
		else if (*flag == 0)
			return ('0');
	}
	return ('\0');
}

int	quotes_flags(t_f_str *f_str, char *line)
{
	int		i;
	int		j;
	int		q_flag;
	char	*quote_string;

	i = 0;
	q_flag = 0;
	quote_string = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!quote_string)
		return (1);
	while (line[i] != '\0')
	{
		j = i;
		quote_string[i] = set_quote_flag(line, &j, &q_flag);
		i = j;
		if ((line[i] == '"' && q_flag != 1) || (line[i] == 39 && q_flag != 2))
			quote_string[i] = set_quote_flag(line, &j, &q_flag);
		i = j;
		quote_string[i] = what_quote(line, i, &q_flag);
		if (line[i] != '\0')
			i++;
	}
	quote_string[i] = '\0';
	f_str->quotes = quote_string;
	return (0);
}
