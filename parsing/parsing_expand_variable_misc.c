/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_variable_misc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:32:44 by rgarcia           #+#    #+#             */
/*   Updated: 2022/12/11 11:44:37 by rgarcia          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_search(char *str, t_f_str f_str)
{
	int	k;

	k = 0;
	while (!(str[k] == '$' \
		&& f_str.quotes[k] != '1') \
		&& str[k] != '\0')
		k++;
	if (f_str.quotes[k] == '\0' || f_str.quotes[k + 1] == '\0')
		return (1);
	return (0);
}

int	copy_var2(char *line, t_inc *i, t_envlist *tmp, char **new_line)
{
	if (i->l_j == 1)
	{
		if (cat_ex_var(line, i, tmp, new_line) == 1)
			return (1);
	}
	else
	{
		if (cat_ex_varnf(line, i, new_line) == 1)
			return (1);
	}
	return (0);
}

int	expand_heredoc(char **str, t_envlist *envc)
{
	t_f_str	f_str;
	int	flag;

	flag = 0;
	while (flag == 0)
	{
		if (search_expand(str, envc) == 1)
			return (1);
		if (quotes_flags(&f_str, *str) == 1)
			return (1);
		if (expand_search(*str, f_str) == 1)
			flag = 1;
		free (f_str.quotes);
	}
	return (0);
}
