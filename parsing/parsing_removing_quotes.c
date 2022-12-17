/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_removing_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:37:10 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/16 15:38:21 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	form_new_str(char **new_str, char *str, t_f_str f_str)
{
	int	i;
	int	nb_nq;

	i = 0;
	nb_nq = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != '"' && str[i] != 39 && is_in_quotes(f_str, i) == 0) \
			|| is_in_quotes(f_str, i) != 0)
		{
			(*new_str)[nb_nq] = str[i];
			nb_nq++;
		}
		i++;
	}
	(*new_str)[nb_nq] = '\0';
}

static int	count_not_quotes(char *str, t_f_str f_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != '"' && str[i] != 39 && is_in_quotes(f_str, i) == 0) \
			|| is_in_quotes(f_str, i) != 0)
			j++;
		i++;
	}
	return (j);
}

static int	swap_free(char **line, char *new_line)
{
	char	*tmp_line;

	if (new_line != NULL)
	{
		tmp_line = *line;
		*line = new_line;
		free(tmp_line);
	}
	return (0);
}

int	removing_quotes(char **str)
{
	int		nb_nq;
	char	*new_str;
	t_f_str	f_str;

	if (quotes_flags(&f_str, *str) == 1)
		return (1);
	nb_nq = count_not_quotes(*str, f_str);
	new_str = malloc(sizeof(char) * nb_nq + 1);
	if (!new_str)
		return (1);
	form_new_str(&new_str, *str, f_str);
	swap_free(str, new_str);
	free(f_str.quotes);
	return (0);
}
