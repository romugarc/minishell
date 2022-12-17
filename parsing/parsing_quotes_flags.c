/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:49:32 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:30:58 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	single_quotes_flags(char *line, char **quote_string, int *i)
{
	(*quote_string)[*i] = '0';
	*i += 1;
	while (line[*i] != 39 && line[*i] != '\0')
	{
		(*quote_string)[*i] = '1';
		*i += 1;
	}
	if (line[*i] == 39)
		(*quote_string)[*i] = '0';
}

static void	double_quotes_flags(char *line, char **quote_string, int *i)
{
	(*quote_string)[*i] = '0';
	*i += 1;
	while (line[*i] != '"' && line[*i] != '\0')
	{
		(*quote_string)[*i] = '2';
		*i += 1;
	}
	if (line[*i] == '"')
		(*quote_string)[*i] = '0';
}

int	quotes_flags(t_f_str *f_str, char *line)
{
	int		i;
	char	*quote_string;

	quote_string = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!quote_string)
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			double_quotes_flags(line, &quote_string, &i);
		else if (line[i] == 39)
			single_quotes_flags(line, &quote_string, &i);
		else
			quote_string[i] = '0';
		if (line[i] != '\0')
			i++;
	}
	quote_string[i] = '\0';
	f_str->quotes = quote_string;
	return (0);
}
